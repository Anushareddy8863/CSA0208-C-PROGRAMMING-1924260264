#include <stdio.h>
typedef struct { int senior, eligible, card; } Passenger;
static unsigned long calls;
static int slow_verify(int card) { ++calls; return card; }
static int order_a(Passenger p) { return (p.senior && p.eligible) || slow_verify(p.card); }
static int order_b(Passenger p) { return slow_verify(p.card) || (p.senior && p.eligible); }
static int nested(Passenger p) {
    if (p.senior && p.eligible) return 1;
    if (slow_verify(p.card)) return 1;
    return 0;
}
int main(void) {
    Passenger a[1000];
    for(int i=0;i<1000;i++){a[i].senior=i%5==0;a[i].eligible=i%2==0;a[i].card=i%10==0;}
    int grants=0; calls=0;
    for(int i=0;i<1000;i++) grants+=order_a(a[i]);
    printf("Cheap checks first: server calls=%lu grants=%d\\n",calls,grants);
    calls=0; grants=0;
    for(int i=0;i<1000;i++) grants+=order_b(a[i]);
    printf("Server check first: server calls=%lu grants=%d\\n",calls,grants);
    calls=0; grants=0;
    for(int i=0;i<1000;i++) grants+=nested(a[i]);
    printf("Nested if: server calls=%lu grants=%d\\n",calls,grants);
    calls=0; int x=0; if(x && slow_verify(1)){} printf("0 && verify calls=%lu\\n",calls);
    if(x & slow_verify(1)){} printf("0 & verify calls=%lu\\n",calls);
    /* Audit requirement: call verifier for every passenger, then combine values. */
    calls=0;
    for(int i=0;i<1000;i++){int audited=slow_verify(a[i].card); grants+=(a[i].senior&&a[i].eligible)||audited;}
    printf("Audit-everyone calls=%lu (one per passenger)\\n",calls);
    return 0;
}
