#include <stdio.h>
#include <stdlib.h>

int digitalRoot(long long n)
{
    if (n < 0) n = -n;
    if (n < 10) return (int)n;
    int sum = 0;
    while (n > 0) { sum += (int)(n % 10); n /= 10; }
    return digitalRoot(sum);
}

long long powerLinear(long long base, int n)
{
    if (n == 0) return 1;
    return base * powerLinear(base, n - 1);
}

long long powerFast(long long base, int n)
{
    if (n == 0) return 1;
    long long half = powerFast(base, n / 2);
    long long result = half * half;
    return (n % 2 == 0) ? result : result * base;
}

long long powerIterative(long long base, int n)
{
    long long result = 1;
    while (n > 0) {
        if (n % 2) result *= base;
        base *= base;
        n /= 2;
    }
    return result;
}

int main(void)
{
    printf("Digital root of 98765 = %d\n", digitalRoot(98765));
    printf("2^10 linear = %lld\n", powerLinear(2, 10));
    printf("2^10 fast = %lld\n", powerFast(2, 10));
    printf("2^10 iterative = %lld\n", powerIterative(2, 10));
    printf("Digital root of 0 = %d\n", digitalRoot(0));
    printf("3^0 = %lld; 3^1 = %lld\n", powerFast(3, 0), powerFast(3, 1));
    return 0;
}
