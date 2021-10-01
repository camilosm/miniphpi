#include "Memory.h"

std::map<std::string, Type*> Memory::m_memory;

Type* Memory::read(const std::string& name) {
	Type* value = Memory::m_memory[name];

	if(!value){
		value = new StringValue("");
		write(name, value);
	}
	return value;
}

void Memory::write(const std::string& name, Type* value) {
	Memory::m_memory[name] = value;
}
