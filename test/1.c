#include "demo/header.h"

#define DEBUG
#define x 1
#define y 2
#define X x
#define Y y
#define BBB(x, y) x * y + AAA
#define AAA CCC
#define CCC 10
#define PRINT_MAX(x, y)         \
    if (x > y)                  \
        printf("%d\n", x);      \
    else                        \
        printf("%d\n", y);
#define STR(s1, s2) s1 s2

int main()
{
    printf("variable 'a' defined in header.h = %d\n", a);

#ifdef DEBUG
    puts("debug macro has been defined");
#else
    puts("not defined");
#endif

#undef DEBUG

#ifdef DEBUG
    puts("debug macro is still defined");
#else
    puts("debug macro has been undefined");
#endif

    printf("macro AAA = %d\n", AAA);
    printf("macro BBB(2, 3) = %d\n", BBB(2, 3));
    printf("macro BBB(2 + 3, 3 + 2) = %d\n", BBB(2 + 3, 3 + 2));
    printf("macro X = %d, Y = %d\n", X, Y);
    printf("macro BBB(BBB(2, 3), 4) = %d\n", BBB(BBB(2, 3), 4));

    PRINT_MAX(3, 5)

    printf("STR(\"a\", \"b\") = %s\n", STR("a", "b"));

    return 0;
}