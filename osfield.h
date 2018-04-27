///@file osfield.h


#ifndef OSFIELD_H
#define OSFIELD_H

#include <vector>
#include "cfield.h"
#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <condition_variable>
#include <mutex>
#include <atomic>

using namespace std;

static std::condition_variable finished;
std::mutex mtx;
vector<vector<int>> solvedfield;

/**
  @brief sometimes you have to remove a number from a vector

  @param vec is the vector you want to change
  @param a is the number you want to remove from the vector

  @returns a vector which does not contain a
*/
vector<int> removefromvector(vector<int> vec, int a){
        for(unsigned int i = 0; i < vec.size(); i++) {
                if(vec[i] == a) {
                        vec.erase(vec.begin()+i);
                        return removefromvector(vec,a);
                }
        }
        return vec;
}

/**
  @brief with this you can get the possible numbers for a field in the sudoku field

  @param  field is the field you want to solve
  @param i is one of the coordinates from the sudoku field
  @param a is one of the coordinates from the sudoku field

  @returns a vector with all possible numbers for that field
*/
vector<int> getposibilities(vector<vector<int> > field, int i, int a){
        vector<int> posibilities = {1,2,3,4,5,6,7,8,9};
        for(int b = 0; b < 9; b++) {
                if(field[i][b] != 0) {posibilities = removefromvector(posibilities,field[i][b]); }
                if(field[b][a] != 0) {posibilities = removefromvector(posibilities,field[b][a]); }
        }
        int s1, s2;
        if(i < 3) {s1 = 0; }else if(i < 6) {s1 = 3; }else{s1 = 6; }
        if(a < 3) {s2 = 0; }else if(a < 6) {s2 = 3; }else{s2 = 6; }                                        for(int c = 0; c < 3; c++) {
                for(int d = 0; d < 3; d++) {
                        if(field[c+s1][d+s2] != 0) {posibilities = removefromvector(posibilities,field[c+s1][d+s2]); }
                }
        }
        return posibilities;
}

/**
  @brief fills in the obvious numbers

  @param field is the field you want to solve

  @returns the field without the obvious numbers
*/
vector<vector<int> > removeobvious(vector<vector<int> > field){ // this works fine
        vector<vector<int> > oldfield = field;
        do {
                oldfield = field;
                for(int i = 0; i < 9; i++) {
                        for(int a = 0; a < 9; a++) {
                                if(field[i][a] == 0) {
                                        vector<int> posibilities = getposibilities(field, i, a);
                                        if(posibilities.size() == 1) {field[i][a] = posibilities[0]; }
                                }
                        }
                }
        } while(field != oldfield);

        return field;
}

/**
  @brief i want it to solve the sudoku

  @param argument is the field you want to solve
*/
void* getsolvedfield(void* argument){
        vector<vector<int> > field = *((vector<vector<int> >*)argument);
        field = removeobvious(field);
        if(checkfield(field)){solvedfield = field; finished.notify_one(); pthread_exit(NULL);} //if solved this will end everything
        for(int i = 0; i < 9; i++) { // go throught all fields
                for(int a = 0; a < 9; a++) {
                        if(field[i][a] == 0) { // if a field equals 0 it has to be filled
                          vector<int> pos = getposibilities(field,i,a);
                          for(int p:pos){
                            field[i][a] = p; // fill in all possibilities
                            getsolvedfield((void*)&field); //call the function again until it has solved it. unfortunately that does not work right now
                            field[i][a] = 0;
                          }
                        }
                }
        }
}

/**
  @brief calls getsolvedfield and waits until the sudoku is solved

  @param field is the field you want to solve

  @returns the solved field
*/
vector<vector<int> > solvefield(vector<vector<int> > field){
        pthread_t t1;
        pthread_create(&t1,NULL,getsolvedfield,(void*)&field);
        std::unique_lock<std::mutex> ml (mtx);
        while(true){
          finished.wait(ml); // waits until a solution is found
            return solvedfield;
        }
}

#endif
