#ifndef INTEGER_VALUE_H
#define INTEGER_VALUE_H

#include "Value.h"

class IntegerValue : public Value<int> {
    public:
        IntegerValue(int value);

        int value() const;

    private:
        int m_value;
};

#endif
