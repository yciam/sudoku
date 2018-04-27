///@file cfield.h


#ifndef CFIELD_H
#define CFIELD_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers = {1,2,3,4,5,6,7,8,9};

/**
  @brief checks if sudokuhs are finished

  @param field is the sudoku field

  @returns true if sudokuhs are finished
*/
bool checkh(vector<vector<int>> field){
  for(int i = 0; i < 9; i++){
    sort(field[i].begin(), field[i].end());
    if(field[i] != numbers){return false;}
  }
  return true;
}

/**
  @brief checks if sudokuws are finished

  @param field is the sudoku field

  @returns true if sudokuws are finished
*/
bool checkw(vector<vector<int>> field){
  for(int i = 0; i < 9; i++){
    vector<int> avector;
    for(int a = 0; a < 9; a++){
      avector.push_back(field[a][i]);
    }
    sort(avector.begin(), avector.end());
    if(avector != numbers){return false;}
  }
  return true;
}

/**
  @brief checks if sudokusquares are finished

  @param field is the sudoku field

  @returns true if sudokusquares are finished
*/
bool checks(vector<vector<int>> field){
  for(int i = 0; i < 3; i++){
    for(int a = 0; a < 3; a++){
      vector<int> svector;
      for(int b = 0; b < 3; b++){
        for(int c = 0; c < 3; c++){
          svector.push_back(field[3*i+b][3*a+c]);
        }
      }
      sort(svector.begin(), svector.end());
      if(svector != numbers){return false;}
    }
  }
  return true;
}

/**
  @brief checks if sudoku is finished

  @param field is the sudoku field

  @returns true if sudoku is correct
*/
bool checkfield(vector<vector<int>> field){
  if(checkh(field) && checkw(field) && checks(field)){return true;}else{return false;}
}

#endif
