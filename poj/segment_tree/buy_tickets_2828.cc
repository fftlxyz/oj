// 思路很巧妙, I Like,
// 路漫漫其修远兮 吾将上下而求索
// 倒着插入，pos 表示其前面有几个空位, 在线段树上存放这个结点的空位数
// fly2best	2828	Accepted	4800K	3485MS	G++	1572B	2013-03-03 08:38:50
// 1AC, 思路比较清楚，一次AC
#include <stdio.h>

const int MAXN = 200005;
int empty_pos[MAXN << 4];
int pos[MAXN];
int val[MAXN];
int ans[MAXN];
static inline void pushup(int rt);
static int update(int pos, int l, int r, int rt);
static void build(int l, int r, int rt);

int main(int argc, const char *argv[])
{
    int n;
    while (scanf("%d", &n) != EOF) {
        build(1, n, 1);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", pos + i, val + i);
        }
        for (int i = n - 1; i >= 0; --i) {
            int pi = update(pos[i] + 1, 0, n - 1, 1);
            ans[pi] = *(val + i);
        }
        for (int i = 0; i < n; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}


static void build(int l, int r, int rt)
{
    if (l == r) {
        empty_pos[rt] = 1;
        return;
    }
    int m = (l + r) >> 1;
    build(l , m, rt << 1);
    build(m + 1 , r, rt << 1 | 1);
    pushup(rt);
}


static inline void pushup(int rt)
{
    empty_pos[rt] = empty_pos[rt << 1] + empty_pos[rt << 1 | 1];
}

//找到第pos个空位，并维护线段树结点信息
static int update(int pos, int l, int r, int rt)
{
    if (l == r) {
        empty_pos[rt] = 0;
        return l;
    }

    int m = (l + r) >> 1;
    int ret;
    if (empty_pos[rt << 1] >= pos) {
       ret = update(pos, l, m, rt << 1);
    } else {
       ret = update(pos - empty_pos[rt << 1], m + 1, r, rt << 1 | 1);
    }
    pushup(rt);
    return ret;
}
