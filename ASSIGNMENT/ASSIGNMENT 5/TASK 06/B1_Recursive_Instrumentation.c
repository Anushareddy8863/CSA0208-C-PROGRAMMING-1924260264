#include <stdio.h>
long long calls;

long long power_linear(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}

long long power_fast(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    long long half = power_fast(base, exp / 2); /* compute only once */
    return (exp % 2 == 0) ? half * half : half * half * base;
}

long long power_iterative(long long base, int exp)
{
    long long result = 1;
    while (exp > 0) {
        if (exp % 2) result *= base;
        base *= base;
        exp /= 2;
    }
    return result;
}

int main(void)
{
    calls = 0;
    printf("linear: %lld in %lld calls\n", power_linear(2, 30), calls);
    /* Evaluation order in printf is unspecified; calculate before printing. */
    calls = 0;
    long long linear = power_linear(2, 30);
    printf("linear verified: %lld in %lld calls\n", linear, calls);

    calls = 0;
    long long fast = power_fast(2, 30);
    printf("fast: %lld in %lld calls\n", fast, calls);

    printf("iterative: %lld\n", power_iterative(2, 30));
    return 0;
}
