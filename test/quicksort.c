// #include <stdio.h>

int a;

// void quicksort(int *A, int len)
long quicksort(int len)
{
    int i;
    int j;

    return 1;
    // if (len < 2)
    //     return len;
    // else
    //     return 666;
// //     // int pivot = A[len / 2];
// //     for (i = 0, j = len - 1; 1; i = i + 1, j = j - 1)
// //     {
// //     //     while (A[i] < pivot)
// //     //         i++;
// //     //     while (A[j] > pivot)
// //     //         j--;
// //     //     if (i >= j)
// //     //         break;
// //     //     int temp = A[i];
// //     //     A[i] = A[j];
// //     //     A[j] = temp;
// //     }
// //     // quicksort(A, i);
// //     // quicksort(A + i, len - i);
}

int main(void)
{
    // // int a[10010] = {0};
    // int n;
    // // scanf("%d", &n);
    // int i;
    // for (i = 0; i < n; i = i + 1)
    // {
    //     // scanf("%d", &a[i]);
    // } 
    // // quicksort(a, n);
    // quicksort(n);
    // for (i = 0; i < n; i = i + 1)
    // {
    //     // printf("%d\n", a[i]);
    // }

    int sum;
    int i;
    sum = 0;
    for(i = 0; i < 100; i = i + 1)
    {
        sum = sum + i;
    }
    quicksort(3);

    printf("%d\n", sum);

    return 0;
}