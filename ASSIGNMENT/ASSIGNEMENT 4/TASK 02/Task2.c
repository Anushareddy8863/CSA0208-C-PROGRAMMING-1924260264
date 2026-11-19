#include <stdio.h>
#include <string.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[30];
    char city[20];
    int pincode;
} Person;

typedef struct {
    int id;
    float weight;
    Date bookingDate;
    Person sender;
    Person receiver;
    char serviceType[10];
    float charge;
} Parcel;

void print_parcel(const Parcel *p)
{
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id, p->weight, p->receiver.city, p->receiver.pincode,
           p->bookingDate.day, p->bookingDate.month, p->bookingDate.year);
}

void sort_by_weight(Parcel p[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].weight < p[min].weight) min = j;
        }
        if (min != i) {
            Parcel temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

void list_by_receiver_city(const Parcel p[], int n, const char city[])
{
    for (int i = 0; i < n; i++) {
        if (strcmp(p[i].receiver.city, city) == 0)
            print_parcel(&p[i]);
    }
}

int main(void)
{
    Parcel list[3] = {
        {501, 4.5f, {12,10,2026}, {"Arun","Madurai",625001},
         {"Bala","Madurai",625001}, "Normal", 80.0f},
        {502, 1.2f, {12,10,2026}, {"Devi","Chennai",600077},
         {"Kavi","Chennai",600077}, "Express", 120.0f},
        {503, 2.8f, {13,10,2026}, {"Rani","Salem",636001},
         {"Maha","Coimbatore",641001}, "Normal", 95.0f}
    };

    printf("Sorted by weight:\n");
    sort_by_weight(list, 3);
    for (int i = 0; i < 3; i++) print_parcel(&list[i]);

    printf("\nParcels for receiver city Chennai:\n");
    list_by_receiver_city(list, 3, "Chennai");

    /* Access expressions for third parcel:
       (i) list[2].receiver.pincode
       (ii) ptr->receiver.pincode, where ptr = &list[2]
    */
    Parcel *ptr = &list[2];
    printf("\nThird parcel PIN using dot: %d\n", list[2].receiver.pincode);
    printf("Third parcel PIN using arrow: %d\n", ptr->receiver.pincode);

    printf("Bytes copied in one structure swap: %zu\n", sizeof(Parcel));
    return 0;
}
