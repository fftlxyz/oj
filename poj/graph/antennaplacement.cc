/*
 * poj 3020
 * memory: 1376K
 * time: 0MS
 * complier: G++
 * code length: 2428B
 * date: 2012-11-18 09:36:59
 * 怎么把普通无向图的匹配，转化为二分图的匹配
 *
 * 答案是: 匹配数 + 未匹配节点的数目
 *        = 总节点数 - 匹配数
 * 因为总结点数 = 2*匹配数 + 未匹配节点的数目
 *
 * */
#include <stdio.h>
#include <string.h>

const int H = 42;
const int W = 12;

char matrix[H][W];
int nodehash[H][W];

int h, w ;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int n = 0;
int adjl[H*W][H*W];
int match[H*W];
int used[H*W];

void input()
{
    scanf("%d%d\n", &h, &w);
    n = 0;
    for (int i = 0; i < h; ++i){
        scanf("%s", &matrix[i]);
        for (int j = 0; j < w; ++j) {
            if(matrix[i][j] == '*') {
                nodehash[i][j] = ++n;
            }
        }
        // printf("%s\n", matrix[i]);
    }

}

void build()
{
    memset(adjl, 0, sizeof(adjl));
    for (int i = 0; i < h; ++i) {
        for (int j = 0 ; j < w; ++j) {
            if (matrix[i][j] == '*') {
                int nodei = nodehash[i][j];
                for (int k = 0; k < 4; ++k) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(x > -1 && x < h && y > -1 && y < w && matrix[x][y] == '*') {
                        adjl[nodei][++adjl[nodei][0]] = nodehash[x][y];
                    }
                }
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
        // printf("%d\n", i);
        // for (int j = 1; j <= adjl[i][0]; ++j) {
            // printf("%d ", adjl[i][j]);
        // }
        // printf("\n");
    // }
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
        printf("%d\n", n - hungary()/ 2);
    }
    return 0;
}
