#ifndef NSFIELD_H
#define NSFIELD_H

#include <vector>
#include <pthread.h>
#include <algorithm>
#include <iostream>
#include "cfield.h"
#include <unistd.h>

using namespace std;

int counter = 0;
bool solved = false;
vector<vector<char> > thesolvedfield;
int nuot = 0;

/**
   @brief sets the pnumsoffield in the field

   @param field is the sudoku field you wanna solve
   @param pnumsoffield are the possible numbers of the field

   @returns the field
 */
vector<vector<char> > getnums(vector<vector<char> > field,vector<vector<vector<char> > > pnumsoffield){
        for(int a = 0; a < 9; a++) {
                for(int b = 0; b < 9; b++) {
                        if(pnumsoffield[a][b].size() == 1) {
                                if(pnumsoffield[a][b][0] != 0) {
                                        field[a][b] = pnumsoffield[a][b][0];
                                }
                        }
                }
        }
        return field;
}

/**
   @brief removes the impossible numbers from pnumsoffield

   @param pnumsoffield the possible numbers of the field
   @param field is the sudoku field
   @param a is the first coordinate from the field you wanna clear;
   @param b is the seccond coordinate from the field you wanna clear;

   @returns pnumsoffield
 */
vector<vector<vector<char> > > cleardoubles(vector<vector<vector<char> > > pnumsoffield,vector<vector<char> > field){
        for(int a = 0; a < 9; a++) {
                for(int b = 0; b < 9; b++) {
                        if(pnumsoffield[a][b].size() > 1) {
                                vector<char> h; vector<char> v; vector<char> s;
                                for(int i = 0; i < 9; i++) {
                                        h.push_back(field[a][i]);
                                        v.push_back(field[i][b]);
                                }
                                int oa = a, ob = b, na, nb;
                                if(a < 3) {na = 0; }else if(a < 6) {na = 3; }else{na = 6; }
                                if(b < 3) {nb = 0; }else if(b < 6) {nb = 3; }else{nb = 6; }
                                for(int d = 0; d < 3; d++) {
                                        for(int c = 0; c < 3; c++) {
                                                s.push_back(field[na+c][nb+d]);
                                        }
                                }
                                vector<vector<char> > hvs = {h,v,s};
                                for(y : hvs) {
                                        for(x : y) {
                                                for(int i = 0; i < pnumsoffield[oa][ob].size(); i++) {
                                                        if(pnumsoffield[oa][ob][i] == x) {
                                                                pnumsoffield[oa][ob].erase(pnumsoffield[oa][ob].begin()+i);
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        return pnumsoffield;
}

/**
   @brief fills the pnumsoffield with all numbers if field in sudoku is empty

   @param field is the sudoku field

   @returns the pnumsoffield
 */
vector<vector<vector<char> > > getpnumsoffield(vector<vector<char> > field){
        vector<vector<vector<char> > > pnumsoffield = {{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}}};;
        for(int i = 0; i < 9; i++) {
                for(int a = 0; a < 9; a++) {
                        if(field[i][a] == 0) {
                                pnumsoffield[i][a] = {1,2,3,4,5,6,7,8,9};
                        }else{
                                pnumsoffield[i][a].push_back(field[i][a]);
                        }
                }
        }
        return pnumsoffield;
}

//only used for sort
bool sortfor(vector<char> &a, vector<char> &b){
        return (a[2] < b[2]);
}

void* getsolvedfield(void* argument){
  nuot++;
        vector<vector<char> > field = *((vector<vector<char> >*)argument);
        pthread_t t;
        vector<vector<vector<char> > > pnumsoffield; // here the possible number for the field are stored
        pnumsoffield = getpnumsoffield(field);
        //ddraw(field, z);
        counter++;
        //cout << counter << " " << solved << endl;
        vector<vector<char> > oldfield = field;
        for(;; ) {
          if(solved){pthread_exit(NULL);}
                oldfield = field;
                pnumsoffield = cleardoubles(pnumsoffield, field);
                field = getnums(field, pnumsoffield);
                if(checkfield(field)) {break;}
                if(field == oldfield) {
                        vector<vector<char> > posibleturns(81,{0,0,0});
                        int countforposibletruns = 0;
                        for(int a = 0; a < 9; a++) {
                                for(int b = 0; b < 9; b++) {
                                        if(field[a][b] == 0 && pnumsoffield[a][b].size() > 1) {
                                                posibleturns[countforposibletruns][0] = a;
                                                posibleturns[countforposibletruns][1] = b;
                                                posibleturns[countforposibletruns][2] = pnumsoffield[a][b].size();
                                                countforposibletruns++;
                                        }
                                }
                        }
                        sort(posibleturns.begin(), posibleturns.end(), sortfor); // sorts so that the lowest number of fields are tryed first
                        for(s : posibleturns) {
                                if(s[2] > 0) {
                                        for(int i = 0; i < s[2]; i++) {
                                                field[s[0]][s[1]] = pnumsoffield[s[0]][s[1]][i];
                                                if(nuot > 100){sleep(1);}
                                                pthread_create(&t,NULL,getsolvedfield,(void*)&field);
                                                field = oldfield;
                                        }
                                }
                        }
                        break;
                };
        }
        if(checkfield(field)){
          thesolvedfield = field;
          solved = true;
        }
        nuot--;
        pthread_exit(NULL);
}

/**
   @brief Solves the sudoku

   @param field is the sudoku field

   @returns the solved field
 */
vector<vector<char> > solvefield(vector<vector<char> > field){
        pthread_t t1;
          pthread_create(&t1,NULL,getsolvedfield,(void*)&field);
        for(;;) {
                cout << "number: " << nuot << endl;
                if(solved) {return thesolvedfield; }
        }
}

#endif
