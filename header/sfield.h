#ifndef SFIELD_H
#define SFIELD_H

#include <array>

using namespace std;

/**
  @brief used to get the exact number of a field if there is only one possibility

  @param fnum is the number you wanna check

  @returns the number of a field if there is only one possibility
*/
int exactnumber(uint16_t fnum){
  for(uint8_t i = 0; i < 9; i++){
    uint16_t num = 0;
    num |= 1 << i;
    if(fnum == num){return i;}
  }
  return -1;
}

/**
  @brief removes the already used fields from the other possibilitys of the fields

  @param field is the sudoku field you wanna solve

  @returns the better field
*/
array<array<uint16_t,9>,9> removeobvious(array<array<uint16_t,9>,9> field){
  for(uint8_t i = 0; i < 9; i++){
    for(uint8_t a = 0; a < 9; a++){
      int8_t num = exactnumber(field[i][a]);
      if(num != -1){
        for(uint8_t b = 0; b < 9; b++){
          field[i][b] &= ~(1 << num);
          field[b][a] &= ~(1 << num);
        }
        uint8_t s1, s2;
        if(i < 3) {s1 = 0; }else if(i < 6) {s1 = 3; }else{s1 = 6; }
        if(a < 3) {s2 = 0; }else if(a < 6) {s2 = 3; }else{s2 = 6; }
        for(uint8_t c = 0; c < 3; c++) {
                for(uint8_t d = 0; d < 3; d++) {
                      field[c+s1][d+s2] &= ~(1 << num);
                }
        }
        field[i][a] |= 1 << num;
      }
    }
  }
  return field;
}

/**
  @brief removes the other possibilitys if one of the possibilitys is the only option

  @param field is the sudoku field you wanna solve

  @returns the better field
*/
array<array<uint16_t,9>,9> removenotsoobvious(array<array<uint16_t,9>,9> field){
  for(uint8_t i = 0; i < 9; i++){
    for(uint8_t a = 0; a < 9; a++){
      if(exactnumber(field[i][a]) == -1){
        for(uint8_t b = 0; b < 9; b++){
          if((field[i][a] >> b) & 1){
            field[i][a] &= ~(1 << b);
            bool p1 = true, p2 = true, p3 = true;
            for(uint8_t c = 0; c < 9; c++){
              if(((field[i][c] >> b) & 1)) p1 = false;
              if(((field[c][a] >> b) & 1)) p2 = false;
            }
            uint8_t s1, s2;
            if(i < 3) {s1 = 0; }else if(i < 6) {s1 = 3; }else{s1 = 6; }
            if(a < 3) {s2 = 0; }else if(a < 6) {s2 = 3; }else{s2 = 6; }
            for(uint8_t c = 0; c < 3; c++) {
                    for(uint8_t d = 0; d < 3; d++) {
                          if(((field[c+s1][d+s2] >> b) & 1)) p3 = false;
                    }
            }
            if(p1 || p2 || p3){field[i][a] = 0; field[i][a] |= 1 << b;}else{field[i][a] |= 1 << b;}
          }
        }
      }
    }
  }
  return field;
}

/**
  @brief calls removeobvious and removenotsoobvious until the sudoku is solved

  @param field is the sudoku field you wanna solve

  @returns the solved field
*/
array<array<uint16_t,9>,9> solvefield(array<array<uint16_t,9>,9> field){
  array<array<uint16_t,9>,9> oldfield;
  do{
    oldfield = field;
    field = removeobvious(field);
    field = removenotsoobvious(field);
  }while(oldfield != field);
  return field;
}

#endif
