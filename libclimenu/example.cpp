#include "libclimenu.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

int main() {
    libclimenu::Menu menu("libclimenu example", "1.0", {"print random number", "print something"});
    libclimenu::clear();
    bool toBreak = 0;
    while (!toBreak) {
        srand(time(nullptr));
        int menuOp;
        menu.printAndGetInput(menuOp, true);
        switch (menuOp) {
            case 0: {
                libclimenu::clear();
                toBreak = 1;
                break;
            }
            case 1: {
                libclimenu::clear();
                int minN;
                int maxN;
                cout << "min number: ";
                cin >> minN;
                cout << "max number: ";
                cin >> maxN;
                libclimenu::clear();
                cout << "your number is: " << rand() % maxN + minN << "\n";
                libclimenu::sep();
                break;
            }
            case 2: {
                libclimenu::clear();
                cin.ignore();
                string toPrint;
                cout << "text to print: ";
                getline(cin, toPrint);
                libclimenu::clear();
                cout << "you typed: " << toPrint << "\n";
                libclimenu::sep();
                break;
            }
            default: {
                libclimenu::clear();
                libclimenu::error("no option made for input " + to_string(menuOp));
                libclimenu::sep();
                break;
            }
        }
    }
    return 0;
}
// linux: g++ example.cpp -o example ./libclimenu.so
// windows: g++ example.cpp -o example.exe ./libclimenu.dll