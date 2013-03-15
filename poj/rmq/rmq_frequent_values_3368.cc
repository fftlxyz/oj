// 11346499	fly2best	3368	Accepted	4952K	1157MS	G++	3325B	2013-03-13 22:10:02
// 题目不难, 不知道哪里写挫了, 跑了1s+
// 总结啊, 别人怎么写的, 我的怎么这么慢...
#include <stdio.h>
const int MAXN = 100100;
int n, q;

int dp_max[MAXN][21];

int array[MAXN];

int X[MAXN];
int frequent[MAXN];
int sum[MAXN]; //sum frequent
int m = 0;

void process();
int bin_search(int key, int *p, int n);
int query(int x1, int x2);
static int inline max(int a, int b) {return a > b ? a: b;}

int main(int argc, const char *argv[])
{

    while( scanf("%d%d", &n, &q) == 2) {

        for(int i = 0; i < n; ++i) {
            scanf("%d", array + i);
        }

        process();

        for(int k = 0; k < q; ++k) {
            int i, j;
            scanf("%d%d", &i, &j);
            printf("%d\n", query(i - 1, j - 1));
        }

    }

    return 0;
}

int query(int x1, int x2)
{
    int y1 = bin_search(array[x1], X, m);
    int y2 = bin_search(array[x2], X, m);

    if (y1 == y2)
        return x2 - x1 + 1;

    // printf("%d %d\n", x1, x2);
    // printf("%d %d\n", y1, y2);

    int k1, k2;
    k1 = y1;
    k2 = y2;

    //x1 - 1是否是区间的结尾
    //if so sum[y1 - 1] == x1

    //非区间的开始
    int minleft = -1;
    if (y1 == 0 && x1 != 0) {
        ++k1;
        minleft = sum[0] - x1;
    }

    if ( y1 != 0 && sum[y1 - 1] != x1) {
        ++k1;
        minleft = frequent[y1] - (x1 - sum[y1 - 1]);
    }

    int minright = -1;
    if (y2 == 0 && x2 != sum[0] - 1) {
        --k2;
        minright = x2;
    }
    if (y2 != 0 && sum[y2] != x2 + 1) {
        --k2;
        minright = x2 + 1 - sum[y2 - 1];
    }


    int rmax = -1;
    if ( k1 != m && k2 != -1) {
        int j = 0;
        while ((k2 + 1 - k1) >> j)
            ++j;
        --j;
        rmax = max(dp_max[k1][j], dp_max[k2 + 1 - (1 << j)][j]);
    }

    rmax = max(rmax, minleft);
    rmax = max(rmax, minright);

    return rmax;
}

void process()
{
    X[0] = array[0];
    frequent[0] = 1;
    m = 0;
    for(int i = 1; i < n; ++i) {
        if (array[i] != array[i - 1]) {
            ++m;
            X[m] = array[i];
            frequent[m] = 1;
        } else {
            frequent[m] += 1;
        }
    }
    ++m;

    // for (int i = 0; i < m; ++i) {
        // printf("%d ",X[i]);
    // }
    // printf("\n");

    // for (int i = 0; i < m; ++i) {
        // printf("%d ", frequent[i]);
    // }
    // printf("\n");

    sum[0] = frequent[0];
    for (int i = 1; i < m; ++i) {
        sum[i] = frequent[i] + sum[i-1];
    }

    // for (int i = 0; i < m; ++i) {
        // printf("%d ",sum[i]);
    // }
    // printf("\n");


    //dp[i][j] 表示[i, i + 2^j)上的最大值
    for (int i = 0; i < m; ++i) {
        dp_max[i][0] = frequent[i];
    }

    for (int j = 1; (1 << j) <= m; ++j) {
        int len = 1 << j;
        for (int i = m - len; i > -1 ; --i) {
                dp_max[i][j] = max(dp_max[i][j - 1], dp_max[i + (len >> 1)][j - 1]);
        }
    }

}

int bin_search(int key, int *p, int n)
{
    int l = 0;
    int r = n;

    while(l < r) {
        int m = (l + r) >> 1;
        if (p[m] == key) {
            return m;
        } else {
            if (key > p[m] )
                l = m + 1;
            else {
                r = m;
            }
        }
    }
    //what i am curious, if can not find , what m is
    return -1;
}
