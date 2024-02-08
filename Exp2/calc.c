#include <stdio.h>
#include "ComplexNumber.h"

int main()
{
    int temp1, temp2;

    printf("Enter values of Complex number 1: ");
    scanf("%d %d", &temp1, &temp2);
    ComplexNumber a = {temp1, temp2};
    printf("\nEnter values of Complex number 2: ");
    scanf("%d %d", &temp1, &temp2);
    ComplexNumber b = {temp1, temp2};

    ComplexNumber sum = add(a, b);
    ComplexNumber diff = subtract(a, b);
    ComplexNumber mul = multiply(a, b);
    ComplexNumber div = divide(a, b);

    printf("\n");
    printf("Sum: %.2f + %.2fi\n", sum.real, sum.imag);
    printf("Difference: %.2f + %.2fi\n", diff.real, diff.imag);
    printf("Product: %.2f + %.2fi\n", mul.real, mul.imag);
    printf("Quotient: %.2f + %.2fi\n", div.real, div.imag);
    return 0;
}
