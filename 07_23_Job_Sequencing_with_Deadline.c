#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;    
    int deadline; 
    int profit;  
} Job;

int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    int slot[maxDeadline + 1];
    char result[maxDeadline + 1];

    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = 0;
        result[i] = '-';
    }

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    printf("Job sequence to maximize profit: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%c ", result[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Job ID, Deadline, Profit (e.g., A 2 100): ");
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}
