// rmq sparse table 1A
// 思路很简单阿, 但是..， 没有一次写对，调了很长时间
// 为什么思路很简单的东西, 我却写了这么长时间呢?
// 反思, 总结
// 11343486	fly2best	3264	Accepted	6848K	3407MS	G++	1724B
// 我求(1 << j) < n, 写错了, 应该是等于
// 这个题目的数据水了
#include <stdio.h>

const int MAXN = 50005;

int dp_min[MAXN][16];
int dp_max[MAXN][16];

int height[MAXN];

static inline int max(int a ,int b) {return a > b ? a : b;}
static inline int min(int a ,int b) {return a < b ? a : b;}

int main(int argc, const char *argv[])
{

    int n, q;

    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d",height + i);
    }

    //construct
    // dp[i][j] stands for max or min value [i, i + 2^j)
    // dp[i][j] = max(dp[i, j -1], dp[i + 2^(j-1), j - 1])
    //
    // dp[i][0] 表示 height[i, i + 1) 即 height[i]
    for (int i = 0; i < n; ++i) {
        dp_min[i][0] = dp_max[i][0] =  height[i];
    }

    for (int j = 1; (1 << j) < n; ++j) {
        int len = 1 << j;
        for (int i = n - 1; i > -1 ; --i) {
            if (i + len <= n) {
                // printf("range:%d %d %d %d\n", i, i + len, i + len / 2, i + len/2 + (1 << (j -1)));
                dp_min[i][j] = min(dp_min[i][j - 1], dp_min[i + (len >> 1)][j - 1]);
                dp_max[i][j] = max(dp_max[i][j - 1], dp_max[i + (len >> 1)][j - 1]);
                // printf("min_max:%d %d %d %d\n", i, i + len, dp_min[i][j], dp_max[i][j]);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a -= 1;
        b -= 1;
        int j = 0;
        while ((b + 1 - a) >> j)
            ++j;
        --j;
        // printf("%d %d:%d %d\n", a, b, 1 << j, b + 1 - (1 << j));
        int rmax = max(dp_max[a][j], dp_max[b + 1 - (1 << j)][j]);
        int rmin = min(dp_min[a][j], dp_min[b + 1 - (1 << j)][j]);
        printf("%d\n", rmax - rmin);
    }

    return 0;
}
