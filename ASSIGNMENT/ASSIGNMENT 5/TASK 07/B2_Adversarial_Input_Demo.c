#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char fixedName[20];
    char line[100];

    printf("Enter a donor name (fgets safely reads up to 99 chars): ");
    if (!fgets(line, sizeof line, stdin)) {
        fprintf(stderr, "No input received\n");
        return 1;
    }
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) >= sizeof fixedName) {
        printf("Name is too long for fixedName[%zu]; rejecting safely.\n",
               sizeof fixedName);
        return 1;
    }
    strcpy(fixedName, line);
    printf("Accepted donor name: %s\n", fixedName);

    FILE *fp = fopen("missing_donor_file.txt", "r");
    if (!fp) perror("Could not open donor data file");

    printf("argc=%d\n", 0); /* CLI validation example is in A3 file. */
    return 0;
}
