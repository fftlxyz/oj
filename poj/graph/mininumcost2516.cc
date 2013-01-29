
/* poj 2516
 * memory: 1160K
 * time: 329MS
 * complier: G++
 * code length: 4196B
 * date: 2012-11-10 17:06:51
 * 汗，先runtime error,
 * 然后 memory limit
 * 没有认真分析，数据的规模
 * 接着Time Limit Exceeded
 * 人品啊..............
 * 最后一个优化:判断order是否大于supply很诡异
 * 这个题目又一次交我要去分析时间和空间复杂度。。。。
 * come on, boy~~
 * */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <queue>
#include <vector>
using std::queue;
using std::vector;

int store[51][51];
int order[51][51];
int cost[51][51][51];

int cap[105][105];
int kcost[105][105];
int flow[51];


bool input();
void construct(int ki);
bool mcmf(int s, int t, int n, int& f, int& c);

int n, m, k;

int main(int argc, const char *argv[])
{
    int fi, ci, isfull;
    int c = 0;
    while (input()) {

        c = 0;
        for (int ki = 1; ki <= k; ++ki) {
            construct(ki);
            isfull = mcmf(0, m+n+1, m+n+2, fi, ci);
            c += ci;
            // printf("%d %d\n", fi, ci);
            if(!isfull){
                c = -1;
                break;
            }
        }
        printf("%d\n", c);
    }

    return 0;
}

void construct(int ki)
{
    int u, v;
    u = 0;
    memset(cap, 0, sizeof(cap));
    memset(kcost, 0, sizeof(kcost));
    for (int mi = 1; mi <= m; ++mi) {
        v = mi;
        cap[u][v] = store[mi][ki];
    }

    for(int mi = 1; mi <= m; ++mi) {
        u = mi;
        for(int nj = 1; nj <= n; ++nj){
            v = m + nj;
            cap[u][v] = store[mi][ki];
            kcost[u][v] = cost[ki][mi][nj];
            kcost[v][u] = -kcost[u][v]; // how to prove it carefully
        }
    }

    v = m + n + 1;
    for (int ni = 1; ni <= n; ++ni) {
        u = m + ni;
        cap[u][v] = order[ni][ki];
    }
}

bool input()
{
    scanf("%d%d%d", &n, &m, &k);

    if(m == 0 && n == 0 && k==0)
        return false;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= k; ++j) {
            scanf("%d", &order[i][j]);
        }
    }

    for(int i = 1; i <=m; ++i){
        for(int j = 1; j <= k; ++j) {
            scanf("%d", &store[i][j]);
        }
    }

    for(int ki = 1; ki <= k; ++ki)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
            {
                scanf("%d", &cost[ki][j][i] );
            }
    return true;
}

bool mcmf(int s, int t, int n, int& f, int& c)
{
    const int MAXN = 105;
    const int MAXDIST = MAXN*100;
    bool inque[MAXN] =  {0};
    int dist[MAXN];
    int prev[MAXN];
    queue<int> q;
    int u, v;
    f = 0;
    c = 0;

    int supply = 0;

    for (int i = 0; i < n; ++i) {
        supply += cap[s][i];
    }
    int  order = 0;
    for (int i = 0; i < n; ++i) {
        order += cap[i][t];
    }

    if( order == 0) {
        f = c = 0;
        return true;
    }
    if( order > supply ) {
        return false;
    }

    while (1) {

        for(int i = 0 ; i < n; ++i){
            dist[i] = MAXDIST;
        }

        dist[s] = 0;
        q.push(s);
        inque[s] = true;

        // try to analysis it
        while (!q.empty()) {
            u = q.front();
            q.pop();
            inque[u] = false;

            for ( v = 0; v < n; ++v) {
                if ( cap[u][v] > 0 && dist[v] > dist[u] + kcost[u][v] ) {

                    prev[v] = u;
                    dist[v] = dist[u] + kcost[u][v];
                    if( !inque[v]) {
                        q.push(v);
                        inque[v] = true;
                    }
                }
            }
        }

        if( dist[t] == MAXDIST )
            break;

        int a = INT_MAX;
        v = t;
        while( v != s ) {
            u = prev[v];
            if(a > cap[u][v])
                a = cap[u][v];
            v = u;
        }

        c += dist[t] * a;
        f += a;
        v = t;
        while( v != s ) {
            u = prev[v];
            cap[u][v] -= a;
            cap[v][u] += a;
            v = u;
        }
    }

    int restcap = 0;
    for(int i = 0; i < n; ++i) {
        restcap += cap[i][t];
    }
    // full flow or not
    return restcap == 0;
}
