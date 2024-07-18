#include "IntegerValue.h"

IntegerValue::IntegerValue(int value)
  : Value(Type::IntegerType), m_value(value) {
}

int IntegerValue::value() const {
    return m_value;
}
