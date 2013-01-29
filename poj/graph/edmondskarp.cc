#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <queue>
using std::queue;

const int MAX_N = 100;

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

            for ( v = 1; v <= n; ++v){
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
    int u, v, c;
    n = 6;
    while( scanf("%d%d%d", &u, &v, &c) == 3){
        cap[u][v] = c;
    }

    printf("%d\n", edmondskarp(1,n));

    return 0;
}
