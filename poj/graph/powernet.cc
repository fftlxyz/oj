
/* poj 1459
 * memory: 612K
 * time: 641MS
 * complier: G++
 * code length: 1788B
 * date: 2012-11-07 20:33:02
 * 1A
 * 这个题。。。
 * 我不是很理解。。。
 * 导论上不是说，不能有回边的嘛。。
 * 可这是为什么呢。。。
 * 这个题目中有回边，但是edkarp 还是A了。。。。
 * 该总结了。。。
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <queue>
using std::queue;

const int MAX_N = 105;

int cap[MAX_N][MAX_N];
int n = 0;

//返回最大流
int edmondskarp(int s, int t)
{
    int pre[MAX_N];
    int flow[MAX_N][MAX_N];
    int a[MAX_N];
    int u, v, f;
    queue<int> q;

    memset(flow, 0 , sizeof(flow));
    f = 0;

    while (1) {

        q.push(s);
        memset(a, 0, sizeof(a));
        a[s] = INT_MAX;
        while (!q.empty()) {
            u = q.front();
            q.pop();

            for ( v = 0; v <= n; ++v){
                if (!a[v] && cap[u][v] - flow[u][v] > 0){
                    q.push(v);

                    pre[v] = u;
                    a[v] = a[u] < cap[u][v] - flow[u][v]
                        ? a[u] : cap[u][v] - flow[u][v];
                }
            }
        }

        if( a[t] == 0)
            break;

        for( u = t; u != s; u = pre[u]){
            flow[pre[u]][u] += a[t];
            flow[u][pre[u]] -= a[t];
        }

        f += a[t];
    }

    return f;

}


int main(int argc, const char *argv[])
{
    int na, np, nc, nm;

    while( scanf("%d%d%d%d", &na, &np, &nc, &nm) == 4){

        memset(cap, 0, sizeof(cap));
        int u, v, c;

        for(int i = 0; i < nm; ++i){
            scanf(" (%d,%d)%d", &u, &v, &c);
            cap[u][v] = c;
        }

        u = na;
        for(int i = 0; i < np; ++i){
            scanf(" (%d)%d", &v,&c);
            cap[u][v] = c;
        }

        v = na+1;
        for(int i = 0; i < nc; ++i){
            scanf(" (%d)%d", &u, &c);
            cap[u][v] = c;
        }

        n = na + 2;
        printf("%d\n", edmondskarp(na,na+1));
    }

    return 0;
}
