/*
TASK 4 - Safe macros
Preprocessor evidence: gcc -E Task04_SafeMacros.c
*/
#include <stdio.h>
#define RUPEES_TO_PAISE(r) ((long long)(r) * 100LL)
#define SQUARE(x) ((x) * (x))
#define MAX_VALUE(a, b) (((a) > (b)) ? (a) : (b))

static inline long long square_fn(long long x) { return x * x; }
static inline int max_fn(int a, int b) { return a > b ? a : b; }

int main(void)
{
    int a = 4, b = 7, i = 2;
    printf("SQUARE(a+1)=%d\n", SQUARE(a + 1));
    printf("MAX_VALUE(a,b)=%d\n", MAX_VALUE(a, b));
    printf("Rupees 50 -> %lld paise\n", RUPEES_TO_PAISE(50));
    /* Do not pass i++ to MAX_VALUE: a macro may evaluate an argument twice. */
    printf("inline square=%lld inline max=%d\n",
           square_fn(5), max_fn(a, b));
    printf("i before side-effect-safe use=%d\n", i);
    return 0;
}
