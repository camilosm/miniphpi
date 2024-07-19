#include "Interruption.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>

void Interruption::semantical(int line) {
    std::cout << std::setfill('0') << std::setw(2) << line << ": Operação inválida" << std::endl;
    exit(1);
}
