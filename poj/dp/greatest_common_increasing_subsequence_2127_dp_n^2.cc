
#include <stdio.h>
#include <string.h>

// 11437641	fly2best	2127	Accepted	2728K	94MS	G++	2332B	2013-04-05 11:32:22  O(n^2)
// 11437637	fly2best	2127	Accepted	2728K	1563MS	G++	2349B	2013-04-05 11:31:35 O(n^3)
// 11437154	fly2best	2127	Wrong Answer			G++	1989B	2013-04-05 09:18:34
//
// 参考资料
// https://www.chenyajun.com/2011/01/23/5600
// http://www.cnblogs.com/proverbs/archive/2012/10/05/2712029.html

// #define __DEBUG__

const int MAXN = 550;

int a[MAXN];
int b[MAXN];

int dp[MAXN][MAXN];
int pij[MAXN][MAXN];

int stack[MAXN];
int top = 0;

static inline int max(int a, int b) {return a > b ? a : b;}

int main(int argc, const char *argv[])
{

    int m, n;
    int i, j, k;
    int mlen;

    while (scanf("%d", &m) != EOF) {

        for (i = 1; i <= m; ++i)
            scanf("%d", a + i);

        scanf("%d", &n);
        for (i = 1; i <= n; ++i)
            scanf("%d", b + i);

        memset(dp, 0, sizeof(dp));
        memset(pij, 0, sizeof(pij));
        top = 0;

        int ans = 0;
        int maxi = 0;
        int maxj = 0;

        for (i = 1; i <= m; i++) {

            mlen = 0;
            k = 1;

            for(j = 1; j <= n; j++) {

                dp[i][j] = dp[i-1][j];
                pij[i][j] = 0;

                if (b[j] < a[i]) {

                    if( dp[i - 1][j] > mlen) {
                        mlen = dp[i - 1][j];
                        k = j;
                    }
                }

                if (b[j] == a[i]) {
                    dp[i][j] = mlen + 1;
                    pij[i][j] = k;
                }

                if (dp[i][j] > ans) {
                    ans = dp[i][j];
                    maxi = i;
                    maxj = j;
                }
            }
        }

        printf("%d\n", ans);
#ifdef __DEBUG__
        printf("%d %d\n", maxi, maxj);

        printf("dp:\n");
        for (i = 1; i <= m; ++i) {
            for(j = 1; j <= n; ++j)
                printf("%d ", dp[i][j]);
            printf("\n");
        }

        printf("pij:\n");
        for (i = 1; i <= m; ++i) {
            for(j = 1; j <= n; ++j)
                printf("%d ", pij[i][j]);
            printf("\n");
        }
#endif
        i = maxi;
        j = maxj;

        while (top != ans) {

#ifdef __DEBUG__
            // printf("%d ", b[j]);
#endif
            if(pij[i][j] != 0) {
                stack[top++] = b[j];
                j = pij[i][j];
            }
            i--;
        }

        while (top != 0) {
            printf("%d ", stack[--top]);
        }
        printf("\n");
    }

    return 0;
}
