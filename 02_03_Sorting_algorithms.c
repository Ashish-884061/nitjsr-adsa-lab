#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to perform insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    // Start from the second element (the first is already 'sorted')
    for (i = 1; i < n; i++)
    {
        // The element to be inserted into the sorted portion
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position.
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Place the key at its correct location
        arr[j + 1] = key;
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    int swapped; // A flag for optimization
    for (i = 0; i < n - 1; i++)
    {
        swapped = 0; // Reset flag for the new pass
        // Last i elements are already in place, so we don't need to check them
        for (j = 0; j < n - i - 1; j++)
        {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1; // Set flag to true if a swap occurred
            }
        }

        // If no two elements were swapped in the inner loop, the array is sorted
        if (swapped == 0)
        {
            break;
        }
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one, move the boundary of the unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in the unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        if (min_idx != i)
        {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

void shellSort(int arr[], int n)
{
    int gap, i, j, temp;

    // Start with a big gap, then reduce the gap
    // Using Knuth's sequence h = 3*h + 1
    for (gap = 1; gap < n / 3; gap = gap * 3 + 1)
        ;

    // After the loop, 'gap' is the largest gap smaller than n/3.
    // We now reduce the gap until it becomes 1.
    for (; gap > 0; gap /= 3)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements arr[0..gap-1] are already in gapped order
        // so we start from the gap-th element and go up to n.
        for (i = gap; i < n; i += 1)
        {
            // Add arr[i] to the elements that have been gap sorted.
            // Save arr[i] in temp and make a hole at position i.
            temp = arr[i];

            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // Pivot is the last element
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If the current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    // Place the pivot in its correct position
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// The main function that implements QuickSort
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        // pi is the partitioning index, arr[pi] is now at the right place
        int pi = partition(arr, low, high);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    i = 0;    // Initial index of first subarray
    j = 0;    // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function that sorts arr[left..right] using merge()
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child = 2*i + 1
    int right = 2 * i + 2; // right child = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // If largest is not the root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// The main function to do heap sort
void heapSort(int arr[], int n)
{
    // 1. Build a maxheap
    // Start from the last non-leaf node (n/2 - 1) and go backwards.
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // 2. One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to the end
        swap(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp (exponent, e.g., 10^i).
void countingSort(int arr[], int n, int exp)
{
    int *output = (int *)malloc(n * sizeof(int)); // output array
    int count[10] = {0};
    int i;

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains the actual
    // position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to the current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

// The main function to that sorts arr[] of size n using Radix Sort
void radixSort(int arr[], int n)
{
    // Find the maximum number to know the number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing the digit number, exp is passed. exp is 10^i
    // where i is the current digit number.
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

void countingSort1(int arr[], int n)
{
    if (n <= 1)
        return;

    // 1. Find the maximum element to determine the range
    int max = getMax(arr, n);

    // 2. Create and initialize the count array
    int *count = (int *)malloc((max + 1) * sizeof(int));
    memset(count, 0, (max + 1) * sizeof(int));

    // 3. Store the frequency of each element
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    // 4. Store the cumulative frequency
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // 5. Build the output array
    int *output = (int *)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 6. Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    // Free allocated memory
    free(count);
    free(output);
}

struct Node
{
    float data;
    struct Node *next;
};

// Function to insert a node into a sorted linked list (Insertion Sort)
void sortedInsert(struct Node **head_ref, struct Node *new_node)
{
    struct Node *current;
    // Special case for the head end
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        // Locate the node before the point of insertion
        current = *head_ref;
        while (current->next != NULL && current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// The main function that sorts arr[] of size n using Bucket Sort
void bucketSort(float arr[], int n)
{
    // 1) Create n empty buckets
    struct Node **buckets = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i = 0; i < n; i++)
    {
        buckets[i] = NULL;
    }

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++)
    {
        int bucketIndex = n * arr[i];
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        // Insert into the bucket's linked list in a sorted manner
        sortedInsert(&buckets[bucketIndex], newNode);
    }

    // 3) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        struct Node *current = buckets[i];
        while (current != NULL)
        {
            arr[index++] = current->data;
            struct Node *temp = current;
            current = current->next;
            free(temp); // Free memory
        }
    }
    free(buckets); // Free the main buckets array
}

// Function to print an array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap1(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

// The recursive function that implements Radix Exchange Sort
void radix_exchange_sort_recursive(unsigned int arr[], int left, int right, int bit)
{
    // Stop recursion if the subarray is empty/single or all bits are processed
    if (right <= left || bit < 0)
    {
        return;
    }

    int i = left;
    int j = right;

    // Partition the array based on the current bit
    while (i <= j)
    {
        // Find the first element from the left that has a '1' at the current bit
        while (i <= j && !((arr[i] >> bit) & 1))
        {
            i++;
        }
        // Find the first element from the right that has a '0' at the current bit
        while (i <= j && ((arr[j] >> bit) & 1))
        {
            j--;
        }

        // If i and j haven't crossed, swap the elements
        if (i < j)
        {
            swap1(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Recursively sort the two partitions ('0's and '1's) on the next bit
    radix_exchange_sort_recursive(arr, left, j, bit - 1);
    radix_exchange_sort_recursive(arr, i, right, bit - 1);
}

// Main function to call the recursive sort
void radixExchangeSort(unsigned int arr[], int n)
{
    // Start sorting from the most significant bit (31 for a 32-bit unsigned int)
    radix_exchange_sort_recursive(arr, 0, n - 1, 31);
}

// struct Node
// {
//     int data;
//     struct Node *next;
// };

// Function to insert a node into a sorted linked list (Insertion Sort)
void sortedInsert1(struct Node **head_ref, struct Node *new_node)
{
    struct Node *current;
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next != NULL && current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Function to find the maximum element in an array
int findMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// The main sorting function
void addressCalculationSort(int arr[], int n)
{
    // Find max element to create a suitable hash function
    int max = findMax(arr, n);

    // Create n empty "address" slots (buckets)
    struct Node **addresses = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i = 0; i < n; i++)
    {
        addresses[i] = NULL;
    }

    // Map elements to addresses
    for (int i = 0; i < n; i++)
    {
        // Simple linear hash function: h(key) = (key * n) / (max + 1)
        int address = (long long)arr[i] * n / (max + 1);

        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;

        // Insert into the list at the calculated address
        sortedInsert1(&addresses[address], newNode);
    }

    // Gather elements back into the original array
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        struct Node *current = addresses[i];
        while (current != NULL)
        {
            arr[index++] = current->data;
            struct Node *temp = current;
            current = current->next;
            free(temp); // Free memory
        }
    }
    free(addresses); // Free the main address array
}

// Main function to test the algorithm
int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: \n");
    printArray(arr, n);

    // quickSort(arr, 0, n - 1);
    // mergeSort(arr, 0, n - 1);
    // countingSort1(arr, n);
    // bucketSort((float *)arr, n);
    // radixExchangeSort((unsigned int *)arr, n);
    addressCalculationSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}