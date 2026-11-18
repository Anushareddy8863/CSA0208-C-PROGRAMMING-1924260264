/*
TASK 5 - Header file and conditional debugging
Compile normal: gcc -std=c11 -Wall -Wextra Task05_HeaderDebug.c -o task05
Compile debug:  gcc -std=c11 -Wall -Wextra -DDEBUG Task05_HeaderDebug.c -o task05
*/
#include <stdio.h>
#include "billing.h"

long long compute_bill(int units)
{
    if (units < 0) return 0LL;
    long long energy = 0LL;
    if (units > SLAB1_UNITS)
        energy += (long long)(units < SLAB2_UNITS ? units - SLAB1_UNITS :
                              SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE;
    if (units > SLAB2_UNITS)
        energy += (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] units=%d energy_paise=%lld\n", units, energy);
#endif
    return FIXED_CHARGE_PAISE + energy;
}

int main(void)
{
    int units = 350;
    long long bill = compute_bill(units);
    printf("Bill for %d units = Rs %lld.%02lld\n",
           units, bill / 100LL, bill % 100LL);
    return 0;
}
