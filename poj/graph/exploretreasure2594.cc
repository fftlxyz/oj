/* poj 2594
 * memory: 1648K
 * time: 766MS
 * complier: G++
 * code length: 1933B
 * date: 2012-11-18 14:07:01
 * 怎么没考虑回边也能过。。。。
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
const int N = 505;

bool d[N][N];

int n = 0;
int adjl[N][N];
int match[N];
int used[N];

bool input()
{
    int ne;
    int s, t;
    scanf("%d%d", &n, &ne);
    if(n == 0 && ne == 0)
        return false;

    memset(d, 0, sizeof(d));
    for ( int i = 1; i <= ne; ++i) {
        scanf("%d%d", &s, &t);
        d[s][t] = 1;
    }

    return true;
}

void build()
{
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j =1; j <= n; ++j) {
                if(d[i][k] && d[k][j])
                    d[i][j] = true;
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        adjl[i][0] = 0;
        for(int j = 0; j <=n; ++j) {
            if(d[i][j])
                adjl[i][++adjl[i][0]] = j;
        }
    }
}

//dfs 来找argument path
bool dfs(int i)
{
    for(int k = 1; k <= adjl[i][0]; ++k) {
        int j = adjl[i][k];

        //why used[j]
        //dfs 的时候，我们需要判断一个顶点是否被访问过
        //为什么之判断右边的顶点呢？
        //除了根节点以外，其他的左边的节点，只能通过右边的节点到达
        //一个左边的节点，只有一个关联的右边的节点
        //so,如果右边的节点，能保证不重复访问，就能保证所有的节点不重复访问
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

        //without the code will also ac
        //so 没有无向边
        // for (int j = 1; j <= n; ++j) {
            // int i = match[j];
            // if ( i && i > j && match[i] == j)
               // --maxmatch;
        // }

        printf("%d\n", n - maxmatch);
    }
    return 0;
}
