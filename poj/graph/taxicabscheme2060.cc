/* poj 2060
 * memory: 1364K
 * time: 32MS
 * complier: G++
 * code length: 1998B
 * date: 2012-11-18 10:44:08
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
const int N = 505;
struct
{
    int s, e;
    int x1, y1, x2, y2;
} node[N];
int n = 0;

int adjl[N][N];
int match[N];
int used[N];


void input()
{
    int h, m;
    scanf("%d", &n);

    for ( int i = 1; i <= n; ++i) {
        scanf("%d:%d%d%d%d%d", &h, &m, &node[i].x1, &node[i].y1, &node[i].x2, &node[i].y2);
        node[i].s = h*60 + m;
        node[i].e = node[i].s + abs(node[i].x1 - node[i].x2) + abs(node[i].y1 - node[i].y2);
        // printf("%d %d %d %d %d %d\n", node[i].s, node[i].e, node[i].x1, node[i].y1, node[i].x2, node[i].y2);
    }

}

void build()
{
    for(int i = 1; i <= n; ++i) {
        adjl[i][0] = 0;
        for(int j = i + 1; j <=n; ++j) {
            if( node[i].e + abs(node[j].x1 - node[i].x2) + abs(node[j].y1 - node[i].y2) < node[j].s )
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
    int ncase;
    scanf("%d", &ncase);
    while (ncase--) {
        input();
        build();
        printf("%d\n", n - hungary());
    }
    return 0;
}
