#include <iostream>
#include <bitset>
#include <array>
#include "gfield.h"
#include "sfield.h"

using namespace std;

void draw(array<array<bitset<9>,9>,9> field){
  cout  << endl;
  for(int i = 0; i < 9; i++){
    cout << "| ";
    for(int a = 0; a < 9; a++){
      cout << field[i][a] << " ";
      if((a+1) % 3 == 0) cout << "| ";
      if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << endl;};
    }
  }
}

int main(int argc, char const *argv[]) {
  array<array<bitset<9>,9>,9> field;
  field = generatefield(field);
  draw(field);
  if(field[1][1] == 010000000){cout << "t" << endl;}else{cout << field[1][1] << endl;}
  //field = solvefield(field);
  draw(field);
  while(true){}
  return 0;
}
