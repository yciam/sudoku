#include <iostream>
#include <array>
#include "header/gfield.h"
#include "header/sfield.h"
#include <chrono>

/**
   @mainpage sudoku

   @todo Make everything better
 */

using namespace std;

int main(int argc, char const *argv[]) {
        srand(time(NULL));
        array<array<uint16_t,9>,9> field, solvedfield;
        cout << "Enter A difficulty Level between 1 and 55!" << endl;
        int difficulty = 0;
        //cin >> difficulty;
        field = generatefield(difficulty);
        solvedfield = solvefield(field);
        /**
        while(field != solvedfield) {
            int i, a, s;
            draw(field);
            cout << "Enter the Row:" << endl;
            cin >> i;
            cout << "Enter the Column:" << endl;
            cin >> a;
            cout << "Enter the Solution:" << endl;
            cin >> s;
            i--; a--;
            if(exactnumber(solvedfield[i][a])+1 == s){field[i][a] = 1 << (s-1);}else{
              cout << "That was Wrong!" << endl << endl << "Do you need some Help?" << endl;
              string t;
              cin >> t;
              if(t == "yes" || t == "Yes"){field[i][a] = solvedfield[i][a];}
            }
        }
        */
        draw(field);
        cout << "You solved the Sudoku!" << endl;
        cin.ignore().get();
        return 0;
}
