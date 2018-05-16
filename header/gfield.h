///@file gfield.h

#ifndef GFIELD_H
#define GFIELD_H

#include <array>
#include "sfield.h"
#include <iostream>
#include <thread>

using namespace std;

/**
   @brief draws the Sudoku field

   @param field is your Sudoku Field
 */
void draw(array<array<uint16_t,9>,9> field){
        system("clear");
        cout << endl;
        for(int i = 0; i < 9; i++) {
                cout << "| ";
                for(int a = 0; a < 9; a++) {
                        cout << exactnumber(field[i][a])+1 << " ";
                        if((a+1) % 3 == 0) cout << "| ";
                        if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << endl; };
                }
        }
}

/**
   @brief returns the posithion of the nth high bit

   @param position is the position of the High bit you want if you only count High Bits
   @param number is the number you wanna Analyse

   @returns the postion of the nth High Bit
 */
uint8_t positionof(uint8_t position, uint16_t number){
        uint8_t NumberOfHighBits = 0;
        for(int i = 0;; i++) {
                if(((number >> i) & 1)) {
                        NumberOfHighBits++;
                        if(position == NumberOfHighBits) return i;
                }
        }
}

/**
   @brief will return the number of high bits

   @param i is obvious

   @returns the number of High Bits
 */
int countHighBits(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

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
        if(difficulty > 55) { //64 should be the limit, but sadly it takes to long
                cout << "difficulty to high" << endl;
                while(true) {}
        }

        array<array<uint16_t,9>,9> field;
        array<array<uint16_t,9>,9> rfield;
        array<array<uint16_t,9>,9> sfield;
        for(int i = 0; i < 9; i++) {
                for(int a = 0; a < 9; a++) {
                        field[i][a] = 511;
                        rfield[i][a] = 511;
                        sfield[i][a] = 511;
                }
        }

        for(int i = 0; i < 9; i++) {
                for(int a = 0; a < 9; a++) {
                        rfield = field;
                        rfield = removeobvious(field);
                        if(rfield[i][a] != 0) {
                          field[i][a] = 1 << positionof(rand() % countHighBits(rfield[i][a]), rfield[i][a]);
                        }else{
                                for(;;){
                                  field[i][a] = 511;
                                        if(a == 0) {if(i > 0) {i--; a = 8; }else{a = 0;}}else{a--; }
                                        field[i][a] = 511;
                                        field[i][a] &= ~(1 << exactnumber(field[i][a]));
                                        field[i][a] = removeobvious(field)[i][a];
                                        if(countHighBits(field[i][a]) > 2){break;}
                                }
                                if(a == 0) {if(i > 0) {i--; a = 8; }else{a = 0;}}else{a--; }
                                field[i][a] = 511;
                                field[i][a] = removeobvious(field)[i][a];
                                field[i][a] &= ~(1 << exactnumber(field[i][a]));
                                if(a == 0) {if(i > 0) {i--; a = 8; }else{a = 0;}}else{a--; }
                        }
                }
        }

        array<array<uint16_t,9>,9> oldfield = field;
        for(;; ) {
                for(int i = 0; i < difficulty; i++) {
                        int a = rand() % 9, b = rand() % 9;
                        if(field[a][b] != 511) {field[a][b] = 511; }else{i--; }
                }
                if(oldfield == solvefield(field) && nozero(field)) {return field; }else{field = oldfield; }
                if(!nozero(field)){draw(field); while(true){}}
        }
}
#endif
