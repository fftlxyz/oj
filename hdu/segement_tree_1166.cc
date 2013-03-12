
// hdu 1166
// 基本的线段树，点更改，区间查询
//7672697	2013-03-01 21:16:39	Accepted	1166	375MS	1004K	2513 B	G++	fly2best
#include <stdio.h>
#include <string.h>

const int MAXN = 50005;

int sum[MAXN << 2];

void build(int l, int r, int rt);
void update(int i, int add, int L, int R, int rt);
int query(int l, int r, int L, int R, int m);
void pushup(int rt);

int main(int argc, const char *argv[])
{
    int casenum;
    int n;
    int casei = 1;
    char oper[16] = {0};

    scanf("%d", &casenum);

    while(casei <= casenum) {
        memset(sum, 0, sizeof(sum));
        scanf("%d", &n);
        build(1, n, 1);
        int i, j;

        printf("Case %d:\n", casei);
        while(scanf("%s", oper) && (oper[0] != 'E')) {
            scanf("%d %d", &i, &j);
            switch(oper[0]) {
                case 'Q':
                    // printf("query:%d %d\n", i, j);
                    printf("%d\n", query(i, j, 1, n, 1));
                    break;
                case 'A':
                    // printf("update:%d %d\n", i, j);
                    update(i, j, 1, n, 1);
                    break;
                case 'S':
                    // printf("update:%d %d\n", i, -j);
                    update(i, -j, 1, n, 1);
                    break;
            }
        }
        ++casei;
    }

    build(1,10,1);
    return 0;
}

void build(int l, int r, int rt)
{
    if (l == r)
        scanf("%d", &sum[rt]);
    else {
        int m = (l + r) / 2;
        build(l ,m, rt << 1);
        build(m + 1 ,r, rt << 1 | 1);
        pushup(rt);
    }
    // printf("%d %d %d\n", l, r, sum[rt]);
}

void pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int i, int add, int L, int R, int rt)
{
    if ( L == R) {
        // if (L != i)
            // printf("error\n");
        sum[rt] += add;
        // printf("%d %d\n", i, sum[rt]);
        return;
    }

    int m = (L + R) >> 1;

    if ( i <= m)
        update(i, add, L, m, rt << 1);
    else
        update(i, add, m + 1, R, rt << 1 | 1);

    pushup(rt);
    // printf("update:%d %d %d\n", L, R, sum[rt]);
}

int query(int l, int r, int L, int R, int rt)
{
    // printf("query: %d %d\n", L, R);
    int ret = 0;
    if(l <= L && r >= R)
        ret = sum[rt];
    else {
        int m = (L + R) >> 1;
        if ( l <= m)
            ret += query(l, r, L, m, rt << 1);
        if ( m + 1 <= r)
            ret += query(l, r, m +1, R, rt << 1 | 1);
    }

    return ret;
}

