/* Q7 - Student Council Election Counting
   Compile: gcc Q7_Election_Counting.c -o q7
   Run: ./q7
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 12
#define MAX_VOTES 500000

typedef struct {
    int candidate;
    int votes;
} Result;

int main(void) {
    int candidates,votes;
    int count[MAX_CANDIDATES+1]={0};
    int valid=0,invalid=0;
    printf("Enter number of candidates (1-%d): ",MAX_CANDIDATES);
    if(scanf("%d",&candidates)!=1 || candidates<1 || candidates>MAX_CANDIDATES) {
        puts("Invalid candidate count."); return 1;
    }
    printf("Enter number of votes (0-%d): ",MAX_VOTES);
    if(scanf("%d",&votes)!=1 || votes<0 || votes>MAX_VOTES) {
        puts("Invalid vote count."); return 1;
    }
    int *ballots=malloc((size_t)(votes?votes:1)*sizeof(int));
    if(!ballots) { perror("malloc"); return 1; }
    puts("Enter each vote as a candidate number:");
    for(int i=0;i<votes;i++) {
        if(scanf("%d",&ballots[i])!=1) {
            puts("Invalid input."); free(ballots); return 1;
        }
    }

    clock_t start=clock();
    for(int i=0;i<votes;i++) {
        int v=ballots[i];
        if(v>=1 && v<=candidates) { count[v]++; valid++; }
        else invalid++;
    }
    clock_t end=clock();

    Result result[MAX_CANDIDATES];
    for(int i=0;i<candidates;i++) {
        result[i].candidate=i+1;
        result[i].votes=count[i+1];
    }
    /* Sort candidates by votes descending; candidate number breaks ties. */
    for(int i=0;i<candidates-1;i++)
        for(int j=i+1;j<candidates;j++)
            if(result[j].votes>result[i].votes) {
                Result t=result[i]; result[i]=result[j]; result[j]=t;
            }

    printf("\nValid votes: %d\nInvalid votes: %d\n",valid,invalid);
    puts("Candidate results (descending votes):");
    for(int i=0;i<candidates;i++)
        printf("Candidate %d: %d votes\n",result[i].candidate,result[i].votes);

    if(result[0].votes==0) puts("No valid votes: no winner.");
    else {
        int tie=0;
        for(int i=1;i<candidates && result[i].votes==result[0].votes;i++) tie++;
        if(tie) {
            printf("Tie among %d candidates with %d votes.\n",tie+1,result[0].votes);
        } else printf("Winner: Candidate %d with %d votes.\n",
                      result[0].candidate,result[0].votes);
    }
    printf("Counting CPU time: %.6f seconds\n",
           (double)(end-start)/CLOCKS_PER_SEC);
    free(ballots);
    return 0;
}
