/*
TASK 6 - scanf validation and formatted output
*/
#include <stdio.h>

int main(void)
{
    unsigned int previous, current;
    unsigned int units;
    long long bill_paise;

    printf("Enter previous and current meter readings (0..65535): ");
    if (scanf("%u %u", &previous, &current) != 2) {
        fprintf(stderr, "Invalid input: enter two whole-number readings.\n");
        return 1;
    }
    if (previous > 65535U || current > 65535U) {
        fprintf(stderr, "Reading outside 16-bit meter range.\n");
        return 1;
    }

    units = (current - previous) & 65535U;
    bill_paise = 5000LL;
    if (units > 100U)
        bill_paise += (long long)(units < 200U ? units - 100U : 100U) * 225LL;
    if (units > 200U)
        bill_paise += (long long)(units - 200U) * 450LL;

    printf("Units consumed: %u\n", units);
    printf("Bill: Rs %lld.%02lld\n",
           bill_paise / 100LL, bill_paise % 100LL);
    return 0;
}
