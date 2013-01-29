
/* poj 1548
 * memory: 1828K
 * time: 47MS
 * complier: G++
 * code length: 1690B
 * date: 2012-11-18 14:49:32
 * 数据水了
 * 最小路径覆盖...
 * 不过在discuss中看到dilworth 定理什么的 LIS 需要在做做
 * 嗯，这是第50道
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
const int N = 25*25;

struct
{
    int x,y ;
} node[N];

int adjl[N][N];
int match[N];
int used[N];

int n = 0;

bool input()
{
    int s, t;
    n = 0;
    while(1) {
        scanf("%d%d", &s, &t);
        if(s == -1 && t == -1 )
            return false;
        if(s == 0 && t == 0)
            return true;

        ++n;
        node[n].x = s;
        node[n].y = t;

        // printf("%d %d %d\n", n, s, t);
    }
}

void build()
{
    for(int i = 1; i <= n; ++i) {
        adjl[i][0] = 0;
        for(int j = 1; j <=n; ++j) {
            if ( j != i && node[i].y >= node[j].y && node[i].x >= node[j].x ) {
                adjl[i][++adjl[i][0]] = j;
                // printf("%d %d\n", i, j);
            }
        }
    }
}

//dfs 来找argument path
bool dfs(int i)
{
    for(int k = 1; k <= adjl[i][0]; ++k) {
        int j = adjl[i][k];
        if(!used[j]) {
            used[j] = true;
            if(match[j] == 0 || dfs(match[j])) {
                match[j] = i;
                return true;
            }
        }
    }

    return false;
}

//二分图的最大匹配
//怎么证明这个方法是正确的
//精巧
int hungary()
{
    int maxmatch = 0;

    memset(match, 0, sizeof(match));

    for ( int i = 1; i <= n; ++i) {
        memset(used, 0, sizeof(used));
        if(dfs(i)) {
            ++maxmatch;
        }
    }
    return maxmatch ;
}


int main(int argc, const char *argv[])
{
    while (input()) {
        build();
        //solove
        int maxmatch = hungary();
        printf("%d\n", n - maxmatch);
    }
    return 0;
}
