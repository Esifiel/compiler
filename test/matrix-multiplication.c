int a[30][40];
int b[30][40];
int c[30][40];

int main()
{
    int ma, na, mb, nb;
    int i, j, k;

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
        for (i = 0; i < ma; i++)
            for (j = 0; j < nb; j++)
            {
                // c[i][j] = 0;
                // for (k = 0; k < na; k++)
                //     c[i][j] += a[i][k] * b[k][j];
            }

    for (i = 0; i < ma; i++)
    {
        for (j = 0; j < nb; j++)
            printf("%10d", c[i][j]);
        puts("");
    }

    return 0;
}