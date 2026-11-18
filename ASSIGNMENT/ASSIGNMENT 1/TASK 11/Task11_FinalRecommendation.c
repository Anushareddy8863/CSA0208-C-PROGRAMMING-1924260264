/*
TASK 11 - Recommended original monthly billing design
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define FIXED_CHARGE_PAISE INT64_C(5000)
#define SLAB1 100
#define SLAB2 200
#define RATE2 225
#define RATE3 450

static int64_t calculate_bill(uint32_t units)
{
    int64_t energy = 0;
    if (units > SLAB1)
        energy += (int64_t)(units < SLAB2 ? units - SLAB1 : SLAB2 - SLAB1) * RATE2;
    if (units > SLAB2)
        energy += (int64_t)(units - SLAB2) * RATE3;
    return FIXED_CHARGE_PAISE + energy;
}

int main(void)
{
    uint32_t units = 350U;
    int64_t amount = calculate_bill(units);
    printf("Recommended design: units=%" PRIu32 ", bill=Rs %" PRId64 ".%02" PRId64 "\n",
           units, amount / 100, amount % 100);
    puts("Use fixed-width unsigned meter readings and signed 64-bit paise totals.");
    puts("Keep tariff definitions in one header; revise centrally and retest.");
    puts("For frequent revisions, load validated tariff configuration at startup.");
    return 0;
}
