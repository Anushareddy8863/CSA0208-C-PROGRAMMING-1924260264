/*
TASK 2 - Data types, limits and rollover
Compile: gcc -std=c11 -Wall -Wextra Task02_DataTypes.c -o task02
*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    /* Conversion to unsigned short performs modulo USHRT_MAX+1 arithmetic. */
    return (unsigned short)(current - previous);
}

int main(void)
{
    printf("sizeof(char)=%zu int=%zu long=%zu long long=%zu\n",
           sizeof(char), sizeof(int), sizeof(long), sizeof(long long));
    printf("sizeof(meter_t)=%zu bytes, maximum reading=%u\n",
           sizeof(meter_t), (unsigned)USHRT_MAX);
    printf("INT_MAX=%d LONG_MAX=%ld LLONG_MAX=%lld\n",
           INT_MAX, LONG_MAX, LLONG_MAX);
    printf("FLT_DIG=%d DBL_DIG=%d\n", FLT_DIG, DBL_DIG);
    printf("Consumption: %u units\n", consumption(1200, 1530));
    printf("Consumption: %u units\n", consumption(65400, 120));

    /* Floating-point illustration: binary floating point cannot represent
       most decimal fractions exactly. Integer paise remains exact. */
    float total_float = 0.0f;
    long long total_paise = 0;
    for (int i = 0; i < 4000; ++i) {
        total_float += 162.50f;
        total_paise += 16250LL;
    }
    printf("4000 bills using float: Rs %.2f\n", total_float);
    printf("4000 bills using paise: Rs %lld.%02lld\n",
           total_paise / 100LL, total_paise % 100LL);
    return 0;
}
