void quicksort(int A[], int len)
{
    int i, j, pivot, temp;

    if (len < 2)
        return;

    pivot = A[len / 2];
    for (i = 0, j = len - 1; ; i++, j--)
    {
        while (A[i] < pivot)
            i++;
        while (A[j] > pivot)
            j--;
        if (i >= j)
            break;
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
    quicksort(A, i);
    quicksort(A + i, len - i);
}

int main()
{
    int A[10010] = {0};
    int n, i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    quicksort(A, n);

    for (i = 0; i < n; i++)
        printf("%d\n", A[i]);

    return 0;
}