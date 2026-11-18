#include <stdio.h>
char grade_if(int m){
    if(m<0||m>100)return '?';
    if(m>=90)return 'S'; else if(m>=80)return 'A'; else if(m>=70)return 'B';
    else if(m>=60)return 'C'; else if(m>=50)return 'D'; else return 'F';
}
char grade_switch(int m){
    if(m<0||m>100)return '?';
    switch(m/10){
        case 10: case 9:return 'S'; case 8:return 'A'; case 7:return 'B';
        case 6:return 'C'; case 5:return 'D'; default:return 'F';
    }
}
char grade_table(int m){
    static const char g[11]={'F','F','F','F','F','D','C','B','A','S','S'};
    if(m<0||m>100)return '?'; return g[m/10];
}
const char *scholarship(char g,int income){
    if(g=='?'||income<0)return "Invalid input";
    if(income<=200000&&(g=='S'||g=='A'))return "Full scholarship";
    if(income<=400000&&(g=='S'||g=='A'||g=='B'))return "Partial scholarship";
    return "No scholarship";
}
int main(void){
    int a[]={100,90,89,85,84,80,79,75,74,70,69,60,59,50,49,0,-1,101};
    puts("marks if-ladder switch table");
    for(unsigned i=0;i<sizeof a/sizeof a[0];i++)
        printf("%5d %c %c %c\\n",a[i],grade_if(a[i]),grade_switch(a[i]),grade_table(a[i]));
    printf("Scholarship example: %s\\n",scholarship('A',180000));
    return 0;
}
