#include <stdio.h>

int maxVal = 0;

void knapsack(int i, int n, int W, int wt[], int val[], int currentWeight, int currentValue) {
    if (i == n) {
        if(currentValue > maxVal) maxVal = currentValue;
        return;
    }

    if(currentWeight + wt[i] <= W)
        knapsack(i+1, n, W, wt, val, currentWeight + wt[i], currentValue + val[i]);

    knapsack(i+1, n, W, wt, val, currentWeight, currentValue);
}

int main() {
    int n, W;
    printf("Enter number of items and capacity: ");
    scanf("%d %d", &n, &W);

    int val[n], wt[n];
    printf("Enter values: ");
    for(int i=0;i<n;i++) scanf("%d", &val[i]);

    printf("Enter weights: ");
    for(int i=0;i<n;i++) scanf("%d", &wt[i]);

    knapsack(0, n, W, wt, val, 0, 0);
    printf("Maximum value: %d\n", maxVal);
    return 0;
}
