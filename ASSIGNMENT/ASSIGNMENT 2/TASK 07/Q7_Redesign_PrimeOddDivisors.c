#include <stdio.h>
static unsigned long original_count,redesign_count;
static int original_prime(unsigned long n){
    original_count=0;if(n<2)return 0;
    for(unsigned long d=2;d<=n/d;d++){++original_count;if(n%d==0)return 0;}return 1;
}
static int redesigned_prime(unsigned long n){
    redesign_count=0;if(n<2)return 0;if(n==2)return 1;
    ++redesign_count;if(n%2==0)return 0;
    for(unsigned long d=3;d<=n/d;d+=2){++redesign_count;if(n%d==0)return 0;}return 1;
}
int main(void){
    unsigned long a[]={97,100,7919,1000003,1000000007};
    puts("number original-count redesigned-count result");
    for(unsigned i=0;i<sizeof a/sizeof a[0];i++){
        int x=original_prime(a[i]);unsigned long oc=original_count;
        int y=redesigned_prime(a[i]);unsigned long rc=redesign_count;
        printf("%10lu %13lu %16lu %s/%s\\n",a[i],oc,rc,x?"prime":"not-prime",y?"prime":"not-prime");
    }
    puts("Redesign checks divisor 2 once, then odd divisors only. Both O(sqrt(n)) time, O(1) extra space.");
    return 0;
}
