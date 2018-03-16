#ifndef SFIELD_H
#define SFIELD_H

#include <vector>
#include "cfield.h"

using namespace std;

int counter;

bool isfieldfull(vector<vector<vector<int> > > pnumsoffield){
  for(int a = 0; a < 9; a++) {
          for(int b = 0; b < 9; b++) {
                  if(pnumsoffield[a][b].size() > 1) {
                          return false;
                  }
          }
  }
  return true;
}

/**
  @brief sets the pnumsoffield in the field

  @param field is the sudoku field you wanna solve
  @param pnumsoffield are the possible numbers of the field

  @returns the field
*/
vector<vector<int> > getnums(vector<vector<int> > field,vector<vector<vector<int> > > pnumsoffield){
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
vector<vector<vector<int> > > cleardoubles(vector<vector<vector<int> > > pnumsoffield,vector<vector<int> > field){
        for(int a = 0; a < 9; a++) {
                for(int b = 0; b < 9; b++) {
                        if(pnumsoffield[a][b].size() > 1) {
                                vector<int> h; vector<int> v; vector<int> s;
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
                                vector<vector<int> > hvs = {h,v,s};
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
vector<vector<vector<int> > > getpnumsoffield(vector<vector<int> > field){
        vector<vector<vector<int> > > pnumsoffield = {{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}}};;
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

vector<vector<int> > getsolvedfield(vector<vector<int> > field){
  vector<vector<vector<int> > > pnumsoffield;
  pnumsoffield = getpnumsoffield(field);
        vector<vector<int> > oldfield = field;
        counter++;
        cout << counter << endl;
        int a,b;
        while(true) {
                oldfield = field;
                pnumsoffield = cleardoubles(pnumsoffield, field);
                field = getnums(field, pnumsoffield);
                if(isfieldfull(pnumsoffield)){break;}
                if(checkfield(field)) {break;}
                if(field == oldfield) {
                  do{
                    a = rand() % 9;
                    b = rand() % 9;
                  }while(field[a][b] != 0 && pnumsoffield[a][b].size() > 1);
                  field[a][b] = rand() % 9;
                  field = getsolvedfield(field);
                  if(checkfield(field)){return field;}else{field[a][b] = 0;}
                };
        }
        return field;
}

/**
   @brief Solves the sudoku

   @param field is the sudoku field

   @returns the solved field
 */
vector<vector<int> > solvefield(vector<vector<int> > field){
        srand(time(NULL));
        vector<vector<int> > oldfield = field;
        while(true){
          field = getsolvedfield(oldfield);
          if(checkfield(field)){return field;}
        }
}

#endif
