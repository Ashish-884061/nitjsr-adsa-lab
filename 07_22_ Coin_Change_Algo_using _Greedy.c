#include <stdio.h>

void coinChange(int coins[], int n, int amount) {
    printf("Coins used to make change for %d:\n", amount);

    for (int i = 0; i < n; i++) {
        int count = amount / coins[i];
        if (count > 0) {
            printf("%d coin(s) of %d\n", count, coins[i]);
            amount -= count * coins[i];
        }
    }

    if (amount > 0) {
        printf("Change cannot be made completely with given denominations.\n");
    }
}

int main() {
    int coins[] = {100, 50, 20, 10, 5, 2, 1};  
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount;
    printf("Enter the amount to make change: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
