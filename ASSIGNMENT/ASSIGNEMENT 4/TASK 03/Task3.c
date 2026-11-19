#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

struct all_values {
    float celsius;
    int percent;
    char status[8];
};

void show(const struct reading *r)
{
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
        default:
            printf("Unknown reading\n");
    }
}

int main(void)
{
    struct reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY, {.percent = 68}},
        {STATUS, {.status = "OK"}}
    };

    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);
    printf("sizeof structure with all fields = %zu\n", sizeof(struct all_values));

    for (int i = 0; i < 3; i++) show(&log[i]);

    /* Misuse experiment: writing temperature, then reading humidity.
       This reads an inactive union member; its value is not portable/meaningful. */
    struct reading test = {TEMPERATURE, {.celsius = 31.5f}};
    printf("Misuse experiment (inactive member): humidity = %d\n",
           test.value.percent);

    return 0;
}
