#include <stdio.h>

struct account {
    int number;
    float balance;
};

void addInterest(struct account *a, float rate)
{
    if (a == NULL) return;

    printf("Address inside addInterest: %p\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100.0f;
}

int main(void)
{
    struct account list[3] = {
        {101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}
    };
    struct account *p = list;

    for (int i = 0; i < 3; i++) {
        printf("Address in main:          %p\n", (void *)&list[i]);
        addInterest(&list[i], 4.0f);
    }

    printf("\nUpdated account balances:\n");
    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", p[i].number, p[i].balance);

    /* Correct pointer member access: p->number and p->balance */
    printf("First account through arrow: %d %.2f\n",
           p->number, p->balance);

    return 0;
}
