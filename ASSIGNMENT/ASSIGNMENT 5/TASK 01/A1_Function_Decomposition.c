#include <stdio.h>
#include <string.h>

typedef struct { int day, month, year; } Date;
typedef struct {
    int donorId;
    char name[50], bloodGroup[4], phone[11];
    int age;
    Date lastDonation;
} Donor;
typedef struct { char bloodGroup[4]; int units; } Stock;
typedef struct { int eligibleCount; int youngestDonorId; } EligibilityResult;

int registerDonor(Donor *d, int id, const char *name, const char *group,
                  int age, const char *phone, Date last);
int isEligible(const Donor *d, Date today);
int findEligible(const Donor donors[], int n, const char *group, Date today,
                 int *youngestId);
EligibilityResult findEligibleResult(const Donor donors[], int n,
                                     const char *group, Date today);
Stock *findStock(Stock stock[], int n, const char *group);
int updateStock(Stock *s, int change);
int saveDonors(const char *filename, const Donor donors[], int n);
int loadDonors(const char *filename, Donor donors[], int capacity);

int registerDonor(Donor *d, int id, const char *name, const char *group,
                  int age, const char *phone, Date last)
{
    if (!d || !name || !group || !phone) return 0;
    d->donorId = id; d->age = age; d->lastDonation = last;
    snprintf(d->name, sizeof d->name, "%s", name);
    snprintf(d->bloodGroup, sizeof d->bloodGroup, "%s", group);
    snprintf(d->phone, sizeof d->phone, "%s", phone);
    return 1;
}

/* Simplified policy for demonstration: at least 90 days since last donation. */
int isEligible(const Donor *d, Date today)
{
    int oldDays = d->lastDonation.year * 365 + d->lastDonation.month * 30
                + d->lastDonation.day;
    int nowDays = today.year * 365 + today.month * 30 + today.day;
    return (nowDays - oldDays) >= 90;
}

int findEligible(const Donor donors[], int n, const char *group, Date today,
                 int *youngestId)
{
    int count = 0, youngestAge = 1000;
    if (youngestId) *youngestId = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(donors[i].bloodGroup, group) == 0 &&
            isEligible(&donors[i], today)) {
            count++;
            if (donors[i].age < youngestAge) {
                youngestAge = donors[i].age;
                if (youngestId) *youngestId = donors[i].donorId;
            }
        }
    }
    return count;
}

EligibilityResult findEligibleResult(const Donor donors[], int n,
                                     const char *group, Date today)
{
    EligibilityResult r;
    r.eligibleCount = findEligible(donors, n, group, today,
                                   &r.youngestDonorId);
    return r;
}

Stock *findStock(Stock stock[], int n, const char *group)
{
    for (int i = 0; i < n; i++)
        if (strcmp(stock[i].bloodGroup, group) == 0) return &stock[i];
    return NULL;
}

int updateStock(Stock *s, int change)
{
    if (!s || s->units + change < 0) return 0;
    s->units += change;
    return 1;
}

int saveDonors(const char *filename, const Donor donors[], int n)
{
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("fopen donor file"); return 0; }
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d|%s|%s|%d|%s|%d/%d/%d\n",
                donors[i].donorId, donors[i].name, donors[i].bloodGroup,
                donors[i].age, donors[i].phone, donors[i].lastDonation.day,
                donors[i].lastDonation.month, donors[i].lastDonation.year);
    fclose(fp);
    return 1;
}

int loadDonors(const char *filename, Donor donors[], int capacity)
{
    FILE *fp = fopen(filename, "r");
    int n = 0;
    if (!fp) { perror("fopen donor file"); return -1; }
    while (n < capacity &&
           fscanf(fp, "%d|%49[^|]|%3[^|]|%d|%10[^|]|%d/%d/%d\n",
                  &donors[n].donorId, donors[n].name, donors[n].bloodGroup,
                  &donors[n].age, donors[n].phone, &donors[n].lastDonation.day,
                  &donors[n].lastDonation.month, &donors[n].lastDonation.year) == 8)
        n++;
    fclose(fp);
    return n;
}

int main(void)
{
    Donor donors[3];
    Stock stocks[2] = {{{"O+"}, 10}, {{"A-"}, 5}};
    Date today = {19, 11, 2026};
    registerDonor(&donors[0], 101, "Anu", "O+", 24, "9876543210", (Date){1,1,2026});
    registerDonor(&donors[1], 102, "Bala", "O+", 31, "9876543211", (Date){1,1,2026});
    registerDonor(&donors[2], 103, "Devi", "A-", 22, "9876543212", (Date){1,10,2026});
    EligibilityResult r = findEligibleResult(donors, 3, "O+", today);
    printf("Eligible O+ donors: %d; youngest donor ID: %d\n",
           r.eligibleCount, r.youngestDonorId);
    updateStock(findStock(stocks, 2, "O+"), -2);
    printf("O+ stock after issue: %d units\n", stocks[0].units);
    saveDonors("donors.txt", donors, 3);
    return 0;
}
