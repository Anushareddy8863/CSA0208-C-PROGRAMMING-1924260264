/* Q6 - A Directory of Names: Sorting and Searching Strings
   Compile: gcc Q6_Directory_Name_Search.c -o q6
   Run: ./q6
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 500
#define NAME_LEN 30

int comparisons=0;
int compare_counted(const char a[],const char b[]) {
    comparisons++;
    return strcmp(a,b);
}
void remove_newline(char s[]) {
    s[strcspn(s,"\n")]='\0';
}
void sort_names(char names[][NAME_LEN],int n) {
    for(int i=1;i<n;i++) {
        char key[NAME_LEN];
        strcpy(key,names[i]);
        int j=i-1;
        while(j>=0 && compare_counted(names[j],key)>0) {
            strcpy(names[j+1],names[j]);
            j--;
        }
        strcpy(names[j+1],key);
    }
}
int binary_search(char names[][NAME_LEN],int n,const char key[]) {
    int low=0,high=n-1;
    while(low<=high) {
        int mid=low+(high-low)/2;
        int cmp=compare_counted(names[mid],key);
        if(cmp==0) return mid;
        if(cmp<0) low=mid+1;
        else high=mid-1;
    }
    return -1;
}
int main(void) {
    char names[MAX_NAMES][NAME_LEN];
    int n;
    printf("Number of residents (1-%d): ",MAX_NAMES);
    if(scanf("%d",&n)!=1 || n<1 || n>MAX_NAMES) {
        puts("Invalid number."); return 1;
    }
    getchar();
    for(int i=0;i<n;i++) {
        printf("Name %d: ",i+1);
        if(!fgets(names[i],NAME_LEN,stdin)) return 1;
        remove_newline(names[i]);
    }
    comparisons=0;
    sort_names(names,n);
    printf("\nSorted names (strcmp calls during sort: %d):\n",comparisons);
    for(int i=0;i<n;i++) {
        printf("%s\n",names[i]);
        if(i>0 && strcmp(names[i],names[i-1])==0)
            printf("  DUPLICATE: %s\n",names[i]);
    }
    char key[NAME_LEN];
    printf("\nSearch name: ");
    if(!fgets(key,sizeof key,stdin)) return 1;
    remove_newline(key);
    comparisons=0;
    int pos=binary_search(names,n,key);
    printf("Search result index=%d, strcmp calls=%d\n",pos,comparisons);
    return 0;
}
