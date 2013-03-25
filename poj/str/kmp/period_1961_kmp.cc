
#include <stdio.h>

const int MAXN = 1000100;

char buf[MAXN] = {0};
int next[MAXN] = {0};

void getnext(char *str, int m, int *next);

int main(int argc, const char *argv[])
{
    int n;

    int casei = 1;
    while (scanf("%d%s", &n, buf) == 2) {

        getnext(buf, n, next);
        printf("Test case #%d\n",casei++);

        for (int i = 1; i < n; ++i) {
            if (buf[i] == buf[next[i]] && ( (i+1) % (i - next[i]) == 0)) {
                printf("%d %d\n", i + 1, (i + 1)/(i - next[i]));
            }
        }

        printf("\n");
    }

    return 0;
}

void getnext(char *str,int m, int *next)
{
    int i = 0;
    int j = -1;
    next[i] = j;

    while (i < m) {
        while (j >= 0 && str[i] != str[j])
            j = next[j];

        ++i; ++j;
        next[i] = j;
    }
}
