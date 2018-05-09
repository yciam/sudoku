///@file gfield.h

#ifndef GFIELD_H
#define GFIELD_H

#include <vector>
#include <array>
#include "sfield.h"
#include <list>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

/**
  @brief will check if there are any Zeros in your field

  @param field is the field you wanna check

  @returns true only if there are no Zeros 
*/
bool nozero(array<array<uint16_t,9>,9> field){
        for(int i = 0; i < 9; i++) {
                for(int a = 0; a < 9; a++) {
                        if(field[i][a] == 0) return false;
                }
        }
        return true;
}

/**
   @brief generates a sudoku field

   @param difficulty is the difficulty

   @returns the sudoku field
*/
array<array<uint16_t,9>,9> generatefield(int difficulty){
        if(difficulty > 52) { //64 should be the limit, but sadly it takes to long
                cout << "difficulty to high" << endl;
                while(true) {}
        }

        array<array<uint16_t,9>,9> field;
        srand(time(NULL));
        for(;; ) {
                for(;; ) {

                        for(int i = 0; i < 9; i++) {
                                for(int a = 0; a < 9; a++) {
                                        field[i][a] = 511;
                                }
                        }

                        for(int i = 0; i < 9; i++) {
                                for(int a = 0; a < 9; a++) {
                                        field = removeobvious(field);
                                        for(;;) {
                                                uint16_t z = rand() % 9;
                                                if(((field[i][a] >> z) & 1)) {field[i][a] = 1 << z; break; }
                                                if(field[i][a] == 0){break;}
                                        }
                                }
                        }

                        if(nozero(field)) break;
                }

                array<array<uint16_t,9>,9> oldfield = field;
                for(int i = 0; i < difficulty; i++) {
                  int a = rand() % 9, b = rand() % 9;
                        if(field[a][b] != 511){field[a][b] = 511;}else{i--;}
                }
                if(oldfield == solvefield(field)) {return field; }
        }
}
#endif
