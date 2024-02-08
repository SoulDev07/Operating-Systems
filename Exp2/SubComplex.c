#include "ComplexNumber.h"

ComplexNumber subtract(ComplexNumber a, ComplexNumber b)
{
    ComplexNumber result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}
