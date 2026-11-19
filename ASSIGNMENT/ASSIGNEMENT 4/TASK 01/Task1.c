#include <stdio.h>
#include <string.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    char name[50];
    int age;
    char phone[11]; /* 10 digits + '\0' */
    BloodPressure bp;
    Date visitDate;
} Patient;

void addPatient(Patient *p, const char name[], int age, const char phone[],
                BloodPressure bp, Date visitDate)
{
    if (p == NULL) return;

    snprintf(p->name, sizeof p->name, "%s", name);
    p->age = age;
    snprintf(p->phone, sizeof p->phone, "%s", phone);
    p->bp = bp;
    p->visitDate = visitDate;
}

void sortByAge(Patient patients[], int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (patients[j].age > patients[j + 1].age) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}

void printPatient(const Patient *p)
{
    printf("%-12s Age:%d Phone:%s BP:%d/%d Visit:%02d/%02d/%04d\n",
           p->name, p->age, p->phone, p->bp.systolic, p->bp.diastolic,
           p->visitDate.day, p->visitDate.month, p->visitDate.year);
}

int main(void)
{
    Patient patients[100];
    int count = 0;

    BloodPressure bp1 = {120, 80};
    BloodPressure bp2 = {110, 70};

    addPatient(&patients[count++], "Anu", 25, "9876543210",
               bp1, (Date){12, 10, 2026});
    addPatient(&patients[count++], "Ravi", 40, "9123456780",
               bp2, (Date){13, 10, 2026});

    printf("Before sorting:\n");
    for (int i = 0; i < count; i++) printPatient(&patients[i]);

    sortByAge(patients, count);

    printf("\nAfter sorting by age:\n");
    for (int i = 0; i < count; i++) printPatient(&patients[i]);

    return 0;
}
