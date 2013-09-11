#include <stdio.h>
#include <string.h>

// 1A, 好久没刷题了, 虽然题目不难, 但还是很开心
// poj 1141
// 472K
// 0MS
// G++
// 1781B
// 2013-09-09 21:15:43

const int N = 105;
int dp[N][N];
int pos[N][N];
char str[N];

void print_bracket(int i, int j);

int main(int argc, const char *argv[])
{
    scanf("%s", str);
    // memcpy(str, "([(]", 4);

    int n = strlen(str);

    for(int i = 0; i < n; ++i){
        dp[i][i] = 1;
        pos[i][i] = i;
    }

    for(int s = 2; s <= n ; ++s) {
        for(int i = 0; i + s <= n; ++i) {

            int j = i + s - 1;

            dp[i][j] = n;

            if ((str[i] == '(' && ')' == str[j]) || (str[i] == '[' && str[j] == ']')) {
                dp[i][j] = dp[i+1][j-1];
                pos[i][j] = -1;
            }

            for(int k = i; k + 1 <= j; ++k) {
                if (dp[i][k] +  dp[k+1][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k+1][j];
                    pos[i][j] = k;
                }
            }
        }
    }

    // for(int s = 1; s <= n ; ++s) {
        // for(int i = 0; i + s <= n; ++i) {
            // int j = i + s - 1;
            // printf("%d ", dp[i][j]);
        // }
        // printf("\n");
    // }
    // printf("%d\n", dp[0][n-1]);

    print_bracket(0, n-1);
    printf("\n");
    return 0;
}

void print_bracket(int i, int j)
{

    if (i > j)
        return;

    if (i == j) {
        if (str[i] == '(' || str[i] == ')') {
            printf("()");
        }

        if (str[i] == '[' || str[i] == ']') {
            printf("[]");
        }

        return;
    }

    if (pos[i][j] == -1) {
        printf("%c", str[i]);
        print_bracket(i+1, j-1);
        printf("%c", str[j]);
        return;
    }

    int k = pos[i][j];

    print_bracket(i, k);
    print_bracket(k+1, j);
}
