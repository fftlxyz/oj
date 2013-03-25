
#include <stdio.h>
#include <string.h>
#include <assert.h>

const int MAXN = 10100;

struct Edge
{
   int to;
   struct Edge * next;
   int indegree;
   int dfsi;
} nodes[MAXN];

bool isroot[MAXN];

int  rmq_sequence[MAXN << 1];
int dp_min[MAXN << 1][20];
int left[MAXN]; // N在rmq_sequence的下标

int dfsitonode[MAXN];

int n;

int lca_rmq_index;
int dfs_index;

static inline int max(int a, int b) {return a > b ? a : b;}
static inline int min(int a, int b) {return a < b ? a : b;}
void lca_to_rmq();
void rmq_init();
int rmq(int x, int y);
void dfs(int rt);
void add_edge(int from, int to);

int main(int argc, const char *argv[])
{
    int casenum;

    scanf("%d", &casenum);
    while (casenum--) {

        int i ,x, y;
        scanf("%d", &n);

        memset(nodes, 0, sizeof(nodes));
        memset(isroot, 0, sizeof(isroot));
        memset(left, -1, sizeof(left));

        for (i = 0; i < n - 1; ++i) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
        }

        lca_to_rmq();

        rmq_init();

        scanf("%d%d", &x, &y);

        printf("%d\n", dfsitonode[rmq(min(left[x], left[y]), max(left[x], left[y]))]);

    }

    return 0;
}

//因为这知识一个oj程序, 我没有考虑内存释放的问题
void add_edge(int from, int to)
{

    Edge * e = new Edge();
    e->to = to;
    e->next = nodes[from].next;

    nodes[from].next = e;
    ++nodes[to].indegree;
}


void lca_to_rmq()
{
    int i = 0;
    int root = -1;
    for (i = 1; i <= n; ++i) {
        if (nodes[i].indegree == 0) {
            root = i;
        }
    }
    lca_rmq_index = 0;
    dfs_index = 0;
    dfs(root);

    // for(int i = 0; i < lca_rmq_index; ++i) {
        // printf("%d ", rmq_sequence[i]);
    // }
    // printf("\n");

    // printf("rmq_index:%d\n", lca_rmq_index);
}



void dfs(int rt)
{
    Edge *p;

    nodes[rt].dfsi = dfs_index;
    dfsitonode[dfs_index] = rt;
    rmq_sequence[lca_rmq_index] = dfs_index;
    left[rt] = lca_rmq_index;

    dfs_index++;
    lca_rmq_index++;

    p = nodes[rt].next;

    while (p != NULL) {

        if (left[p->to] == -1) {
            dfs(p->to);
            rmq_sequence[lca_rmq_index++] = nodes[rt].dfsi;
        }
        p = p->next;
    }

}

//dp_min[i][j] (i, i + 2^j - 1)
void rmq_init()
{
    int m = 2 * n - 1;

    assert(m == lca_rmq_index);

    int i, j;
    for (i = 0; i < m; ++i) {
        dp_min[i][0] = rmq_sequence[i];
    }

    // dp_min[i][j] =min(min[i,i + 2^(j-1) -1], min(i + 2^(j-1), i + 2^j - 1)
    //
    for (j = 1; (1 << j) <= m; ++j) {
        int step = 1 << j;
        for(i = 0; i + step <= m; ++i) {
            dp_min[i][j] = min(dp_min[i][j-1], dp_min[i + (step >> 1) ][j - 1]);
        }
    }
}


//x <= y
int rmq(int x, int y)
{
    int j = 0;
    while ((1 << j) < y - x + 1) {
        ++j;
    }
    --j;

    return min(dp_min[x][j], dp_min[y - (1 << j) + 1][j]);
}
