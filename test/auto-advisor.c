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

const int MAXLEN = 1000;
const int MAXN = 100;

char name[MAXN][10];
int credit[MAXN];
// struct dep
// {
//     char name[10];
//     struct dep *another;
//     struct dep *next;
// } * dependency[MAXN];
// char grade[MAXN];

// void extract(char pyfa[][MAXLEN], int n)
// {
//     char *vec[MAXN] = {0};

//     for (int i = 0; i < n; i++)
//     {
//         int cnt = split(pyfa[i], '|', vec);
//         assert(cnt == 4);

//         // course name
//         strcpy(name[i], vec[0]);
//         // course credit
//         credit[i] = atoi(vec[1]);
//         // dependency
//         if (vec[2][0])
//         {
//             // for ; part
//             char *subvec1[MAXLEN] = {0};
//             // for , part
//             char *subvec2[MAXLEN] = {0};

//             // dummy head
//             dependency[i] = (struct dep *)calloc(sizeof(struct dep), 1);
//             struct dep *p = dependency[i];

//             int groups = split(vec[2], ';', subvec1);
//             for (int ii = 0; ii < groups; ii++)
//             {
//                 p->another = (struct dep *)calloc(sizeof(struct dep), 1);
//                 struct dep *tmp = p->another;

//                 int items = split(subvec1[ii], ',', subvec2);
//                 for (int jj = 0; jj < items; jj++)
//                 {
//                     tmp->next = (struct dep *)calloc(sizeof(struct dep), 1);
//                     strcpy(tmp->next->name, subvec2[jj]);
//                     tmp = tmp->next;
//                 }

//                 p = p->another;
//             }
//         }
//         // course grade
//         if (vec[3][0])
//             grade[i] = vec[3][0];
//     }
// }

// void dump(int index)
// {
//     printf("course %s:\tcredit: %d\tgrade: %c\n", name[index], credit[index], grade[index] ? grade[index] : ' ');
//     if (dependency[index])
//     {
//         int cnt = 0;
//         for (struct dep *p = dependency[index]->another; p; p = p->another)
//         {
//             printf("choice %d: ", cnt++);
//             for (struct dep *tmp = p->next; tmp; tmp = tmp->next)
//                 printf("%s ", tmp->name);
//             puts("");
//         }
//     }
//     else
//         puts("no courses required ahead");
//     puts("--------------------------------------------");
// }

int main()
{
    double gpa = 0;
    int total = 0, try = 0, taken = 0, remaining = 0;
    // char pyfa[MAXN][MAXLEN];
    int cnt;

    // get input
    // for (cnt = 0; gets(pyfa[cnt]), strcmp(pyfa[cnt], ""); cnt++)
        // ;

    // // get info
    // extract(pyfa, cnt);

    // for (int i = 0; i < cnt; i++)
    // {
    //     total += credit[i];
    //     if (grade[i] && grade[i] != 'F')
    //     {
    //         taken += credit[i];
    //         switch (grade[i])
    //         {
    //         case 'A':
    //             gpa += credit[i] * 4;
    //             break;
    //         case 'B':
    //             gpa += credit[i] * 3;
    //             break;
    //         case 'C':
    //             gpa += credit[i] * 2;
    //             break;
    //         case 'D':
    //             gpa += credit[i] * 1;
    //             break;
    //         default:
    //             break;
    //         }
    //     }
    //     else if (grade[i] == 'F')
    //         try += credit[i];
    // }
    // try += taken;
    // remaining = total - taken;
    // if (try != 0)
    //     gpa /= try;
    // else
    //     gpa = 0;
    // printf("GPA: %.1f\n", gpa);
    // printf("Hours Attempted: %u\n", try);
    // printf("Hours COmpleted: %u\n", taken);
    // printf("Credits Remaining: %u\n\n", remaining);
    // puts("Possible Courses to Take Next");
    // if (remaining == 0)
    //     puts("None - Congratulations!");
    // else
    // {
    //     // find recommend
    //     // for each course
    //     for (int i = 0; i < cnt; i++)
    //         // if the credits got
    //         if (grade[i] && grade[i] != 'F')
    //             // for other courses
    //             for (int j = 0; j < cnt; j++)
    //                 // delete the course from their dependencies
    //                 if (dependency[j])
    //                     for (struct dep *p = dependency[j]->another; p; p = p->another)
    //                         for (struct dep *prev = p, *cur = p->next; cur;)
    //                             if (!strcmp(cur->name, name[i]))
    //                             {
    //                                 prev->next = cur->next;
    //                                 struct dep *tmp = cur;
    //                                 cur = cur->next;
    //                                 free(tmp);
    //                                 break;
    //                             }
    //                             else
    //                             {
    //                                 prev = cur;
    //                                 cur = cur->next;
    //                             }

    //     for (int i = 0; i < cnt; i++)
    //         if ((!grade[i] || grade[i] == 'F'))
    //             if (!dependency[i])
    //                 printf("%s\n", name[i]);
    //             else
    //                 for (struct dep *p = dependency[i]->another; p; p = p->another)
    //                     if (!p->next)
    //                     {
    //                         printf("%s\n", name[i]);
    //                         break;
    //                     }
    // }

    return 0;
}