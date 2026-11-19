#include <stdio.h>
#include <string.h>

const char *groups[8] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

int *lowestStock(int stock[], int n)
{
    if (!stock || n <= 0) return NULL;
    int *lowest = &stock[0];
    for (int i = 1; i < n; i++)
        if (stock[i] < *lowest) lowest = &stock[i];
    return lowest;
}

int groupIndex(const char *group)
{
    for (int i = 0; i < 8; i++)
        if (strcmp(groups[i], group) == 0) return i;
    return -1;
}

int main(int argc, char *argv[])
{
    int stock[8] = {20, 5, 18, 7, 9, 3, 25, 6};
    int *p = stock;

    printf("p + 3 is address of stock[3]\n");
    printf("*(p + 3) = %d; p[3] = %d\n", *(p + 3), p[3]);
    printf("*p++ = %d; pointer then advances to next element\n", *p++);

    int *low = lowestStock(stock, 8);
    if (low) printf("Lowest stock = %d\n", *low);

    if (argc == 1) {
        printf("Usage: %s find GROUP | issue GROUP UNITS\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "find") == 0 && argc == 3) {
        int idx = groupIndex(argv[2]);
        if (idx < 0) { fprintf(stderr, "Invalid blood group\n"); return 1; }
        printf("%s has %d units\n", groups[idx], stock[idx]);
    } else if (strcmp(argv[1], "issue") == 0 && argc == 4) {
        int idx = groupIndex(argv[2]), units = 0;
        if (idx < 0 || sscanf(argv[3], "%d", &units) != 1 || units <= 0) {
            fprintf(stderr, "Invalid group or unit count\n"); return 1;
        }
        if (units > stock[idx]) { fprintf(stderr, "Insufficient stock\n"); return 1; }
        stock[idx] -= units;
        printf("Issued %d units of %s; remaining=%d\n", units, groups[idx], stock[idx]);
    } else {
        fprintf(stderr, "Invalid arguments. Use find GROUP or issue GROUP UNITS\n");
        return 1;
    }
    return 0;
}
