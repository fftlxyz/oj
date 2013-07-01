
// 11440582	fly2best	3974	Accepted	10128K	235MS	G++	1244B	2013-04-05 21:16:51

#include <cstdio>
#include <algorithm>
using std::min;
using std::max;

const int MAXN = 1000010;

char str[MAXN << 1];
int p[MAXN << 1];

int n;
void input();
int manacher(char * str, int n);

int main(int argc, const char *argv[])
{
    int i = 1;
    while (1) {
        input();
        // printf("%s %d\n", str + 1, n);

        if (str[2] == 'E') {
            break;
        }

        printf("Case %d: %d\n", i++, manacher(str, n));

    }
    return 0;
}

//过于精妙，需要再理理...
int manacher(char * str, int n)
{
    int id;
    int i;
    int mx = 0;

    for (i = 1; i <= n; ++i) {
        p[i] = 1;
        if (mx > i) {
            p[i] = min(p[2*id -i], mx -i);
        }

        while (str[i + p[i]] == str[i - p[i]])
            p[i]++;

        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }

    int ret = -1;
    for (i = 1; i <= n; ++i)
        ret = max(ret, p[i] - 1);
    return ret;

}

void input()
{
    int i = 1;

    int ch;
    str[0] = '$';
    str[1] = '#';
    while ( (ch=getchar()) != EOF && ch != '\n') {
        str[2 * i] = ch;
        str[2 * i + 1] = '#';
        ++i;
    }
    str[2*i] = '\0';
    n = 2*i - 1;
}



