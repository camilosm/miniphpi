#ifndef INTERRUPTION_H
#define INTERRUPTION_H

#include <cstdlib>
#include <iomanip>
#include <iostream>

class Interruption {
    public:
        static void semantical(int line) {
            std::cout << std::setfill('0') << std::setw(2) << line << ": Operação inválida" << std::endl;
            std::exit(1);
        }
};

#endif // INTERRUPTION_H
