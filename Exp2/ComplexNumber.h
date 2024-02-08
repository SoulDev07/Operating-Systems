// Complex Number Structure
typedef struct ComplexNumber
{
    double real;
    double imag;
} ComplexNumber;

// Function declarations
ComplexNumber add(ComplexNumber a, ComplexNumber b);
ComplexNumber subtract(ComplexNumber a, ComplexNumber b);
ComplexNumber multiply(ComplexNumber a, ComplexNumber b);
ComplexNumber divide(ComplexNumber a, ComplexNumber b);
