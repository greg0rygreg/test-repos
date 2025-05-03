#include "libclimenu.hpp"
#include <iostream>

namespace libclimenu {
    Menu::Menu(std::string name, std::string version, std::vector<std::string> options) {
        this->name = name;
        this->version = version;
        this->options = options;
    }
    void Menu::printAndGetInput(int &optionInt, bool printName) {
        if (printName) {
            std::cout << this->name << " v" << this->version << "\n";
        }
        for (int i = 0; i < this->options.size(); i++) {
            std::cout << "(" << i+1 << ") " << this->options[i] << "\n";
        }
        std::cout << "(0) exit\n";
        std::cout << "\n(?) >> ";
        std::cin >> optionInt;
    }
    void clear() {
        std::cout << "\x1b[2J\x1b[H";
    }
    void sep() {
        std::cout << std::string(75, '-') << "\n";
    }
    void error(std::string info) {
        std::cout << "\x1b[1;31merror:\x1b[0m " << info << "\n";
    }
    void warning(std::string info) {
        std::cout << "\x1b[1;33mwarning:\x1b[0m " << info << "\n";
    }
}
// linux: g++ libclimenu.cpp -fPIC -shared -o libclimenu.so
// windows: g++ libclimenu.cpp -fPIC -shared -o libclimenu.dll