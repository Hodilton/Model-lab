#ifndef TASK_1_VALUE_CPP
#define TASK_1_VALUE_CPP

#include "Value.h"

template <typename T>
Value<T>::Value()
    : value(T()), absoluteError(0), relativeError(0) {}
template <typename T>
Value<T>::Value(T value, double absErr, double relErr)
    : value(value), absoluteError(absErr), relativeError(relErr) { calcAbsoluteError(); }

template<typename T>
void Value<T>::calcAbsoluteError() {
    value == 0
        //? throw std::runtime_error("Division by zero")
        ? 0
        : absoluteError = relativeError / std::abs(value);
}

template<typename T>
void Value<T>::calcRelatError() {
    value == 0
        //? throw std::runtime_error("Division by zero")
        ? 0
        : relativeError = absoluteError / std::abs(value);
}

template<typename T>
Value<T> Value<T>::operator+(const Value& other) {
    Value<T> temp(
        this->value + other.value,
        0,
        this->absoluteError + other.absoluteError);

    temp.calcAbsoluteError();

    return temp;
}

template<typename T>
Value<T> Value<T>::operator-(const Value& other) {
    Value<T> temp(
        this->value - other.value,
        0,
        this->absoluteError + other.absoluteError);

    temp.calcAbsoluteError();

    return temp;
}

template<typename T>
Value<T> Value<T>::operator*(const Value& other) {
    Value<T> temp(
        this->value * other.value,
        0,
        this->relativeError + other.relativeError);

    temp.calcAbsoluteError();

    return temp;
}

template<typename T>
Value<T> Value<T>::operator/(const Value& other) {
    Value<T> temp(
        (other.value == 0
            ? throw std::runtime_error("Division by zero")
            : this->value / other.value),
        0,
        this->relativeError + other.relativeError);

    temp.calcAbsoluteError();

    return temp;
}

//template <typename T> T Value<T>::getValue() const { return value; }
//template <typename T> double Value<T>::getAbsoluteError() const { return absoluteError; }
//template <typename T> double Value<T>::getRelativeError() const { return relativeError; }

#endif // !TASK_1_VALUE_CPP