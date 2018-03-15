#ifndef SFIELD_H
#define SFIELD_H

#include <vector>
#include <iostream>

using namespace std;

/**
  @brief removes the impossible numbers from pnumsoffield

  @param pnumsoffield the possible numbers of the field
  @param field is the sudoku field
  @param a is the first coordinate from the field you wanna clear;
  @param b is the seccond coordinate from the field you wanna clear;

  @returns pnumsoffield
*/
vector<vector<vector<int>>> cleardoubles(vector<vector<vector<int>>> pnumsoffield,vector<vector<int>> field, int a, int b){
  if(pnumsoffield[a][b].size() > 1){
  vector<int> h; vector<int> v; vector<int> s;
  for(int i = 0; i < 9; i++){
    h.push_back(field[a][i]);
    v.push_back(field[i][b]);
  }
  int oa = a, ob = b;
  if(a < 3){a = 0;}else if(a < 6){a = 3;}else{a = 6;}
  if(b < 3){b = 0;}else if(b < 6){b = 3;}else{b = 6;}
  for(int d = 0; d < 3; d++){
    for(int c = 0; c < 3; c++){
      s.push_back(field[a+c][b+d]);
    }
  }
  vector<vector<int>> hvs = {h,v,s};
  for(y:hvs){
    for(x:y){
      for(int i = 0; i < pnumsoffield[oa][ob].size(); i++){
        if(pnumsoffield[oa][ob][i] == x){
          pnumsoffield[oa][ob].erase(pnumsoffield[oa][ob].begin()+i);
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
vector<vector<vector<int>>> getpnumsoffield(vector<vector<int>> field){
  vector<vector<vector<int>>> pnumsoffield = {{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0},{0},{0},{0},{0}}};;
  for(int i = 0; i < 9; i++){
    for(int a = 0; a < 9; a++){
      if(field[i][a] == 0){
        pnumsoffield[i][a] = {1,2,3,4,5,6,7,8,9};
      }else{
        pnumsoffield[i][a].push_back(field[i][a]);
      }
    }
  }
  return pnumsoffield;
}

/**
  @brief Solves the sudoku

  @param field is the sudoku field

  @returns the solved field
*/
vector<vector<int>> solvefield(vector<vector<int>> field){
  vector<vector<vector<int>>> pnumsoffield;
  pnumsoffield = getpnumsoffield(field);
  for(int a = 0; a < 9; a++){
    for(int b = 0; b < 9; b++){
      cout << a << " " << b << endl;
      pnumsoffield = cleardoubles(pnumsoffield, field,a,b);
    }
  }

  return field;
}

#endif
