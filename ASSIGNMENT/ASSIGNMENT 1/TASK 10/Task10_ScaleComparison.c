/*
TASK 10 - Scale and accumulator comparison
The example uses a constant sample bill of 16250 paise.
*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    const long long one_bill_paise = 16250LL;
    const int counts[] = {4000, 60000, 800000};
    printf("LONG_MAX=%ld LLONG_MAX=%lld DBL_DIG=%d\n",
           LONG_MAX, LLONG_MAX, DBL_DIG);

    for (size_t j = 0; j < sizeof counts / sizeof counts[0]; ++j) {
        long long exact_paise = 0LL;
        double double_rupees = 0.0;
        float float_rupees = 0.0f;
        for (int i = 0; i < counts[j]; ++i) {
            exact_paise += one_bill_paise;
            double_rupees += 162.50;
            float_rupees += 162.50f;
        }
        printf("%d bills: paise total=%lld; double=%.2f; float=%.2f\n",
               counts[j], exact_paise, double_rupees, (double)float_rupees);
    }
    puts("Check overflow using count * maximum_bill_paise against LLONG_MAX.");
    return 0;
}
