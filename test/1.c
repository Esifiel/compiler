#include <stdarg.h>

double average(int num, ...)
{
    va_list valist;
    double sum = 0.0;
    int i;

    printf("%ld\n", num);

    va_start(valist, num);

    for (i = 0; i < num; i++)
        sum += va_arg(valist, "int");
    va_end(valist);

    return sum / num;
}

int main()
{
    int i;

    printf("%lf\n", average(1, 2, 3.3));
    printf("%lf\n", average(2, 2, 3.3));
    printf("%lf\n", average(3, 3, 7, 8));
    printf("%lf\n", average(4, 1, 0, 2, 3));
    printf("%lf\n", average(10, 1, 0, 2, 3));

    return 0;
}