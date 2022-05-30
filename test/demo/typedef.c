typedef int INT;
typedef INT INTINT;

struct node {
    struct node *left;
    struct node *right;
};
typedef struct node NODE;

typedef struct {
    int a;
    double b;
} ST;

int main()
{
    INT a = 1;
    INTINT b = 2;

    NODE new;
    ST tmp;

    printf("a = %d, b = %d\n", a, b);

    new.left = 0;
    new.right = 0;
    printf("left = %p, right = %p\n", new.left, new.right);

    tmp.a = 11;
    tmp.b = 2.2;
    printf("a = %d, b = %lf\n", tmp.a, tmp.b);

    return 0;
}