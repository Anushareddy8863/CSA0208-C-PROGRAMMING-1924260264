#include <stdio.h>
enum { LIGHT=0, FAN=1, AC=2, HEATER=3, PUMP=4 };
unsigned char switch_on(unsigned char r,int d){return (unsigned char)(r | (1u<<d));}
unsigned char switch_off(unsigned char r,int d){return (unsigned char)(r & ~(1u<<d));}
unsigned char toggle(unsigned char r,int d){return (unsigned char)(r ^ (1u<<d));}
int is_on(unsigned char r,int d){return (r & (1u<<d)) != 0u;}
void show(unsigned char r){for(int b=7;b>=0;b--)putchar(((r>>b)&1u)?'1':'0');putchar('\\n');}
int main(void){
    unsigned char reg=0;
    reg=switch_on(reg,LIGHT); /* 1 */
    reg=switch_on(reg,AC);    /* 5 */
    show(reg);
    reg=toggle(reg,FAN);      /* 7 */
    reg=switch_off(reg,LIGHT);/* 6 */
    show(reg);
    printf("AC is %s, PUMP is %s\\n",is_on(reg,AC)?"ON":"OFF",is_on(reg,PUMP)?"ON":"OFF");
    return 0;
}
