/* Q3 - Merging Two Merit Lists
   Compile: gcc Q3_Merit_List_Merge.c -o q3
   Run: ./q3
*/
#include <stdio.h>
#include <stdlib.h>

long comparisons;
int merge(const int a[], int na, const int b[], int nb, int out[]) {
    int i=0,j=0,k=0;
    comparisons=0;
    while (i<na && j<nb) {
        comparisons++;
        /* >= keeps campus A first when scores are equal. */
        if (a[i] >= b[j]) out[k++]=a[i++];
        else out[k++]=b[j++];
    }
    while (i<na) out[k++]=a[i++];
    while (j<nb) out[k++]=b[j++];
    return k;
}
int main(void) {
    int campusA[]={98,91,85,72}, campusB[]={95,91,80}, merged[7];
    int n=merge(campusA,4,campusB,3,merged);
    for(int i=0;i<n;i++) printf("%d ",merged[i]);
    printf("\nComparisons = %ld\n",comparisons);

    /* Empty-list test */
    int empty_result[3], other[]={88,77,66};
    n=merge(NULL,0,other,3,empty_result);
    printf("One empty list: ");
    for(int i=0;i<n;i++) printf("%d ",empty_result[i]);
    putchar('\n');
    return 0;
}
