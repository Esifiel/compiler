double average(int num, ...)
{
    va_list valist;
    double sum = 0.0;
    int i;

    va_start(valist, num);

    for (i = 0; i < num; i++)
        sum += va_arg(valist, "int");
    va_end(valist);

    return sum / num;
}

int main()
{
    printf("avg(1) = %lf\n", average(1, 2));
    printf("avg(2, 3) = %lf\n", average(2, 2, 3));
    printf("avg(3, 7, 8) = %lf\n", average(3, 3, 7, 8));
    printf("avg(1, 0, 2, 3) = %lf\n", average(4, 1, 0, 2, 3));
    printf("avg(1, 0, 2, 3, 5) = %lf\n", average(5, 1, 0, 2, 3, 5));

    return 0;
}
