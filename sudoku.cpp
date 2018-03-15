#include <iostream>
#include <vector>
#include "gfield.h"
#include "cfield.h"
#include "sfield.h"

using namespace std;

/**
  @brief draws the field

  @param field you play on
*/
void draw(vector<vector<int>> field){
  cout << "-------------------------" << endl;
  for(int i = 0; i < 9; i++){
    cout << "| ";
    for(int a = 0; a < 9; a++){
      cout << field[i][a] << " ";
      if((a+1) % 3 == 0) cout << "| ";
      if(a == 8) {cout << endl; if((i+1) % 3 == 0) cout << "-------------------------" << endl;};
    }
  }
}

int main(int argc, char const *argv[]) {
  vector<vector<int>> field ={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,},{0,0,0,0,0,0,0,0,0,},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  field = generatefield(3, field);
  draw(field);
  field = solvefield(field);
  draw(field);
  if(checkfield(field)){cout << "SOLVED!" << endl;}
  while (true) {}
  return 0;
}
