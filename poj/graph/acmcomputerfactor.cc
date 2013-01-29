
/* poj 3436
 * memory:584K
 * time:0MS
 * complier:G++
 * code length:4690B
 * date:2012-11-09 15:32:33
 * 最大流 dinic 临接矩阵
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <queue>
using std::queue;

const int MAX_N = 55;
int cap[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
int lev[MAX_N];

struct Node
{
    int pf;
    int in[12];
    int out[12];
} nodes[MAX_N];
int nodescou = 1;
int p, n;

queue<int> nodeque;
int bfs(int s, int t)
{
    int u, v;
    memset(lev, -1, sizeof(lev));
    lev[s] = 0;
    nodeque.push(s);
    while(!nodeque.empty()){
        u = nodeque.front();
        nodeque.pop();

        for( v = 0; v <= t; ++v){
            if( cap[u][v] - flow[u][v] > 0 && lev[v] == -1 ){
                lev[v] = lev[u] + 1;
                nodeque.push(v);
            }
        }
    }
    return lev[t] != -1;
}

int dinic(int s, int t)
{
    int a[MAX_N], cur[MAX_N];
    int pre[MAX_N];
    int f = 0;
    int i, u, v, flag, ag;

    memset(flow, 0, sizeof(flow));

    //while exist argument path
    while( bfs(s,t) ) {

        //initlize
        for(i = 0; i <= t; i++){
            cur[i] = 0;
            a[i] = INT_MAX;
        }
        u = s;

        while(1){

            flag = 0;
            for(v = cur[u]; v <= t; ++v){
                if( cap[u][v] - flow[u][v] > 0 && lev[u] + 1 == lev[v]){
                    flag = 1;
                    break;
                }
            }

            if( flag ) {
                cur[u] = v ; //why v + 1;
                pre[v] = u;
                a[v] = cap[u][v] - flow[u][v];
                if( a[u] < a[v])
                    a[v] = a[u];

                u = v; // continue dfs
                if( u == t){
                    ag = a[t];
                    f += ag;
                    for( v = t; v != s; v = pre[v] ){
                        // cur[pre[v]] = v + 1; // when find next argument path, from begin from v
                        flow[pre[v]][v] += ag;
                        flow[v][pre[v]] -= ag;
                        a[v] -= ag;
                        //多路增广,下次开始的的地方为
                        //最前面的那条容量为0边的顶点
                        if( cap[pre[v]][v] - flow[pre[v]][v] == 0)
                            u = pre[v];
                    }
                }
            }
            else {
                //此路不通
                if( u != s) {
                        lev[u] = INT_MAX;
                        u = pre[u]; //回溯
                } else {
                    //从s没有增广路退出
                    break;
                }
            }

        }
    }
    return f;
}


void input()
{
    scanf("%d%d", &p, &n);

    nodescou = n;
    for(int ni = 1; ni <= n ; ++ni) {

        Node &node = nodes[ni];
        scanf("%d", &node.pf);

        for(int i = 0; i < p; ++i){
            scanf("%d", &node.in[i]);
        }

        for(int i = 0; i < p; ++i){
            scanf("%d", &node.out[i]);
        }
    }
}

void constructgraph()
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            if (j != i) {
                bool isok = true;
                for (int k = 0; k < p; ++k) {
                    if( !( (nodes[i].out[k] == 0 && nodes[j].in[k] == 0)
                            || (nodes[i].out[k] == 1 && nodes[j].in[k] == 1)
                            ||  nodes[j].in[k] == 2 )) {
                        isok = false;
                        break;
                    }
                }

                if (isok) {
                    cap[i][j] = nodes[i].pf;
                }
            }
    }

    for (int i = 1; i <= n; ++i) {
        bool isin = true;
        bool isout = true;

        for (int j = 0 ; j < p; ++j) {
            if(nodes[i].in[j] == 1) {
                isin = false;
                break;
            }
        }

        for (int j = 0 ; j < p; ++j) {
            if(nodes[i].out[j] == 0) {
                isout = false;
                break;
            }
        }

        if (isin) {
            cap[0][i] = nodes[i].pf;
        }
        if (isout) {
            cap[i][n+1] = nodes[i].pf;
        }
    }
}

int main()
{
    input();
    constructgraph();
    printf("%d", dinic(0,n+1));
    int ncount = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (flow[i][j] > 0) {
                ++ncount;
            }
        }

    printf(" %d\n", ncount);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (flow[i][j] > 0) {
                printf("%d %d %d\n", i, j, flow[i][j]);
            }
        }

    return 0;
}
