/*
TASK 12 - Smart-meter redesign: watt-hours, 15-minute intervals,
time-of-day peak rate (+20%), and run-time tariff configuration.

Compile: gcc -std=c11 -Wall -Wextra Task12_SmartMeterTOU.c -o task12
Run:     ./task12 [optional tariff.txt]

Example tariff.txt (paise per kWh):
base_rate_paise_per_kwh=225
fixed_charge_paise=5000
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

typedef struct {
    int64_t base_rate_paise_per_kwh;
    int64_t fixed_charge_paise;
} Tariff;

static int load_tariff(const char *path, Tariff *t)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;
    char key[80];
    long long value;
    int got_rate = 0, got_fixed = 0;

    while (fscanf(fp, " %79[^=]=%lld", key, &value) == 2) {
        if (strcmp(key, "base_rate_paise_per_kwh") == 0 && value >= 0) {
            t->base_rate_paise_per_kwh = (int64_t)value;
            got_rate = 1;
        } else if (strcmp(key, "fixed_charge_paise") == 0 && value >= 0) {
            t->fixed_charge_paise = (int64_t)value;
            got_fixed = 1;
        }
    }
    fclose(fp);
    return got_rate && got_fixed;
}

/* watt_hours is interval energy. Peak interval (18:00 through 21:59)
   receives 20% surcharge. Round to nearest paise per interval. */
static int64_t interval_charge(int64_t watt_hours, int hour, const Tariff *t)
{
    int64_t rate = t->base_rate_paise_per_kwh;
    if (hour >= 18 && hour < 22)
        rate = (rate * 120 + 50) / 100; /* nearest whole paise */
    /* paise/kWh * Wh / 1000; nearest paise */
    return (watt_hours * rate + 500) / 1000;
}

int main(int argc, char **argv)
{
    Tariff tariff = {225, 5000};
    if (argc > 1 && !load_tariff(argv[1], &tariff)) {
        fprintf(stderr, "Could not load valid tariff file: %s\n", argv[1]);
        return 1;
    }

    /* One house: 35,040 intervals/year. Demonstration values only.
       1 kWh = 1000 Wh; use int64_t for yearly energy and money. */
    int64_t yearly_watt_hours = 0;
    int64_t yearly_energy_paise = 0;
    for (int interval = 0; interval < 35040; ++interval) {
        int hour = (interval % 96) / 4; /* 96 quarter-hours per day */
        int64_t wh = 250;               /* sample 0.25 kWh interval */
        yearly_watt_hours += wh;
        yearly_energy_paise += interval_charge(wh, hour, &tariff);
    }

    int64_t total = yearly_energy_paise + tariff.fixed_charge_paise;
    printf("Yearly energy: %" PRId64 " Wh (%.2f kWh)\n",
           yearly_watt_hours, (double)yearly_watt_hours / 1000.0);
    printf("Energy charge: Rs %" PRId64 ".%02" PRId64 "\n",
           yearly_energy_paise / 100, yearly_energy_paise % 100);
    printf("Total incl. fixed charge: Rs %" PRId64 ".%02" PRId64 "\n",
           total / 100, total % 100);
    puts("Design decision: MODIFY/REDESIGN using 64-bit Wh and paise,");
    puts("runtime tariff configuration, and explicit time-of-day classification.");
    return 0;
}
