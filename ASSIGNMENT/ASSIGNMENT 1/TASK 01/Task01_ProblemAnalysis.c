/*
TASK 1 - Problem analysis and data identification
Compile: gcc -std=c11 -Wall -Wextra Task01_ProblemAnalysis.c -o task01
Run:     ./task01
*/
#include <stdio.h>

int main(void)
{
    /* Inputs: household ID, category, previous and current meter readings.
       Outputs: units consumed, slab energy charge, fixed charge, total bill.
       Tariff values are fixed for one run and should be defined centrally.
       Meter values are 0..65535. Paise is used for exact money arithmetic. */
    const long fixed_charge_paise = 5000L;
    const int slab1_limit = 100;
    const int slab2_limit = 200;
    const int rate1_paise = 0;
    const int rate2_paise = 225;
    const int rate3_paise = 450;

    unsigned int previous = 1200U, current = 1530U;
    unsigned int units = current - previous; /* normal non-rollover example */
    long energy_paise = 0L;

    if (units > (unsigned)slab1_limit)
        energy_paise += (long)(units - (unsigned)slab1_limit) *
                        (long)rate2_paise;
    if (units > (unsigned)slab2_limit)
        energy_paise += (long)(units - (unsigned)slab2_limit) *
                        (long)(rate3_paise - rate2_paise);

    /* For this illustrative calculation, add the first 100 at rate 1,
       the next 100 at rate 2, and units above 200 at rate 3. */
    energy_paise = (units < 100U ? (long)units * rate1_paise : 0L)
                 + (units > 100U ? (long)((units < 200U ? units : 200U) - 100U)
                                      * rate2_paise : 0L)
                 + (units > 200U ? (long)(units - 200U) * rate3_paise : 0L);

    printf("Household: H1001, category: Domestic\n");
    printf("Previous=%u Current=%u Units=%u\n", previous, current, units);
    printf("Energy charge=Rs %ld.%02ld\n",
           energy_paise / 100L, energy_paise % 100L);
    printf("Fixed charge=Rs %ld.%02ld\n",
           fixed_charge_paise / 100L, fixed_charge_paise % 100L);
    printf("Total=Rs %ld.%02ld\n",
           (fixed_charge_paise + energy_paise) / 100L,
           (fixed_charge_paise + energy_paise) % 100L);

    puts("\nText alternative: read digit strings, validate each character,");
    puts("convert d digits in O(d) time; text uses about d bytes plus terminator,");
    puts("whereas an unsigned 16-bit integer uses 2 bytes.");
    puts("Assumptions: one register rollover at most between readings;");
    puts("readings are valid; fixed charge applies to every household.");
    return 0;
}
