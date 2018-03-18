#ifndef SFIELD_H
#define SFIELD_H

#include <vector>
#include "cfield.h"
#include <algorithm>

using namespace std;

int counter = 1;

void ddraw(vector<vector<int>> field){
  system("clear");
  cout << "-------------------------" << endl;
  for(int i = 0; i < 9; i++){
    cout << "| ";
    for(int a = 0; a < 9; a++){
      cout << field[i][a] << " ";
      if((a+1) % 3 == 0) cout << "| ";
      if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << "-------------------------" << endl;};
    }
  }
}

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

//only used for sort
bool sortfor(vector<int> a, vector<int> b){return (a[2] < b[2]);}

/**
  @brief solves the field

  @param field is the sudoku field

  @returns the solved field
*/
vector<vector<int> > getsolvedfield(vector<vector<int> > field){
  vector<vector<vector<int> > > pnumsoffield; // here the possible number for the field are stored
  pnumsoffield = getpnumsoffield(field);
  ddraw(field);
        vector<vector<int> > oldfield = field;
        counter++;
        cout << counter << endl;
        while(true) {
          oldfield = field;
          pnumsoffield = cleardoubles(pnumsoffield, field);
          field = getnums(field, pnumsoffield);
          if(isfieldfull(pnumsoffield)){break;}
          if(checkfield(field)) {break;}
          if(field == oldfield) {
            vector<vector<int>> posibleturns(81,{0,0,0});
            int countforposibletruns = 0;
            for(int a = 0; a < 9; a++){
              for(int b = 0; b < 9; b++){
                if(field[a][b] == 0 && pnumsoffield[a][b].size() > 1){
                  posibleturns[countforposibletruns][0] = a;
                  posibleturns[countforposibletruns][1] = b;
                  posibleturns[countforposibletruns][2] = pnumsoffield[a][b].size();
                  countforposibletruns++;
                }
              }
            }
            sort(posibleturns.begin(), posibleturns.end(), sortfor); // sorts so that the lowest number of fields are tryed first
            for(s:posibleturns){
              if(s[2] > 0){
                for(int i = 0; i < s[2]; i++){
                  field[s[0]][s[1]] = pnumsoffield[s[0]][s[1]][i];
                  field = getsolvedfield(field);
                  if(checkfield(field)){return field;}else{field[s[0]][s[1]] = 0;}
                }
              }
            }
            break;
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
        vector<vector<int> > oldfield = field;
        while(true){
          field = getsolvedfield(oldfield);
          if(checkfield(field)){return field;}
        }
}

#endif
