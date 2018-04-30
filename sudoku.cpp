#include <iostream>
#include <array>
#include <bitset> //sorry
#include "gfield.h"
#include "sfield.h"

using namespace std;

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
  array<array<uint16_t,9>,9> field;
  field = generatefield(field);
  draw(field);
  field = solvefield(field);
  draw(field);
  while(true){}
  return 0;
}
