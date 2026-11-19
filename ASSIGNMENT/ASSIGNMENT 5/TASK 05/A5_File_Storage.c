#include <stdio.h>
#include <string.h>

typedef struct { int groupCode; int units; } Stock;

int saveDonorsText(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("open donors text"); return 0; }
    fprintf(fp, "1001|Anu|O+|24|9876543210|01/01/2026\n");
    fprintf(fp, "1002|Bala|A-|31|9876543211|02/02/2026\n");
    fclose(fp);
    return 1;
}

int saveStockBinary(const char *filename, const Stock stock[], size_t n)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp) { perror("open stock binary"); return 0; }
    size_t written = fwrite(stock, sizeof *stock, n, fp);
    fclose(fp);
    return written == n;
}

int updateUnits(const char *filename, int index, int newUnits)
{
    FILE *fp = fopen(filename, "r+b");
    Stock s;
    if (!fp) { perror("open stock binary"); return 0; }
    if (fseek(fp, (long)index * (long)sizeof(Stock), SEEK_SET) != 0 ||
        fread(&s, sizeof s, 1, fp) != 1) {
        fclose(fp); return 0;
    }
    s.units = newUnits;
    if (fseek(fp, -(long)sizeof(Stock), SEEK_CUR) != 0 ||
        fwrite(&s, sizeof s, 1, fp) != 1) {
        fclose(fp); return 0;
    }
    fclose(fp);
    return 1;
}

int main(void)
{
    Stock stock[5] = {{1,40},{2,25},{3,12},{4,8},{5,30}};
    if (!saveDonorsText("donors.txt")) return 1;
    if (!saveStockBinary("stock.dat", stock, 5)) return 1;

    printf("Update record 3: %s\n", updateUnits("stock.dat", 3, 20) ? "done" : "failed");
    printf("Update record 9: %s\n", updateUnits("stock.dat", 9, 20) ? "done" : "failed");

    FILE *fp = fopen("stock.dat", "rb");
    if (!fp) { perror("read stock"); return 1; }
    Stock s;
    while (fread(&s, sizeof s, 1, fp) == 1)
        printf("%d:%d ", s.groupCode, s.units);
    printf("\n");
    fclose(fp);
    return 0;
}
