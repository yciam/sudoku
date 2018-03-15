#ifndef SFIELD_H
#define SFIELD_H

#include <vector>

using namespace std;

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


  return field;
}

#endif
