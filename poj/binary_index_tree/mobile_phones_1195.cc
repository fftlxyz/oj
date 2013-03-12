#include <stdio.h>
#include <string.h>

// 11336136	fly2best	1195	Time Limit Exceeded			G++	1156B	2013-03-11 08:32:35
// 11336153	fly2best	1195	Time Limit Exceeded			G++	1200B	2013-03-11 08:45:55
// 循环的时候写错了下标， TLE了两次...
// 11336158	fly2best	1195	Accepted	5120K	1032MS	G++	1200B	2013-03-11 08:48:51

const int MAXN = 1100;
int S[MAXN][MAXN];
int n;

static inline int lowbit(int x) {return x & -x;}
void add(int x, int y, int a);
int sum(int x, int y);

int main(int argc, const char *argv[])
{
    int oper;

    while (scanf("%d", &oper) != EOF && oper != 3) {

        if (oper == 1) {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            add(x, y, a);
        } else if(oper == 2) {
            int l, b ,r, t;
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", sum(r,t) - sum(l-1, t) - sum(r, b - 1) + sum(l - 1, b - 1));
        } else if (oper == 0) {
            scanf("%d", &n);
            memset(S, 0, sizeof(S));
        }
    }

    return 0;
}


void add(int x, int y, int a)
{
    x = x + 1;
    y = y + 1;
    int i, j;

    for(i = x; i <= n; i += lowbit(i))
        for(j =y; j <= n; j+= lowbit(j))
            S[i][j] += a;
}


int sum(int x, int y)
{
    x += 1;
    y += 1;
    int ret = 0;
    int i, j;

    for(i = x; i >0 ; i -= lowbit(i))
        for(j =y; j >0 ; j-= lowbit(j))
            ret += S[i][j];

    return ret;
}
