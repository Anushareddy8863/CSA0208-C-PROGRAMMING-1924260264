/* Q1 - Searching a Library Catalogue
   Compile: gcc Q1_Library_Search.c -o q1
   Run: ./q1
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int steps;

int linear_search(const int a[], int n, int key) {
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (a[i] == key) return i;
    }
    return -1;
}

/* Array must be sorted in ascending order. */
int binary_search(const int a[], int n, int key) {
    int low = 0, high = n - 1;
    steps = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    int sorted[] = {1021,1048,1103,1190,1222,1305,1377,1402,1460,1533};
    int unsorted[] = {1222,1021,1460,1103,1533,1305,1048,1402,1190,1377};
    int keys[] = {1021,1305,1533,1400};
    int n = sizeof sorted / sizeof sorted[0];

    puts("LIBRARY CATALOGUE SEARCH");
    for (int k = 0; k < 4; k++) {
        int p = linear_search(unsorted, n, keys[k]);
        printf("Linear: book %d -> index %d, comparisons = %d\n", keys[k], p, steps);
        p = binary_search(sorted, n, keys[k]);
        printf("Binary: book %d -> index %d, comparisons = %d\n", keys[k], p, steps);
    }

    /* Demonstrate generated large sorted catalogue sizes. */
    int sizes[] = {1000, 10000, 100000};
    srand(1);
    for (int s = 0; s < 3; s++) {
        int count = sizes[s];
        int *a = malloc((size_t)count * sizeof(int));
        if (!a) { perror("malloc"); return 1; }
        for (int i = 0; i < count; i++) a[i] = 100000 + i * 3;
        int found = a[count / 2], missing = -1;
        binary_search(a, count, found);
        printf("n=%d binary successful comparisons=%d; ", count, steps);
        binary_search(a, count, missing);
        printf("unsuccessful comparisons=%d\n", steps);
        free(a);
    }
    return 0;
}
