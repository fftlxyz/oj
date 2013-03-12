//这个题目的思路值得整理
//思路很重要
//怎么把二维问题转化了一维问题，从而可以利用线段树解决掉
// 11316760	fly2best	2352	Accepted	1012K	422MS	G++	1343B	2013-03-06 08:31:44
// 没注意区间范围
// 11316756	fly2best	2352	Runtime Error			G++	1343B	2013-03-06 08:27:01

#include <stdio.h>
#include <string.h>

const int MAXN = 32100;

int sum[MAXN<<2];
int level[MAXN];


void update(int a, int l, int r, int rt)
{
    if (l == r) {
        sum[rt]++;
    }
    else {
        int m = (l + r) >> 1;
        if (a <= m)
            update(a, l, m, rt << 1);
        else
            update(a, m + 1, r, rt << 1 | 1);

        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    }
}

int query(int y1, int y2, int l, int r, int rt)
{
    if (y1 <= l && r <= y2)
        return sum[rt];
    else {
        int ret = 0;
        int m = (l + r) >> 1;
        if (y1 <= m)
            ret += query(y1, y2, l, m, rt << 1);
        if (m + 1 <= y2)
            ret += query(y1, y2, m + 1, r, rt << 1 | 1);
        return ret;
    }
}

int main(int argc, const char *argv[])
{
    memset(sum, 0, sizeof(sum));
    memset(level, 0, sizeof(level));
    int n, i, leveli;
    int a, b;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        leveli = query(0, a, 0, MAXN, 1);
        // printf("%d ", leveli);
        ++level[leveli];
        update(a, 0, MAXN, 1);
    }
    // printf("\n");
    for (i = 0; i < n; ++i) {
        printf("%d\n", level[i]);
    }
    return 0;
}
