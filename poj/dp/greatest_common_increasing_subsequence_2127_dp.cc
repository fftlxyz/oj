
#include <stdio.h>
#include <string.h>

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
            for(j = 1; j <= n; j++) {

                dp[i][j] = 0;
                if (a[i] != b[j]) {
                    dp[i][j] = dp[i-1][j];
                    pij[i][j] = 0;
                } else {
                    for (k = 1; k < j; ++k) {
                        if (dp[i][j] < dp[i - 1][k] && b[k] < b[j]) {
                            dp[i][j] = dp[i - 1][k];
                            pij[i][j] = k;
                        }
                    }
                    dp[i][j] += 1;
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
