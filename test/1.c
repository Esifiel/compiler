int main()
{
    char char_a = 127;
    short short_a = 1 << 15;

    int int_a = -1;
    unsigned int uint_a = 1;

    float float_a = 1.2;
    double double_a = -2.3;

    printf("before ++, char_a = %d, short_a = %d\n", char_a, short_a);
    char_a++;
    ++short_a;
    printf("after ++, char_a = %d, short_a = %d\n", char_a, short_a);

    printf("int_a = %d, uint_a = %d\n", int_a, uint_a);
    int_a = int_a * 53 / 7;
    printf("after * 53 / 7, int_a = %d\n", int_a);
    uint_a -= 2;
    printf("after -= 2, uint_a = %d\n", uint_a);
    uint_a /= 7;
    printf("after /= 7, uint_a = %d\n", uint_a);

    uint_a = 0x80000000;
    printf("%d\n", -1);
    printf("%d\n", 1 << 31);
    printf("%d\n", uint_a);
    printf("%u\n", uint_a);

    printf("float_a = %f, double_a = %lf\n", float_a, double_a);
    printf("float_a * double_a = %lf\n", float_a * double_a);

    return 0;
}