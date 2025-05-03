#ifndef LIBCLIMENU_HPP
#define LIBCLIMENU_HPP
#include <string>
#include <vector>

namespace libclimenu {
    //contains information about your menu
    class Menu {
        public:
        //name of the menu
        std::string name;
        // version of the menu
        std::string version;
        // options of the menu
        std::vector<std::string> options;
        // menu configurator/constructor
        Menu(std::string name, std::string version, std::vector<std::string> options);
        /*print the main menu and get user input and put it
        on `optionInt`
        `bool printName`: if 1, print the name of the app defined
        in your `libclimenu::Menu.name` and version in `libclimenu::Menu.version`
        
        else, don't print the name and version of the app*/
        void printAndGetInput(int &optionInt, bool printName);
    };
    //clear the screen for the next operation
    void clear();
    //seperate the screen by exactly 75 hyphens
    void sep();
    /*print an error incase of input invalidation or something
    else*/
    void error(std::string info);
}

#endif // LIBCLIMENU_HPP
// (no compile)