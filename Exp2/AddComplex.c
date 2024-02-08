#include "ComplexNumber.h"

ComplexNumber add(ComplexNumber a, ComplexNumber b)
{
    ComplexNumber result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}
