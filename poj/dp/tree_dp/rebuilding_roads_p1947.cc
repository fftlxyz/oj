#include <stdio.h>
#include <string.h>
#include <algorithm>
using std::min;

//11636138	fly2best	1947	Accepted	584K	63MS	G++	2280B	2013-05-26 11:17:00
//11636217	fly2best	1947	Accepted	580K	47MS	G++	2107B	2013-05-26 11:43:33

const int N = 155;

int dp[N][N];

// #define __DEBUG__

//dp[i][j][k] 表示对于结点i, 用前k颗子树, 获取j的子树, 所需的最少的去边数目
//
//dp[i][j][k]
//不包含第k颗子树
//dp[i][j][k] = dp[i][j][k-1] + 1
//包含第k颗子树
//dp[i][j][k] = min( dp[i][j'][k-1] + dp[childk][j - j'][N])
//
//最后的结果为min(dp[i][p][N])

int n, p;

int edge[N][N];

static inline void add_edge(int u, int v)
{
    edge[u][++edge[u][0]] = v;
}


void dfs(int i, int f)
{

    for (int j = 1; j <= edge[i][0]; ++j) {
        int ci = edge[i][j];
        if (ci != f) {
            dfs(ci, i);
        }
    }

    // 初始化
    for (int j = 0; j <= N; ++j)
        dp[i][j] = 255;

    dp[i][1] = 0;

    if (edge[i][0]) {

        // 现在这就是个类似01背包的问题了
        // 压缩了空间
        for (int k = 1; k <= edge[i][0]; ++k) {
            int ci = edge[i][k];
            if (ci != f) {
                for (int j = N; j >= 1; --j) {
                    int tmp = 255;
                    for (int cj = 1; cj < j; ++cj) {
                        tmp = min(tmp, dp[i][j - cj] + dp[ci][cj]);
                    }
                    dp[i][j] = min(tmp, dp[i][j] + 1);
                }
            }
        }
    }
}


int main(int argc, const char *argv[])
{
    while ( scanf("%d%d", &n, &p) == 2) {

        memset(edge, 0, sizeof(edge));

        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);

            add_edge(u, v);
            add_edge(v, u);
        }


        dfs(1, 0);

        //根结点, 没有父结点
        int answer = dp[1][p];
        for (int i = 1; i <= n; ++i) {
            answer = min(answer, dp[i][p] + 1);
        }

        printf("%d\n", answer);

#ifdef __DEBUG__
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
#endif
    }
    return 0;
}
