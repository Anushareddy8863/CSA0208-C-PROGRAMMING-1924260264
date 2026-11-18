/*
TASK 8 - Compilation stages
Commands:
gcc -E Task08_CompilationStages.c -o Task08_preprocessed.i
gcc -S Task08_CompilationStages.c -o Task08_assembly.s
gcc -c Task08_CompilationStages.c -o Task08_object.o
gcc Task08_object.o -o task08
gcc -Wall -Wextra Task08_CompilationStages.c -o task08
*/
#include <stdio.h>
#define FIXED_PAISE 5000LL

static long long add_fixed_charge(long long energy)
{
    return energy + FIXED_PAISE;
}

int main(void)
{
    printf("Total paise=%lld\n", add_fixed_charge(25313LL));
    return 0;
}
