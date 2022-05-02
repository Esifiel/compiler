int a[30][40];
int b[30][40];
int c[30][40];

int main()
{
    int ma, na, mb, nb;
    int i, j;

    scanf("%d %d", &ma, &na);
    for (i = 0; i < ma; i++)
        for (j = 0; j < na; j++)
            scanf("%d", &a[i][j]);

    scanf("%d %d", &mb, &nb);
    for (i = 0; i < mb; i++)
        for (j = 0; j < nb; j++)
            scanf("%d", &b[i][j]);

    if (na != mb)
        puts("Incompatible Dimensions");
    else
    {
        for(i = 0; i < ma; i++)
        {
            printf("%d\n", 1);
        }
    }

    return 0;
}