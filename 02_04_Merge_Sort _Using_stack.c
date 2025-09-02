#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int left, right;
} StackNode;

typedef struct
{
    StackNode data[MAX];
    int top;
} Stack;

void push(Stack *s, int left, int right)
{
    if (s->top < MAX - 1)
    {
        s->data[++(s->top)].left = left;
        s->data[s->top].right = right;
    }
}

StackNode pop(Stack *s)
{
    return s->data[(s->top)--];
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int n)
{
    Stack s1, s2;
    s1.top = s2.top = -1;

    // Push initial range
    push(&s1, 0, n - 1);

    // Simulate recursion with two stacks
    while (!isEmpty(&s1))
    {
        StackNode node = pop(&s1);
        int l = node.left, r = node.right;
        if (l < r)
        {
            int m = l + (r - l) / 2;
            push(&s1, l, m);
            push(&s1, m + 1, r);
            push(&s2, l, r); // For merging later
        }
    }

    // Merge in order
    while (!isEmpty(&s2))
    {
        StackNode node = pop(&s2);
        int l = node.left, r = node.right;
        int m = l + (r - l) / 2;
        merge(arr, l, m, r);
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}