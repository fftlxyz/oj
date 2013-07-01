
#include <stdio.h>
#include <string.h>

const int N = 210;

int dp[N][N];
int head[N][N];
int a[N];

int main(int argc, const char *argv[])
{
    int casenum;
    int n;

    scanf("%d", &casenum);


    while (casenum--) {
        scanf("%d", &n);

        for (int i = 0; i< n; ++i) {
            scanf("%d", a + i);
        }

        memset(dp, 0, sizeof(dp));

        for (int i = 0;i < n; ++i) {
            dp[i][i] = 1;
            head[i][i] = a[i];
            dp[i][i-1] = 0;
            head[i][i-1] = 300;
        }




        // dp[i][j], 表示的到底什么意思
        // 怎么转化为子问题的

        for (int s = 1; s < n; ++s) {

            for (int i = 0; i + s < n; ++i) {

                int j = s + i;

                dp[i][j] = -1;

                //包含i和j
                if (a[i] == a[j] && a[i] < head[i+1][j-1]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                    head[i][j] = a[i];
                }

                //不包含i, 可能包含j
                if (dp[i][j] < dp[i + 1][j]) {
                    dp[i][j] = dp[i + 1][j];
                    head[i][j] = head[i + 1][j];
                }

                //不包含j, 可能包含i
                if (dp[i][j] < dp[i][j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                    head[i][j] = head[i][j - 1];
                }

            }
        }


        for (int s = 0; s < n; ++s) {
            for (int i = 0; i + s < n; ++i) {
                printf("(%d %d): %d ", i, i + s, dp[i][i+s]);
            }
            printf("\n");
        }

        printf("%d\n", dp[0][n-1]);
    }


    return 0;
}
