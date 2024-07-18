#ifndef ARRAY_VALUE_H
#define ARRAY_VALUE_H

#include <map>
#include <string>

#include "Value.h"

class Type;

class ArrayValue : public Value<std::map<std::string, Type*>> {
    public:
        ArrayValue(const std::map<std::string, Type*>& value);
        virtual ~ArrayValue();

        std::map<std::string, Type*> value() const;

    private:
        std::map<std::string, Type*> m_value;
};

#endif
