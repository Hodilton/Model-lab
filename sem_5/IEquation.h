#pragma once
#ifndef IEQUATION_H
#define IEQUATION_H

#include "./Dependencies/stdafx.h"

class IEquation {
public:
    virtual double evaluate(double x) const = 0;
    virtual double derivativeFirst(double x) const = 0;
    virtual double derivativeSecond(double x) const = 0;
    virtual std::string getStrF() const = 0;

    virtual ~IEquation() = default;
};

#endif // !IEQUATION_H