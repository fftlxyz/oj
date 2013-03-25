#include <stdio.h>
#include <string.h>

//以前没注意啊, kmp可以用来就这个powerstring

const int N = 1001000;
char buf[N]= {0};
int next[N];

void getnext(char *str, int m, int *next);

int main(int argc, const char *argv[])
{

    while (scanf("%s", buf) == 1 && buf[0] != '.') {
        int n = strlen(buf);

        getnext(buf, n, next);

        if (buf[(n - 1)] == buf[next[n -1]]) {
            int plen = n - 1 - next[n - 1];

            if ( n % plen == 0) {
                printf("%d\n", n / plen);
            }
            else {
                printf("1\n");
            }
        } else
            printf("1\n");

    }

    return 0;
}


void getnext(char *str, int m, int *next)
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
