#ifndef GFIELD_H
#define GFIELD_H

#include <vector>
#include <array>
#include "sfield.h"
#include <list>
#include <iostream>
#include <map>


using namespace std;

int counter = 0;

void ddraw(array<array<uint16_t,9>,9> field){
  map<int, int> intmap;
  intmap[1] = 1;intmap[2] = 2;intmap[4] = 3;intmap[8] = 4;intmap[16] = 5;intmap[32] = 6;intmap[64] = 7;intmap[128] = 8;intmap[256] = 9;
  cout  << endl;
  for(int i = 0; i < 9; i++){
    cout << "| ";
    for(int a = 0; a < 9; a++){
      cout << intmap[(int)field[i][a]] << " ";
      if((a+1) % 3 == 0) cout << "| ";
      if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << endl;};
    }
  }
}

bool findthemistake(array<array<uint16_t,9>,9> field){
  for(uint i = 0; i < 9; i++){
    list<uint16_t> l(0); uint end = 0;
    l.clear();
    for(uint a = 0; a < 9; a++){
      if(field[i][a] == 0){break;}
      l.push_back(field[i][a]);
      end++;
    }
    l.unique();
    if(l.size() != end){cout << l.size() << " f " << end << endl; return false;}else{for(s:l){cout << s;} cout << endl << l.size() << " " << end << endl;}
  }
  return true;
}

/**
  @brief generates a sudoku field

  @param difficulty is the difficulty

  @returns the sudoku field
*/
array<array<uint16_t,9>,9> generatefield(int difficulty){
  array<array<uint16_t,9>,9> field;
    for(int i = 0; i < 9; i++){
      for(int a = 0; a < 9; a++){
        field[i][a] = 511;
      }
    }
    srand(time(NULL));
    for(int i = 0; i < 9; i++){
      for(int a = 0; a < 9; a++){
        field = removeobvious(field);
        ddraw(field);
        while(true){
          uint16_t z = rand() % 9;
          if(((field[i][a] >> z) & 1)){field[i][a] = 0; field[i][a] |= 1 << z; break;}
        }
      }
    }

    return field;
}
#endif
