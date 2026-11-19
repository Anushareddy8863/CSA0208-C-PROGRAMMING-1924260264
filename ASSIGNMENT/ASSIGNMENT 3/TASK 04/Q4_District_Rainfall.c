/* Q4 - Two-Dimensional Arrays: District Rainfall Records
   Compile: gcc Q4_District_Rainfall.c -o q4
   Run: ./q4
*/
#include <stdio.h>

#define DISTRICTS 38
#define MONTHS 12

void row_totals(const double rain[][MONTHS], double totals[], int rows) {
    for(int i=0;i<rows;i++) {
        totals[i]=0;
        for(int j=0;j<MONTHS;j++) totals[i]+=rain[i][j];
    }
}
void monthly_averages(const double rain[][MONTHS], double avg[], int rows) {
    for(int j=0;j<MONTHS;j++) {
        double sum=0;
        for(int i=0;i<rows;i++) sum+=rain[i][j];
        avg[j]=sum/rows;
    }
}
void find_maximum(const double rain[][MONTHS], int rows,
                  double *maximum, int *district, int *month) {
    *maximum=rain[0][0]; *district=0; *month=0;
    for(int i=0;i<rows;i++) for(int j=0;j<MONTHS;j++)
        if(rain[i][j]>*maximum) {
            *maximum=rain[i][j]; *district=i; *month=j;
        }
}
double state_average(const double rain[][MONTHS], int rows) {
    double sum=0;
    for(int i=0;i<rows;i++) for(int j=0;j<MONTHS;j++) sum+=rain[i][j];
    return sum/(rows*MONTHS);
}
int main(void) {
    /* Demonstration data; replace/read these values for the actual 38x12 dataset. */
    double rain[DISTRICTS][MONTHS];
    for(int i=0;i<DISTRICTS;i++)
        for(int j=0;j<MONTHS;j++)
            rain[i][j]=(double)((i*17+j*23)%250);

    double totals[DISTRICTS], averages[MONTHS], maximum, overall;
    int wet_district, wet_month;
    row_totals(rain,totals,DISTRICTS);
    monthly_averages(rain,averages,DISTRICTS);
    find_maximum(rain,DISTRICTS,&maximum,&wet_district,&wet_month);
    overall=state_average(rain,DISTRICTS);

    printf("Annual totals (district 1 to 38):\n");
    for(int i=0;i<DISTRICTS;i++) printf("District %2d: %.1f mm\n",i+1,totals[i]);
    printf("Monthly averages: ");
    for(int j=0;j<MONTHS;j++) printf("%.1f ",averages[j]);
    printf("\nState average rainfall = %.2f mm\n",overall);
    printf("Wettest: district %d, month %d, rainfall %.1f mm\n",
           wet_district+1,wet_month+1,maximum);
    puts("Districts below 60% of state average annual rainfall:");
    for(int i=0;i<DISTRICTS;i++)
        if(totals[i] < 0.60 * overall * MONTHS)
            printf("%d ",i+1);
    putchar('\n');
    return 0;
}
