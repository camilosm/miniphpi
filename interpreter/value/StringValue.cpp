#include "StringValue.h"

StringValue::StringValue(std::string value)
  : Value(Type::StringType), m_value(value) {
}

std::string StringValue::value() const {
    return m_value;
}
