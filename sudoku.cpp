#include <iostream>
#include <array>
#include "header/gfield.h"
#include "header/sfield.h"
#include <map>
#include <chrono>

#define DIFFICULTY 20

using namespace std;



/**
  @brief draws the Sudoku field

  @param field is your Sudoku Field
*/
void draw(array<array<uint16_t,9>,9> field){
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

int main(int argc, char const *argv[]) {
  auto begin = std::chrono::high_resolution_clock::now();
  array<array<uint16_t,9>,9> field;
  field = generatefield(DIFFICULTY);
  draw(field);
  field = solvefield(field);
  draw(field);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " microseconds" << std::endl;
  while(true){}
  return 0;
}
