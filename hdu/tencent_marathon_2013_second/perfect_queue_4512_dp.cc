
// 7973612	2013-04-03 08:14:32	Accepted	4512	484MS	544K	1534 B	G++	fly2best
// O(n^4)的算法, 尼玛思路终于清晰了
// 这题目有O(n^2)的算法, 改天整理整理

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

        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            head[i][i] = i;
        }

        for (int s = 1; s < n; ++s) {

            for (int i = 0; i + s < n; ++i) {
                int j = i + s;

                dp[i][j] = 0;

                if (a[i] == a[j]) {

                    int imax = 0;

                    for (int is = 0; is < j - i - 1; ++is) {
                        for (int ii = i + 1; ii + is < j ; ++ii) {
                            int ij = ii + is;

                            if (dp[ii][ij] != 0 && a[i] < a[ii]) {

                                if (dp[ii][ij] > imax)
                                    imax = dp[ii][ij];
                            }
                        }
                    }

                    dp[i][j] = imax + 2;
                }
            }
        }

        int max = 0;
        for (int i = 0; i < n; ++i)  {
            for (int j = i; j < n; ++j) {

                if (dp[i][j] > max)
                    max = dp[i][j];
            }
        }

        printf("%d\n", max);
    }

    return 0;
}
