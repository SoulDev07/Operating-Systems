#include "ComplexNumber.h"

ComplexNumber multiply(ComplexNumber a, ComplexNumber b)
{
    ComplexNumber result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}