#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id, age;
    char name[50], group[4], phone[11];
} Donor;

typedef struct {
    Donor *data;
    size_t size, capacity;
} DonorList;

int addDonor(DonorList *list, Donor donor)
{
    if (list->size == list->capacity) {
        size_t newCapacity = (list->capacity == 0) ? 2 : list->capacity * 2;
        Donor *temp = realloc(list->data, newCapacity * sizeof *list->data);
        if (temp == NULL) {
            perror("realloc");
            return 0; /* old list->data remains valid */
        }
        list->data = temp;
        list->capacity = newCapacity;
    }
    list->data[list->size++] = donor;
    return 1;
}

int main(void)
{
    DonorList list = {NULL, 0, 0};
    for (int i = 0; i < 10; i++) {
        Donor d = {7000 + i, 20 + i, "SampleDonor", "O+", "9876543210"};
        if (!addDonor(&list, d)) {
            free(list.data);
            return 1;
        }
        printf("Added %d size=%zu capacity=%zu\n",
               d.id, list.size, list.capacity);
    }
    printf("Allocated bytes = %zu\n", list.capacity * sizeof(Donor));
    free(list.data);
    list.data = NULL;
    list.size = list.capacity = 0;
    return 0;
}
