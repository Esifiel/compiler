// #include <stdio.h>

// void quicksort(int *A, int len)
// {
//     if (len < 2)
//         return;
//     int pivot = A[len / 2];
//     int i, j;
//     for (i = 0, j = len - 1;; i++, j--)
//     {
//         while (A[i] < pivot)
//             i++;
//         while (A[j] > pivot)
//             j--;
//         if (i >= j)
//             break;
//         int temp = A[i];
//         A[i] = A[j];
//         A[j] = temp;
//     }
//     quicksort(A, i);
//     quicksort(A + i, len - i);
// }

int main(void)
{
    int a;
    double b;
    char c;
    // int a[10010] = {0};
    // int n;
    // scanf("%d", &n);
    // for (int i = 0; i < n; i++)
    //     scanf("%d", &a[i]);
    // quicksort(a, n);
    // for (int i = 0; i < n; i++)
    //     printf("%d\n", a[i]);

    return 0;
}