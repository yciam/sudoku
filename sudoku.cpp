#include <iostream>
#include <array>
#include <bitset> //sorry
#include "gfield.h"
#include "sfield.h"
#include <map>

using namespace std;

map<int, int> intmap;

void drawexact(array<array<uint16_t,9>,9> field){
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

void draw(array<array<uint16_t,9>,9> field){
  cout  << endl;
  for(int i = 0; i < 9; i++){
    cout << "| ";
    for(int a = 0; a < 9; a++){
      cout << bitset<16>(field[i][a]) << " ";
      if((a+1) % 3 == 0) cout << "| ";
      if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << endl;};
    }
  }
}

int main(int argc, char const *argv[]) {
  intmap[1] = 1;intmap[2] = 2;intmap[4] = 3;intmap[8] = 4;intmap[16] = 5;intmap[32] = 6;intmap[64] = 7;intmap[128] = 8;intmap[256] = 9;
  array<array<uint16_t,9>,9> field;
  field = generatefield(field);
  draw(field);
  field = solvefield(field);
  draw(field);
  drawexact(field);
  while(true){}
  return 0;
}
