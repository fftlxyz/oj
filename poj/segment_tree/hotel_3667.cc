// 嗯这题目，我考虑不周全，这种解法时错的
// 1. 如果每次从最大区间分内存，不能保证, 在最大区间的左边有可用内存情况
// 2. 我最大区间的方法的计算方法是错误的.
// 3. 我这道题标记的处理时失败的, 每个线段树结点右3个状态，完全空闲，完全占用，混合状态,  我没考虑混合状态.
//
// bugfix:
// 1. 要查询, 如果可以满足，则有三种情况
//    * max[lc] >= len, query(lc) //注意这种情况不一定时获取整个rt结点的最长空白区间,可能是左儿子中可行的
//    * rmax[lc] + lmax[rc] >= len, 这中情况, 直接返回起始位置 //同上
//    * query(rc)
//
// 2. 最大空白区间，可以跨左右结点，竟然都没注意
// 3. 加状态
//
// 相关问题:
// 1. 内存分配问题
// 2. 最大子序列和
//
// 11308034	fly2best	3667	Accepted	2456K	1032MS	G++	3220B	2013-03-03 20:53:10
// 这个我已经总结了...
// 11308018	fly2best	2886	Runtime Error			G++	3220B	2013-03-03 20:49:33
// 这个是交错题目了,汗
// 11305895	fly2best	3667	Wrong Answer			G++	2464B	2013-03-03 11:53:25
#include <stdio.h>

const int MAXN = 50005;

int set[MAXN << 2];  // 1完全空白, 0 完全被占用, -1 中间状态
//转化为区间最大子序列的问题
int sum[MAXN << 2];  //最大的空白区间的长度
int lsum[MAXN << 2]; //从左边边界开始的最大空白区间长度
int rsum[MAXN << 2]; //到右边边界结束的最大空白区间长度

static inline int max(int a, int b) {return a > b ? a : b;}

void update(int y1, int y2, int c, int l, int r, int rt);
void pushdown(int rt, int len);
void pushup(int rt, int len);
int query(int len, int l, int r, int rt);

int main(int argc, const char *argv[])
{
    int n, m;
    scanf("%d%d", &n, &m);
    sum[1] = lsum[1] = rsum[1] = n;
    set[1] = 1; //
    int oper, a, b;
    while (m--) {
        scanf("%d", &oper);
        if (oper == 1) {
            scanf("%d", &a);
            if (sum[1] >= a) {
                int q = query(a, 1, n, 1);
                printf("%d\n",q);
                update(q, q + a - 1, 0, 1, n, 1);
            } else
                printf("%d\n", 0);
        } else {
            scanf("%d%d", &a, &b);
            update(a, b + a - 1, 1, 1, n, 1);
        }
    }
    return 0;
}


void build(int l, int r, int rt)
{
    if (l == r) {
        set[rt] = -1;
        sum[rt] = lsum[rt] = rsum[rt] = 1;
        return;
    }

    int m = (l + r) >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    pushup(rt, r - l + 1);
}

void update(int y1, int y2, int c, int l, int r, int rt)
{
    if ( y1 <= l && r <= y2) {
        set[rt] = c;
        sum[rt] = lsum[rt] = rsum[rt] = (c ? r - l + 1 : 0);
    } else {
        pushdown(rt, r - l + 1);
        int m = (l + r) >> 1;
        if (y1 <= m)
            update(y1, y2, c, l, m, rt << 1);
        if (m + 1 <= y2)
            update(y1, y2, c, m + 1, r, rt << 1 | 1);
        pushup(rt, r - l + 1);
    }
}

void pushdown(int rt, int len)
{
    if (set[rt] != -1) {
        int lc = rt << 1;
        int rc = rt << 1 | 1;
        set[lc] = set[rc] = set[rt];
        sum[lc] = lsum[lc] = rsum[lc] = (set[lc] ?  len - len / 2 : 0);
        sum[rc] = lsum[rc] = rsum[rc] = (set[rc] ? len / 2 : 0);
        set[rt] = -1;
    }
}

int query(int len, int l, int r, int rt)
{
    pushdown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (sum[rt << 1] >= len)
        return query(len, l ,m, rt << 1);
    else if (rsum[rt << 1] + lsum[rt << 1 | 1] >= len)
        return m + 1 - rsum[rt << 1];
    else
        return query(len, m + 1, r, rt << 1 | 1);
}

void pushup(int rt, int len)
{
    int lc = rt << 1;
    int rc = rt << 1 | 1;

    sum[rt] = max(max(sum[lc],sum[rc]), rsum[lc] + lsum[rc]);
    lsum[rt] = lsum[lc];
    rsum[rt] = rsum[rc];

    if (lsum[lc] == len - len / 2)
        lsum[rt] += lsum[rc];
    if (rsum[rc] == len / 2)
        rsum[rt] += rsum[lc];
    //没有必要报标记合并上去
}
