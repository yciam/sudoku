#ifndef SFIELD_H
#define SFIELD_H

#include <array>
#include <bitset>
#include <iostream>

using namespace std;

int exactnumber(uint16_t fnum){
  for(uint8_t i = 0; i < 9; i++){
    uint16_t num = 0;
    num |= 1 << i;
    if(fnum == num){return i;}
  }
  return -1;
}

array<array<uint16_t,9>,9> removeobvious(array<array<uint16_t,9>,9> field){
  for(uint8_t i = 0; i < 9; i++){
    for(uint8_t a = 0; a < 9; a++){
      uint8_t num = exactnumber(field[i][a]);
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

array<array<uint16_t,9>,9> solvefield(array<array<uint16_t,9>,9> field){
  array<array<uint16_t,9>,9> oldfield;
  do{
    oldfield = field;
    field = removeobvious(field);
  }while(oldfield != field);
  return field;
}

#endif
