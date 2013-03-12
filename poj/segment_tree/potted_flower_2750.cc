
// 连续子序列最大和的一个变形
// 还是个点修改
// 最大区间看是否跨过N,
// 1. 不跨N, 普通的连续子序列最大值
// 2. 跨N, 那就是rmax[i, N]  + lmax[1, i -1] 枚举i, O(nlogn)
//
// bugfix: 这有m次查询阿，M和n一个数量级的
// so . O(n^2logn) 不可能过的, n 有10^5阿
// 优化跨N的计算方法
// lmaxsum[1,N]的区间[1, a]
// rmaxsum[1,N]的区间[b, N]
// 1.如果a <= b-1,  那么跨N的最大值就是两者之和
// 2.如果 a>=b, 那么也就是说, 两个区间有重复, 那么跨N的最大值应该就是整个区间和
// 怎么区分两者的，就和整个[1,N]区间和比较就行了.
//
// so, 每次修改的时间复杂度是O(logN)
// 查询可以在常数时间复杂度内完成.
// so, 建树O(N)
// 修改查询O(NLogN),
//
// bugfix to bugfix:
// nnd, 老子, 思路有问题的, 我偷偷的看了别人的思路, 题意
// 题意我也理解的有问题.  // 不能完全是一个环...
// keypoint
// 1.如果全为正数,减去最小值
// 2.最大连续子区间，和 最小连续子区间不能同时跨过N，
//   sum = 最大连续子区间+最小子区间
//   因此就把这个问题给转化了.
//
// 这是我的思考的过程, 有bug, but i try to fix
// fly2best	2750	Accepted	7616K	719MS	G++	2296B	2013-03-05 19:53:45
// 这个题目，提前准备的很完善
#include <stdio.h>

const int MAXN = 100005;
int sum[MAXN << 4];   //区间和
int maxsum[MAXN << 4];  //最大连续子序列的和
int lmaxsum[MAXN << 4]; //左端开始的最大连续子序列和
int rmaxsum[MAXN << 4]; //终止与右端的最大连续子序列和
int minsum[MAXN << 4];  //最小连续子序列的和
int lminsum[MAXN << 4]; //左端开始的最小连续子序列和
int rminsum[MAXN << 4]; //终止与右端的最小连续子序列和


static inline int max(int a, int b) {return a > b ? a : b;}
static inline int min(int a, int b) {return a < b ? a : b;}

void pushup(int rt);

void build(int l, int r, int rt)
{
    if (l == r) {

        int sumrt;
        scanf("%d", &sumrt);
        sum[rt]
            = maxsum[rt] = lmaxsum[rt] = rmaxsum[rt]
            = minsum[rt] = lminsum[rt] = rminsum[rt] = sumrt;
    } else {
        int m = (l + r) >> 1;
        build(l, m, rt << 1);
        build(m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}


void pushup(int rt)
{
    int lc = rt << 1;
    int rc = rt << 1 | 1;

    sum[rt] = sum[lc] + sum[rc];

    maxsum[rt] = max(max(maxsum[lc], maxsum[rc]), rmaxsum[lc] + lmaxsum[rc]);
    lmaxsum[rt] = max(lmaxsum[lc], sum[lc] + lmaxsum[rc]);
    rmaxsum[rt] = max(rmaxsum[lc] + sum[rc], rmaxsum[rc]);

    minsum[rt] = min(min(minsum[lc], minsum[rc]), rminsum[lc] + lminsum[rc]);
    lminsum[rt] = min(lminsum[lc], sum[lc] + lminsum[rc]);
    rminsum[rt] = min(rminsum[lc] + sum[rc], rminsum[rc]);
}

void update(int p, int c, int l, int r,int rt)
{
    if (l == r)
        sum[rt]
            = maxsum[rt] = lmaxsum[rt] = rmaxsum[rt]
            = minsum[rt] = lminsum[rt] = rminsum[rt] = c;
    else {
        int m = (l + r) >> 1;

        if ( p <= m)
            update(p, c, l , m , rt << 1);
        else
            update(p, c, m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}

int main(int argc, const char *argv[])
{
    int n, m;
    scanf("%d", &n);
    build(1, n, 1);
    scanf("%d", &m);

    while(m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        update(a, b, 1, n, 1);

        int result = maxsum[1];
        if (maxsum[1] == sum[1])
            result -= minsum[1];
        else {
            if (sum[1] - minsum[1] > result)
                result = sum[1] - minsum[1];
        }
        printf("%d\n", result);

    }
    return 0;
}
