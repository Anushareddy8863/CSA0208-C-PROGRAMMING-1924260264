#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int id; char group[4]; int age; } Donor;
typedef struct { Donor *data; size_t size, capacity; } DonorList;

int add_donor(DonorList *list, int id, const char *group, int age)
{
    if (list->size == list->capacity) {
        size_t newCapacity = list->capacity == 0 ? 2 : list->capacity * 2;
        Donor *p = realloc(list->data, newCapacity * sizeof *list->data);
        if (p == NULL) return 0;
        list->data = p;
        list->capacity = newCapacity;
    }
    list->data[list->size].id = id;
    snprintf(list->data[list->size].group, sizeof list->data[list->size].group,
             "%s", group);
    list->data[list->size].age = age;
    list->size++;
    return 1;
}

int main(void)
{
    DonorList list = {NULL, 0, 0};
    const char *groups[] = {"O+", "A+", "B-", "AB+", "O-"};
    clock_t start = clock();

    for (int i = 0; i < 5; i++) {
        if (!add_donor(&list, 7001 + i, groups[i], 20 + i)) {
            perror("realloc"); free(list.data); return 1;
        }
        printf("added %d (%s): size = %zu, capacity = %zu\n",
               list.data[i].id, list.data[i].group, list.size, list.capacity);
    }

    printf("Report: donors eligible for next-week review (demonstration list)\n");
    for (size_t i = 0; i < list.size; i++)
        if (list.data[i].age >= 18)
            printf("Donor ID %d, group %s\n", list.data[i].id, list.data[i].group);

    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Allocated memory: %zu bytes\n", list.capacity * sizeof(Donor));
    printf("Elapsed CPU time: %.6f seconds\n", elapsed);

    free(list.data);
    list.data = NULL;
    list.size = list.capacity = 0;
    return 0;
}
