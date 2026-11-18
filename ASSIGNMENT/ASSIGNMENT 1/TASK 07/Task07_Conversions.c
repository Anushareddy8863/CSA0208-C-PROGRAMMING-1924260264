/*
TASK 7 - Type conversion and precision demonstrations
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("Surprise 1: 5/2 = %d (integer division discards .5)\n", 5 / 2);
    printf("Fix: 5.0/2 = %.1f\n", 5.0 / 2);
    printf("Surprise 2: (double)(5/2) = %.1f\n", (double)(5 / 2));
    printf("Fix: (double)5/2 = %.1f\n", (double)5 / 2);
    printf("Surprise 3: (int)3.99 = %d (fraction truncated)\n", (int)3.99);
    printf("Rounding to nearest paise: %.0f paise\n", 225.5);

    long large = (long)INT_MAX + 100L;
    printf("A long value can exceed INT_MAX: %ld; casting to int is unsafe.\n",
           large);
    puts("Use long long for accumulated paise; round fractional tariff charges");
    puts("once per charge using a documented rule, then store integer paise.");
    return 0;
}
