
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits>
using std::max;
using std::min;

//#define __DEBUG__

const int N = 50100;

int node[N];

struct {
    int to;
    int w;
    int next;
} edge[N << 1];  //双向的
int cnt = 1;

int n;
int m;

//dp[i][0] i经过其父节点能到达的最长路径
//dp[i][1] i在其子树中的最长路径
//dp[i][2] i在其子树中的次长路径
int dp[N][3];

//dpc[i][1] 最长路径经过的子结点
//dpc[i][2] 次长路径经过的子结点
int dpc[N][3];

int dist[N];

struct {
    int v;
    int index;
} dqueue[N], iqueue[N]; //单调递减 decresing queue

int dhead, dtail;
int ihead, itail;

int ans[N];

void add_edge(int u, int v, int w);
void dfs1(int u, int p);
void dfs2(int u, int p, int w);
int find(int q);
void input_min(int i, int key, int k);
void input_max(int i, int key, int k);
int check(int k);

int main(int argc, const char *argv[])
{

    while ( scanf("%d%d", &n, &m) != EOF && n != 0 && m != 0 ) {

        memset(node, 0, sizeof(node));
        memset(edge, 0, sizeof(edge));

        cnt = 1;

        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }

#ifdef __DEBUG__
        for (int i = 1; i <= n; ++i) {
            int p = node[i];
            while (p != 0) {
                printf("%d %d %d\n", i, edge[p].to, edge[p].w);
                p = edge[p].next;
            }
        }
#endif
        memset(dp, 0, sizeof(dp));
        memset(dpc, 0, sizeof(dpc));


        dfs1(1, 0);
        dfs2(1, 0, 0);

#ifdef __DEBUG__
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 3; ++j) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
#endif
        for (int i = 1; i <= n; ++i) {
            dist[i] = max(dp[i][0], dp[i][1]);
        }

#ifdef __DEBUG__
        for (int i = 1; i <= n; ++i) {
            printf("%d ", dist[i]);
        }
        printf("\n");
#endif

        memset(ans, 0, sizeof(ans));

        for (int i = 0; i < m; ++i) {
            int q;
            scanf("%d", &q);
            printf("%d\n", find(q));
        }

    }

    return 0;
}


void add_edge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = node[u];
    node[u] = cnt++;
}

void dfs1(int u, int p)
{

#ifdef __DEBUG__
    printf("%d %d\n", p, u);
#endif

    int next = node[u];

    while (next != 0) {

        int child = edge[next].to;

        if (child != p) {

            dfs1(child, u);

            int len = edge[next].w + dp[child][1];

            if ( len > dp[u][1]) {
                dp[u][2] = dp[u][1];
                dpc[u][2] = dpc[u][1];

                dp[u][1] = len;
                dpc[u][1] = child;

            } else if (len > dp[u][2]) {
                dp[u][2] = len;
                dpc[u][2] = child;
            }
        }

        next = edge[next].next;
    }
}

void dfs2(int u, int p, int w)
{

#ifdef __DEBUG__
    printf("%d %d\n", p, u);
#endif

    if (p != 0) {
        if (dpc[p][1] == u) {
            dp[u][0] = max(dp[p][0], dp[p][2]) + w;
        } else {
            dp[u][0] = max(dp[p][0], dp[p][1]) + w;
        }
    }

    int next = node[u];
    while (next != 0) {
        int v = edge[next].to;

        if (v != p)
            dfs2(v, u, edge[next].w);

        next = edge[next].next;
    }
}

int find(int q)
{
    int len = 1;

    int l = 1, r = n + 1;

    while ( l < r) {

        int m = l + (r - l) / 2;

        if (check(m) <= q) {
            len = m;

            l = m + 1;
        } else {
            r = m;
        }
    }

    return len;
}

//返回区间长度为k上的区间差的最小值
//可以有一个常数优化
int check(int k)
{
    if (ans[k])
        return ans[k];

    ihead = itail = 0;
    dhead = dtail = 0;

    for (int i = 1; i <= k - 1; ++i) {
        input_max(i, dist[i], k);
        input_min(i, dist[i], k);
    }

    ans[k] = std::numeric_limits<int>::max();

    for (int i = k; i <= n; ++i) {
        input_max(i, dist[i], k);
        input_min(i, dist[i], k);
        ans[k] = min(ans[k], dqueue[dhead].v - iqueue[ihead].v);
    }

    return ans[k];
}


void input_max(int i, int key, int k)
{
    while (dhead != dtail && dqueue[dtail - 1].v <= key) {
        --dtail;
    }

    dqueue[dtail].v = key;
    dqueue[dtail].index = i;
    ++dtail;

    while (dhead != dtail && (i - dqueue[dhead].index >= k)) {
        ++dhead;
    }
}


void input_min(int i, int key, int k)
{
    while (ihead != itail && iqueue[itail - 1].v >= key) {
        --itail;
    }

    iqueue[itail].v = key;
    iqueue[itail].index = i;
    ++itail;

    while (ihead != itail && (i - iqueue[ihead].index >= k)) {
        ++ihead;
    }
}
