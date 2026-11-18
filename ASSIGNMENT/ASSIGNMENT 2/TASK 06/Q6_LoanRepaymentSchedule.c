#include <stdio.h>
int main(void){
    double principal,rate_percent,payment;
    const int LIMIT=360; double balance,interest_total=0.0;int month=0;
    printf("Enter principal, monthly interest rate (percent), repayment: ");
    if(scanf("%lf %lf %lf",&principal,&rate_percent,&payment)!=3){puts("Invalid numeric input.");return 1;}
    if(principal<=0||rate_percent<0||payment<=0){puts("Invalid loan values.");return 1;}
    double r=rate_percent/100.0;
    if(payment<=principal*r){puts("Loan will not amortise: repayment must exceed monthly interest.");return 1;}
    balance=principal;
    puts("Month Opening Interest Payment Closing");
    while(balance>0.005){
        if(month>=LIMIT){puts("Safety stop: 360-month limit reached; revise terms.");return 2;}
        ++month;double opening=balance,interest=opening*r,due=opening+interest;
        double actual=payment<due?payment:due; /* final month pays only amount due */
        balance=due-actual;if(balance<0.005)balance=0.0;interest_total+=interest;
        printf("%5d %7.2f %8.2f %8.2f %8.2f\\n",month,opening,interest,actual,balance);
    }
    printf("Months=%d Total interest=Rs %.2f\\n",month,interest_total);
    return 0;
}
