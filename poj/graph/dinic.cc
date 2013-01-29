#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <queue>
using std::queue;

const int MAX_N = 100;
int cap[MAX_N][MAX_N];
int lev[MAX_N];

int bfscount = 0;
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
            if( cap[u][v] > 0 && lev[v] == -1 ){
                lev[v] = lev[u] + 1;
                nodeque.push(v);
            }
        }
    }

    bfscount += 1;

    return lev[t] != -1;
}


int dinic(int s, int t)
{
    int a[MAX_N], cur[MAX_N];
    int pre[MAX_N];
    int flow = 0;
    int i, u, v, flag, ag;

    //while exist argument path
    while( bfs(s,t) ) {

        //initlize
        for(i = 0; i <= t; i++){
            cur[i] = 0;
            a[i] = INT_MAX;
        }
        u = s;

        int loopcount = 0;
        while(1){

            ++loopcount;

            flag = 0;
            for(v = cur[u]; v <= t; ++v){
                if( cap[u][v] > 0 && lev[u] + 1 == lev[v]){
                    flag = 1;
                    break;
                }
            }

            if( flag ) {
                cur[u] = v ; //why v + 1;
                pre[v] = u;
                a[v] = cap[u][v];
                if( a[u] < a[v])
                    a[v] = a[u];

                u = v; // continue dfs
                if( u == t){
                    ag = a[t];
                    flow += ag;
                    for( v = t; v != s; v = pre[v] ){
                        // cur[pre[v]] = v + 1; // when find next argument path, from begin from v
                        cap[pre[v]][v] -= ag;
                        cap[v][pre[v]] += ag;
                        a[v] -= ag;
                        //多路增广,下次开始的的地方为
                        //最前面的那条容量为0边的顶点
                        if( cap[pre[v]][v] == 0)
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

            printf("%d %d\n", bfscount, loopcount);


        }
    }
    return flow;
}

int main()
{
    int nedge, nnode;

    scanf("%d%d", &nedge, &nnode);

    int u, v, c;

    while( nedge-- ){

        scanf("%d%d%d", &u, &v, &c);
        cap[u - 1][v - 1] = c;
    }

    printf("%d\n", dinic(0, nnode-1));
    printf("%d\n", bfscount);

    return 0;
}
