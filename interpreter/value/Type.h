#ifndef TYPE_H
#define TYPE_H

class Type {
    public:
        enum ValueType {
            IntegerType,
            StringType,
            ArrayType
        };

        Type(ValueType type) : m_type(type) {}

        ValueType type() const { return m_type; }

    private:
        ValueType m_type;
};

#endif
