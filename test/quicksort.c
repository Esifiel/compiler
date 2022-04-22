// void quicksort(int A[], int len)
// {
//     int i;
//     int j;
//     int pivot;
//     int temp;
    
//     if (len < 2)
//         return;

//     pivot = A[len / 2];
//     for (i = 0, j = len - 1; 1; i = i + 1, j = j - 1)
//     {
//         while (A[i] < pivot)
//             i++;
//         while (A[j] > pivot)
//             j--;
//         if (i >= j)
//             break;
//         temp = A[i];
//         A[i] = A[j];
//         A[j] = temp;
//     }
//     quicksort(A, i);
//     quicksort(A + i, len - i);
// }

// int main()
// {
//     int A[10010] = {0};
//     int n;
//     int i;

//     scanf("%d", &n);
//     for (i = 0; i < n; i = i + 1)
//     {
//         scanf("%d", &A[i]);
//     }

//     quicksort(A, n);
//     for (i = 0; i < n; i = i + 1)
//     {
//         printf("%d\n", A[i]);
//     }

//     return 0;
// }

int main()
{
    int sum = 0, i;
    for(i = 0; i < 100; i++)
        sum += i;
    
    printf("%d\n", sum);

    return 0;
}