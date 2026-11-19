#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 20
#define MAX_SALES 50
#define MAX_COMBO_PARTS 3

typedef struct {
    int day, month, year;
} Date;

typedef enum { PACKAGED, COOKED, COMBO } ItemKind;

typedef struct {
    Date expiry;
} PackagedInfo;

typedef struct {
    int hour, minute;
} PreparedTime;

typedef struct {
    int partIds[MAX_COMBO_PARTS];
    int quantities[MAX_COMBO_PARTS];
    int partCount;
} ComboInfo;

typedef struct {
    int id;
    char name[30];
    float price;
    int stock;
    ItemKind kind;
    union {
        PackagedInfo packaged;
        PreparedTime cooked;
        ComboInfo combo;
    } details;
} Item;

typedef struct {
    int itemId;
    int quantity;
    float revenue;
} Sale;

typedef struct {
    int itemId;
    char itemName[30];
    float revenue;
} RevenueRow;

int dateSerial(Date d)
{
    struct tm t = {0};
    t.tm_mday = d.day;
    t.tm_mon = d.month - 1;
    t.tm_year = d.year - 1900;
    t.tm_isdst = -1;
    return (int)(mktime(&t) / (24 * 60 * 60));
}

Item *findItem(Item items[], int n, int id)
{
    for (int i = 0; i < n; i++)
        if (items[i].id == id) return &items[i];
    return NULL;
}

int availableStock(Item items[], int n, Item *item)
{
    if (item->kind != COMBO) return item->stock;

    int available = 1000000;
    for (int i = 0; i < item->details.combo.partCount; i++) {
        Item *part = findItem(items, n, item->details.combo.partIds[i]);
        if (part == NULL) return 0;
        int possible = part->stock / item->details.combo.quantities[i];
        if (possible < available) available = possible;
    }
    return available;
}

int recordSale(Item items[], int n, Sale sales[], int *saleCount,
               int itemId, int quantity)
{
    Item *item = findItem(items, n, itemId);
    if (item == NULL || quantity <= 0) return 0;
    if (availableStock(items, n, item) < quantity) {
        printf("Sale rejected for %s: insufficient stock.\n", item->name);
        return 0;
    }

    if (item->kind == COMBO) {
        for (int i = 0; i < item->details.combo.partCount; i++) {
            Item *part = findItem(items, n, item->details.combo.partIds[i]);
            part->stock -= item->details.combo.quantities[i] * quantity;
        }
    } else {
        item->stock -= quantity;
    }

    if (*saleCount < MAX_SALES) {
        sales[*saleCount].itemId = itemId;
        sales[*saleCount].quantity = quantity;
        sales[*saleCount].revenue = item->price * quantity;
        (*saleCount)++;
    }
    printf("Sale recorded: %s x %d, Rs. %.2f\n",
           item->name, quantity, item->price * quantity);
    return 1;
}

void expiryWarnings(Item items[], int n, Date today)
{
    int todayNo = dateSerial(today);
    for (int i = 0; i < n; i++) {
        if (items[i].kind == PACKAGED) {
            int daysLeft = dateSerial(items[i].details.packaged.expiry) - todayNo;
            if (daysLeft >= 0 && daysLeft <= 2)
                printf("Expiry warning: %s expires in %d day(s).\n",
                       items[i].name, daysLeft);
        }
    }
}

void printRevenueSummary(Item items[], int n, Sale sales[], int saleCount)
{
    RevenueRow rows[MAX_ITEMS];
    int rowCount = 0;

    for (int i = 0; i < n; i++) {
        float total = 0.0f;
        for (int j = 0; j < saleCount; j++)
            if (sales[j].itemId == items[i].id)
                total += sales[j].revenue;
        if (total > 0) {
            rows[rowCount].itemId = items[i].id;
            strcpy(rows[rowCount].itemName, items[i].name);
            rows[rowCount].revenue = total;
            rowCount++;
        }
    }

    for (int i = 0; i < rowCount - 1; i++) {
        for (int j = 0; j < rowCount - i - 1; j++) {
            if (rows[j].revenue < rows[j + 1].revenue) {
                RevenueRow temp = rows[j];
                rows[j] = rows[j + 1];
                rows[j + 1] = temp;
            }
        }
    }

    printf("\nDay's revenue summary (high to low):\n");
    for (int i = 0; i < rowCount; i++)
        printf("%s : Rs. %.2f\n", rows[i].itemName, rows[i].revenue);
}

int main(void)
{
    Item items[MAX_ITEMS] = {
        {1, "Juice", 30.0f, 5, PACKAGED, {.packaged = {{21,11,2026}}}},
        {2, "Sandwich", 50.0f, 4, COOKED, {.cooked = {8,30}}},
        {3, "Combo Meal", 75.0f, 0, COMBO,
         {.combo = {{1,2}, {1,1}, 2}}}
    };
    Sale sales[MAX_SALES];
    int saleCount = 0;
    Date today = {19,11,2026};

    printf("Normal sale:\n");
    recordSale(items, 3, sales, &saleCount, 1, 2);

    printf("\nSale exceeding stock:\n");
    recordSale(items, 3, sales, &saleCount, 2, 10);

    printf("\nCombo sale:\n");
    recordSale(items, 3, sales, &saleCount, 3, 1);

    printf("\nExpiry check:\n");
    expiryWarnings(items, 3, today);

    printRevenueSummary(items, 3, sales, saleCount);

    printf("\nRemaining stock: Juice=%d, Sandwich=%d\n",
           items[0].stock, items[1].stock);
    return 0;
}
