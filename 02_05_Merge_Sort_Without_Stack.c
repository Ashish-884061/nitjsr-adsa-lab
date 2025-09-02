#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int m = left; m <= right; m++)
        arr[m] = temp[m];
}

void mergeSortIterative(int arr[], int n)
{
    int temp[n];
    for (int curr_size = 1; curr_size < n; curr_size *= 2)
    {
        for (int left = 0; left < n - 1; left += 2 * curr_size)
        {
            int mid = left + curr_size - 1;
            int right = (left + 2 * curr_size - 1 < n - 1) ? left + 2 * curr_size - 1 : n - 1;

            if (mid < n - 1)
                merge(arr, temp, left, mid, right);
        }
    }
}

int main()
{
    int arr[] = {9, 5, 1, 3, 7, 6, 8, 2, 4, 0};
    int n = sizeof(arr) / sizeof(int);

    mergeSortIterative(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}