#include "header.h"

#define DEBUG

int main()
{
    printf("variable 'a' defined in header.h = %d\n", a);

#ifdef DEBUG
    puts("debug macro has been defined");
#else
    puts("not defined");
#endif

    return 0;
}