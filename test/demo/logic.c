int main()
{
    int a = 1;

    if (a != 1)
        puts("a != 1");
    else
        puts("a = 1");

    if (!a || a + 1 == 2)
        puts("a + 1 == 2");
    else
        puts("no");

    // short circuit logic
    if ((a == 0) && (a += 1))
        ;
    printf("a = %d\n", a);

    if ((a == 1) || (a += 1))
        ;
    printf("a = %d\n", a);

    return 0;
}