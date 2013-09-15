#include <stdio.h>
#include <string.h>
#include <algorithm>
using std::sort;
using std::max;

const int N = 505;
const int D = 1005;

// 12113115 fly2best 3018 Accepted 2616K 454MS G++ 1464B 2013-09-15 20:58:45
// longgent path from in dag

int n;
int d;

int giftbox[N][D];
bool map[N][N];

int maxlen[N];

void init();
void dfs(int u);

int main(int argc, const char *argv[])
{
    while (scanf("%d %d", &n, &d) != EOF) {

        n++;
        init();
        dfs(0);

        if (maxlen[0]) {
            printf("%d\n", maxlen[0]);
        }
        else  {
            printf("Please look for another gift shop!\n");
        }
    }

    return 0;
}

void init()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < d; ++j) {
            scanf("%d", &giftbox[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(giftbox[i], giftbox[i] + d);
    }

    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {

            map[i][j] = true;
            for(int k = 0; k < d; ++k) {
                if ( giftbox[i][k] >= giftbox[j][k]){
                    map[i][j] = false;
                    break;
                }
            }
        }
    }

    memset(maxlen, -1, sizeof(maxlen));
}

// 递归 + 记忆化搜索
void dfs(int u)
{
    if (maxlen[u] != -1){
        return;
    }

    int maxl = -1;

    for (int i = 0; i < n; ++i) {
        if (map[u][i]) {
            dfs(i);
            maxl = max(maxl, maxlen[i]);
        }
    }

    maxlen[u] = maxl + 1;
}
