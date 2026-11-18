/*
TASK 9 - Complete billing program with validation and tests
Input readings are 16-bit meter values. One rollover is handled modulo 65536.
*/
#include <stdio.h>
#include <limits.h>

#define METER_MODULUS 65536U
#define FIXED_CHARGE_PAISE 5000LL
#define SLAB1_UNITS 100U
#define SLAB2_UNITS 200U
#define RATE1_PAISE 0LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

static unsigned int units_used(unsigned int previous, unsigned int current)
{
    return (current - previous) % METER_MODULUS;
}

static long long bill_paise(unsigned int units)
{
    long long energy = 0LL;
    if (units <= SLAB1_UNITS)
        energy = (long long)units * RATE1_PAISE;
    else if (units <= SLAB2_UNITS)
        energy = (long long)SLAB1_UNITS * RATE1_PAISE
               + (long long)(units - SLAB1_UNITS) * RATE2_PAISE;
    else
        energy = (long long)SLAB1_UNITS * RATE1_PAISE
               + (long long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE
               + (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
    return FIXED_CHARGE_PAISE + energy;
}

static void print_bill(unsigned int prev, unsigned int curr)
{
    unsigned int units = units_used(prev, curr);
    long long amount = bill_paise(units);
    printf("%5u -> %5u | %5u units | Rs %lld.%02lld\n",
           prev, curr, units, amount / 100LL, amount % 100LL);
}

int main(void)
{
    puts("Normal and boundary tests:");
    print_bill(1000, 1000);       /* zero */
    print_bill(1000, 1100);       /* 100 */
    print_bill(1000, 1200);       /* 200 */
    print_bill(1000, 1350);       /* 350 */
    print_bill(65400, 120);       /* rollover: 256 */

    puts("\nInteractive validation test:");
    unsigned int previous, current;
    printf("Enter previous and current readings (0..65535): ");
    if (scanf("%u %u", &previous, &current) != 2) {
        puts("ERROR: non-numeric input.");
        return 1;
    }
    if (previous > USHRT_MAX || current > USHRT_MAX) {
        puts("ERROR: reading is outside the meter range.");
        return 1;
    }
    /* A lower current value is treated as rollover. If rollover is not
       physically plausible in the billing interval, flag it for review. */
    if (current < previous)
        puts("NOTICE: rollover detected; verify the interval and meter log.");
    print_bill(previous, current);

    puts("\nFive-household hand-check example:");
    unsigned int sample_units[] = {0, 100, 150, 200, 350};
    long long sum = 0LL;
    for (size_t i = 0; i < sizeof sample_units / sizeof sample_units[0]; ++i) {
        long long b = bill_paise(sample_units[i]);
        sum += b;
        printf("%u units: Rs %lld.%02lld\n", sample_units[i],
               b / 100LL, b % 100LL);
    }
    printf("Five-bill total: Rs %lld.%02lld\n", sum / 100LL, sum % 100LL);
    return 0;
}
