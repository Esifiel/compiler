#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int split(char *src, char delim, char *vec[])
{
    int cnt = 0;
    int len = strlen(src);
    int p = 0, q = 0;

    while (p < len && q < len)
    {
        while (src[q] != delim && q < len)
            q++;
        src[q] = 0;
        vec[cnt++] = &src[p];
        p = q + 1;
    }

    return cnt;
}

#define MAXLEN 1000
#define MAXN 100

char name[MAXN][10];
int credit[MAXN];
struct dep
{
    char name[10];
    struct dep *another;
    struct dep *next;
} * dependency[MAXN];
char grade[MAXN];

void extract(char pyfa[][MAXLEN], int n)
{
    char *vec[MAXN] = {0};

    for (int i = 0; i < n; i++)
    {
        int cnt = split(pyfa[i], '|', vec);
        assert(cnt == 4);

        // course name
        strcpy(name[i], vec[0]);
        // course credit
        credit[i] = atoi(vec[1]);
        // dependency
        if (vec[2][0])
        {
            // for ; part
            char *subvec1[MAXLEN] = {0};
            // for , part
            char *subvec2[MAXLEN] = {0};

            // dummy head
            dependency[i] = (struct dep *)calloc(sizeof(struct dep), 1);
            struct dep *p = dependency[i];

            int groups = split(vec[2], ';', subvec1);
            for (int ii = 0; ii < groups; ii++)
            {
                p->another = (struct dep *)calloc(sizeof(struct dep), 1);
                struct dep *tmp = p->another;

                int items = split(subvec1[ii], ',', subvec2);
                for (int jj = 0; jj < items; jj++)
                {
                    tmp->next = (struct dep *)calloc(sizeof(struct dep), 1);
                    strcpy(tmp->next->name, subvec2[jj]);
                    tmp = tmp->next;
                }

                p = p->another;
            }
        }
        // course grade
        if (vec[3][0] && vec[3][0] != '\n')
            grade[i] = vec[3][0];
    }
}

void dump(int index)
{
    printf("course %s:\tcredit: %d\tgrade: %c\n", name[index], credit[index], grade[index] ? grade[index] : ' ');
    if (dependency[index])
    {
        int cnt = 0;
        for (struct dep *p = dependency[index]->another; p; p = p->another)
        {
            printf("choice %d: ", cnt++);
            for (struct dep *tmp = p->next; tmp; tmp = tmp->next)
                printf("%s ", tmp->name);
            puts("");
        }
    }
    else
        puts("no courses required ahead");
    puts("--------------------------------------------");
}

int main()
{
    double gpa = 0;
    int total = 0, taken = 0, remaining = 0;
    char pyfa[MAXN][MAXLEN];
    int cnt;

    // get input
    for (cnt = 0; strcmp(fgets(pyfa[cnt], MAXLEN - 1, stdin), "\n"); cnt++)
        ;

    // get info
    extract(pyfa, cnt);

    for (int i = 0; i < cnt; i++)
    {
        dump(i);
        if (!grade[i] || grade[i] == 'F')
            remaining += credit[i];
    }

    printf("GPA: %.1f\n", gpa);
    printf("Hours Attempted: %u\n", total);
    printf("Hours COmpleted: %u\n", taken);
    printf("Credits Remaining: %u\n", remaining);
    puts("Possible Courses to Take Next");
    if (remaining == 0)
        puts("None - Congratulations!");
    else
    {
        // find recommend
    }

    return 0;
}

// char input[] =	"top1    des1 ip1 ip2\n"
// 		"top2    des1 ip2 ip3\n"
// 		"ip1     extra1 ip1a ipcommon\n"
// 		"ip2     ip2a ip2b ip2c ipcommon\n"
// 		"des1    des1a des1b des1c\n"
// 		"des1a   des1a1 des1a2\n"
// 		"des1c   des1c1 extra1\n";

// ...
// int find_name(item base, int len, const char *name)
// {
// 	int i;
// 	for (i = 0; i < len; i++)
// 		if (!strcmp(base[i].name, name)) return i;
// 	return -1;
// }

// int depends_on(item base, int n1, int n2)
// {
// 	int i;
// 	if (n1 == n2) return 1;
// 	for (i = 0; i < base[n1].n_deps; i++)
// 		if (depends_on(base, base[n1].deps[i], n2)) return 1;
// 	return 0;
// }

// void compile_order(item base, int n_items, int *top, int n_top)
// {
// 	int i, j, lvl;
// 	int d = 0;
// 	printf("Compile order for:");
// 	for (i = 0; i < n_top; i++) {
// 		printf(" %s", base[top[i]].name);
// 		if (base[top[i]].depth > d)
// 			d = base[top[i]].depth;
// 	}
// 	printf("\n");

// 	for (lvl = 1; lvl <= d; lvl ++) {
// 		printf("level %d:", lvl);
// 		for (i = 0; i < n_items; i++) {
// 			if (base[i].depth != lvl) continue;
// 			for (j = 0; j < n_top; j++) {
// 				if (depends_on(base, top[j], i)) {
// 					printf(" %s", base[i].name);
// 					break;
// 				}
// 			}
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

// int main()
// {
// 	int i, n, bad = -1;
// 	item items;
// 	n = parse_input(&items);

// 	for (i = 0; i < n; i++)
// 		if (!items[i].depth && get_depth(items, i, bad) < 0) bad--;

// 	int top[3];
// 	top[0] = find_name(items, n, "top1");
// 	top[1] = find_name(items, n, "top2");
// 	top[2] = find_name(items, n, "ip1");

// 	compile_order(items, n, top, 1);
// 	compile_order(items, n, top + 1, 1);
// 	compile_order(items, n, top, 2);
// 	compile_order(items, n, top + 2, 1);

// 	return 0;
// }