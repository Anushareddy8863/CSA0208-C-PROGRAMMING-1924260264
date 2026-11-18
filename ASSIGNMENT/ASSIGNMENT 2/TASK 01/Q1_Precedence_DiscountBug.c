#include <stdio.h>
/* Q1: compile: gcc -std=c11 -Wall -Wextra Q1_Precedence_DiscountBug.c -o q1 */
static double correct_bill(double price, int qty, int senior) {
    double gross = price * qty;
    double discount = senior ? gross * 0.15 : 0.0;
    double after_discount = gross - discount;
    double gst = after_discount * 0.05;
    return after_discount + gst;
}
int main(void) {
    double p[] = {100.0, 250.0, 99.99}; int q[] = {2,5,3}, s[] = {1,0,1};
    for (int i=0;i<3;i++) {
        double price=p[i]; int qty=q[i], senior=s[i];
        /* Original expression: * and / bind before + and -, left associative. */
        double total=price*qty-price*qty*15/100*senior+price*qty*5/100;
        double net=total>1000?total-50:total;
        double fixed=correct_bill(price,qty,senior), fixed_net=fixed>1000?fixed-50:fixed;
        printf("Bill %d original total %.2f net %.2f | corrected total %.2f net %.2f\\n",
               i+1,total,net,fixed,fixed_net);
    }
    puts("count = count++ + 1 has undefined behaviour: unsequenced modification/access.");
    puts("Use count++ alone. -Wall may warn about sequence-point issues; warnings vary by compiler.");
    return 0;
}
