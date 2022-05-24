union st {
    int a;
    double b;
    long c;
    char name[0x10];
} ss;

struct abc {
    int a;
    double b;
} hello;

double average(int num, ...)
{
    // va_list valist;
    double sum = 0.0;
    // int i;

    // va_start(valist, num);
    // for (i = 0; i < num; i++)
    //    sum += va_arg(valist, int);
    // va_end(valist);
 
    return sum / num;
}

int main()
{
    int i;
    
    ss.a = 0xffffffff;
    printf("%d", ss.a);
    ss.b = 1.2;
    printf("\n%lf\n", ss.b);
    printf("%d", ss.a);

    puts("");

    printf("%lf\n", average(2, 2, 3));
    printf("%lf\n", average(3, 3, 7, 8, 9));

    return 0;
}