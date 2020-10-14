#include <iostream>
#include <iomanip>
#include "Interruption.h"

void Interruption::semantical(int line){
	std::cout << std::setfill('0') << std::setw(2) << line << "Operação inválida" << std::endl;
	exit(1);
}
