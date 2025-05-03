#ifndef LIBCLIMENU_HPP
#define LIBCLIMENU_HPP
#include <string>
#include <vector>

namespace libclimenu {
    class Menu {
        public:
            std::string name;
            std::string version;
            std::vector<std::string> options;
            Menu(std::string name, std::string version, std::vector<std::string> options);
            // you'll have to print the logo yourself
            //
            // use something like hit font or big font generator
            //
            // (the options start at 1 once printed)
            void printAndGetInput(int &optionInt, bool printName);
    };
    void clear();
    void sep();
    void error(std::string info);
}

#endif // LIBCLIMENU_HPP
// (no compile)