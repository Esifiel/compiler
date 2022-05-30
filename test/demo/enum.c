enum color
{
    RED,
    BLUE,
    GREEN,
    YELLOW
};
enum color2
{
    PURPLE,
    ORANGE = 1 << 31,
    BLACK,
    WHITE = 14
};

void f(enum color c)
{
    switch (c)
    {
    case RED:
        puts("red");
        break;
    case BLUE:
        puts("blue");
        break;
    case GREEN:
        puts("green");
        break;
    case YELLOW:
        break;
    }
}

int main()
{
    printf("enum color RED = %d, BLUE = %d, GREEN = %d, YELLOW = %d\n", RED, BLUE, GREEN, YELLOW);
    printf("enum color2 PURPLE = %d, ORANGE = %d, BLACK = %d, WHITE = %d\n", PURPLE, ORANGE, BLACK, WHITE);

    f(RED);
    f(2);

    return 0;
}