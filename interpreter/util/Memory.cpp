#include "Memory.h"

std::map<std::string, Type*> Memory::m_memory;

Type* Memory::read(const std::string& name) {
	return Memory::m_memory[name];
}

void Memory::write(const std::string& name, Type* value) {
	Memory::m_memory[name] = value;
}
