#include <stdio.h>
unsigned long checks=0;
int is_prime(unsigned long n){
    checks=0; if(n<2)return 0;
    for(unsigned long i=2;i<=n/i;i++){ /* avoids overflow from i*i */
        ++checks; if(n%i==0)return 0;
    } return 1;
}
int baseline(unsigned long n,unsigned long *c){
    *c=0;if(n<2)return 0;
    for(unsigned long i=2;i<n;i++){++*c;if(n%i==0)return 0;}return 1;
}
int while_prime(unsigned long n,unsigned long *c){
    *c=0;if(n<2)return 0;unsigned long i=2;
    while(i<=n/i){++*c;if(n%i==0)return 0;++i;}return 1;
}
int do_prime(unsigned long n,unsigned long *c){
    *c=0;if(n<2)return 0;if(n==2||n==3)return 1;
    unsigned long i=2;
    do{if(i>n/i)break;++*c;if(n%i==0)return 0;++i;}while(i<=n/i);
    return 1;
}
int main(void){
    unsigned long a[]={2,3,97,100,7919,1000003};
    for(unsigned k=0;k<sizeof a/sizeof a[0];k++){
        unsigned long n=a[k],f=0,w=0,d=0,b=0;int p=is_prime(n);f=checks;
        while_prime(n,&w);do_prime(n,&d);baseline(n,&b);
        printf("%8lu %-9s for=%lu while=%lu do=%lu baseline=%lu\\n",n,p?"prime":"not prime",f,w,d,b);
    }return 0;
}
