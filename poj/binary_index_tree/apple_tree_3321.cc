#include <stdio.h>
#include <string.h>

// 11328080	fly2best	3321	Time Limit Exceeded			G++	1872B	2013-03-09 10:15:15
// vector 换成自己写的链表过了, 不过这个时间, 汗...., 应该还有可以优化的余地
// 11328219	fly2best	3321	Accepted	9252K	1000MS	G++	1995B	2013-03-09 10:47:34

struct Edge {
    int to;
    Edge *next;
};

const int MAXN = 100100;

int pre[MAXN];
int post[MAXN];
bool isempty[MAXN];
int c[MAXN<<1];
int dfsindex = 1;
Edge map[MAXN]; //带头结点的链表
int N;

static inline int lowbit(int x) { return x & -x;}
int sum(int x);
void add(int x, int v);

void dfs(int n);

int main(int argc, const char *argv[])
{
    memset(pre, 0, sizeof(pre));
    memset(post, 0, sizeof(post));
    memset(isempty, 1, sizeof(isempty));

    int n, m;
    scanf("%d", &n);
    N = n << 1;

    for (int i = 1; i <= n; ++i) {
        map[i].next = NULL;
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);

        Edge * e = new Edge();
        e->to = b;
        e->next = map[a].next;
        map[a].next = e;

    }

    dfsindex = 1;
    dfs(1);

    //初始化
    for (int i = 1; i <= N; ++i) {
        c[i] = lowbit(i);
    }

    scanf("%d\n", &m);

    for(int i = 0; i < m; ++i) {
        char oper;
        int x;
        scanf("%c%d\n", &oper, &x);

        if (oper == 'C') {
            if (isempty[x]) {
                add(pre[x], -1);
                add(post[x], -1);
            } else {
                add(pre[x], 1);
                add(post[x], 1);
            }
            isempty[x] = !isempty[x];
        } else {
            printf("%d\n", (sum(post[x]) - sum(pre[x] -1 ))/2 );
        }

    }

    return 0;
}


void dfs(int n)
{
    pre[n] = dfsindex++;
    Edge *p = map[n].next;
    while( p != NULL) {
        if (pre[p->to] == post[p->to]) {
            dfs(p->to);
        }
        p = p->next;
    }
    post[n] = dfsindex++;
}

int sum(int x)
{
    int ret = 0;
    while (x > 0) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

void add(int x, int v)
{
    while (x <= N) {
        c[x] += v;
        x += lowbit(x);
    }
}


