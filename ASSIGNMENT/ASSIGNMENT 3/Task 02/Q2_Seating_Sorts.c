/* Q2 - Sorting the Examination Hall Seating Register
   Compile: gcc Q2_Seating_Sorts.c -o q2
   Run: ./q2
*/
#include <stdio.h>
#include <string.h>

typedef struct { long comparisons, swaps, shifts; } Stats;

void bubble_sort(int a[], int n, Stats *s) {
    s->comparisons = s->swaps = s->shifts = 0;
    for (int i = 0; i < n - 1; i++) {
        int changed = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            s->comparisons++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                s->swaps++; changed = 1;
            }
        }
        if (!changed) break;
    }
}
void selection_sort(int a[], int n, Stats *s) {
    s->comparisons = s->swaps = s->shifts = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            s->comparisons++;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int t = a[i]; a[i] = a[min]; a[min] = t; s->swaps++;
        }
    }
}
void insertion_sort(int a[], int n, Stats *s) {
    s->comparisons = s->swaps = s->shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            s->comparisons++;
            if (a[j] > key) { a[j + 1] = a[j]; s->shifts++; j--; }
            else break;
        }
        a[j + 1] = key;
    }
}
void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    putchar('\n');
}
int main(void) {
    int original[] = {42, 17, 31, 8, 25, 13};
    int n = sizeof original / sizeof original[0], a[6];
    Stats s;
    memcpy(a, original, sizeof a); bubble_sort(a, n, &s);
    printf("Bubble: "); print_array(a,n);
    printf("Comparisons=%ld swaps=%ld\n",s.comparisons,s.swaps);
    memcpy(a, original, sizeof a); selection_sort(a, n, &s);
    printf("Selection: "); print_array(a,n);
    printf("Comparisons=%ld swaps=%ld\n",s.comparisons,s.swaps);
    memcpy(a, original, sizeof a); insertion_sort(a, n, &s);
    printf("Insertion: "); print_array(a,n);
    printf("Comparisons=%ld shifts=%ld\n",s.comparisons,s.shifts);

    /* Input order experiment: sorted, nearly sorted, reverse, random. */
    int cases[4][6] = {
        {1,2,3,4,5,6}, {1,2,4,3,5,6},
        {6,5,4,3,2,1}, {4,1,6,2,5,3}
    };
    const char *labels[] = {"Sorted","Nearly sorted","Reverse","Random"};
    for (int c=0;c<4;c++) {
        memcpy(a,cases[c],sizeof a); insertion_sort(a,n,&s);
        printf("%s input - insertion comparisons=%ld shifts=%ld\n",
               labels[c],s.comparisons,s.shifts);
    }
    return 0;
}
