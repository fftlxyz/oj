/* poj 3469
 * memory: 14764K
 * time: 5610MS
 * complier: G++
 * code length: 3360B
 * date: 2012-11-09 19:23:24
 * dinic 非递归 临接表
 * 我在用压如重标记做一次..
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <queue>
using std::queue;

const int MAX_N = 20100;
const int MAX_M = 200100;
const int MAX_E = 4 * MAX_N + 4 * MAX_M;

struct Edge
{
    int from; int to; int cap;
    int next;
} edges[MAX_E];  // static link list
int ecnt = 0;

int lev[MAX_N];
int head[MAX_N];

void init()
{
    ecnt = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int  c)
{
    edges[ecnt].from = u;
    edges[ecnt].to = v;
    edges[ecnt].cap = c;
    edges[ecnt].next = head[u];
    head[u] = ecnt;
    ecnt++;

    edges[ecnt].from = v;
    edges[ecnt].to = u;
    edges[ecnt].cap = 0;
    edges[ecnt].next = head[v];
    head[v] = ecnt;
    ecnt++;
}

queue<int> qnode;
int bfs(int s, int t)
{
    memset(lev, -1, sizeof(lev));
    lev[s] = 0;
    int  p, u, v;

    qnode.push(s);
    while(!qnode.empty()){

        u = qnode.front();
        qnode.pop();

        p = head[u];

        while (p != -1) {

            v = edges[p].to;
            if ( lev[v] == -1 && edges[p].cap > 0 ) {
                lev[v] = lev[u] + 1;
                qnode.push(v);
            }
            p = edges[p].next;
        }
    }
    return lev[t] != -1;
}

int dinic(int s, int t, int n)
{
    int a[MAX_N], ag;
    int pre[MAX_N];
    int cur[MAX_N];
    int u, v;
    int p;
    int f = 0;


    while(bfs(s, t)) {

        for (int i = 0 ; i < n; ++i) {
            cur[i] = head[i];
        }
        memset(pre, -1, sizeof(pre));

        u = s;
        a[s] = INT_MAX;

        while (1) {

            p = cur[u];
            while( p != -1){
                v = edges[p].to;
                if (lev[u] + 1 == lev[v] && edges[p].cap > 0 ) {
                    break;
                }
                p = edges[p].next;
            }

            if( p != -1) {
                pre[v] = u;
                cur[u] = p;
                a[v] = edges[p].cap;
                if( a[v] > a[u])
                    a[v] = a[u];

                if( v != t) {
                    u = v; //continue dfs
                } else {

                    ag = a[t];
                    f += ag;
                    while (v != s){
                        edges[cur[pre[v]]].cap -= ag;
                        edges[cur[pre[v]] ^ 1].cap += ag;
                        a[v] -= ag;
                        if( edges[cur[pre[v]]].cap == 0)
                            u = pre[v];
                        v = pre[v];
                    }
                }

            } else {

                if (u == s) {
                    break;
                } else {
                    lev[u] = INT_MAX; //此路不通
                    u = pre[u];
                }
            }

        }
    }

    return f;
}

int main(int argc, const char *argv[])
{
    int n, m;
    int u, v, c;
    int a, b;
    scanf("%d%d", &n, &m);

    init();

    for ( int i = 1; i <= n; ++i ) {
        scanf("%d%d", &a, &b);

        addedge(0, i, a);
        addedge(i, n+1, b);
    }

    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        addedge(u, v, c);
        addedge(v, u, c);
    }

    printf("%d\n", dinic(0,n+1,n+2));
    return 0;
}
