#include <iostream>
#include "libclimenu.hpp"
using namespace libclimenu;
int main() {
    Menu menu("libclimenu submenu example", "1.0", {"submenu 1", "submenu 2", "info"}, "exit");
    Menu submenu1("", "", {"test 1", "test 2"}, "back to main menu");
    Menu submenu2("", "", {"test 3", "test 4"}, "back to main menu");
    int toBreak;
    clear();
    while(true) {
        int menuOp;
        toBreak = 0;
        menu.printAndGetInput(menuOp, 1);
        switch (menuOp) {
            case 1: {
                clear();
                while (!toBreak){
                    int submenu1Op;
                    std::cout << "submenu 1:\n";
                    submenu1.printAndGetInput(submenu1Op, 0);
                    switch (submenu1Op) {
                        case 1: {
                            clear();
                            std::cout << "hello world 1\n";
                            sep();
                            break;
                        }
                        case 2: {
                            clear();
                            std::cout << "hello world 2\n";
                            sep();
                            break;
                        }
                        case 0: {
                            toBreak = 1;
                            break;
                        }
                        default: {
                            clear();
                            error("no option made for input " + std::to_string(menuOp));
                            sep();
                            break;
                        }
                    }
                }
            }
            case 2: {
                clear();
                while (!toBreak){
                    int submenu2Op;
                    std::cout << "submenu 2:\n";
                    submenu1.printAndGetInput(submenu2Op, 0);
                    switch (submenu2Op) {
                        case 1: {
                            clear();
                            std::cout << "hello world 3\n";
                            sep();
                            break;
                        }
                        case 2: {
                            clear();
                            std::cout << "hello world 4\n";
                            sep();
                            break;
                        }
                        case 0: {
                            toBreak = 1;
                            break;
                        }
                        default: {
                            clear();
                            error("no option made for input " + std::to_string(menuOp));
                            sep();
                            break;
                        }
                    }
                }
            }
            case 3: {
                clear();
                std::cout << menu.getFormattedVersion() << "\n"
                << "licensed under MIT license\n"
                << "this project comes from greg0rygreg/test-repos on github,\n"
                << "because it is not big enough to have its own repo\n";
                sep();
                break;
            }
            case 0: {
                clear();
                exit(0);
                break;
            }
            default: {
                clear();
                error("no option made for input " + std::to_string(menuOp));
                sep();
                break;
            }
        }
    }
    return 0;
}