/*
 * poj 1422
 * memory: 440K
 * time: 0MS
 * complier: G++
 * code length: 1366B
 * date: 2012-11-18 10:00:11
 * dag上的，最小不相交路径覆盖
 * minumu disjoin path cover in dag = numbofnodes - numofmaxmatch
 * 比较神奇的地方是，直接在原图的临接表上跑的匈牙利算法。
 * 数据是一样的，但是解释的方法不一样，也就得到了不通的结果。
 * amazing algorithm, thinking....
 * */
#include <stdio.h>
#include <string.h>
const int N = 125;
int n = 0;
int adjl[N][N];
int match[N];
int used[N];

void input()
{
    int ne, s, e;
    scanf("%d%d", &n, &ne);
    memset(adjl, 0, sizeof(adjl));
    for ( int i = 0; i < ne; ++i) {
        scanf("%d%d", &s, &e);
        adjl[s][++adjl[s][0]] = e;
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
        printf("%d\n", n - hungary());
    }
    return 0;
}
