// poj
// fly2best
// 3468
// Accepted
// 4504K
// 2688MS
// G++
// 2906B
// 2013-03-01 16:42:08
// 这个题目又揪出了我对线段树理解的几个不正确的地方
// 1. add 可能为负数, 在向下传递的时候需要注意.
// 2. 更新完子节点，需要更新父节点信息
// 3. sum + add 的值才是节点真正的值
// 4. 更新某一节点的时候，add的值是累加的，和set有所区别
// k. 这是线段树 第二题
// 烦躁是没用的，淡定下来，好好想想，不行就和别人写的程序比较一下，看哪里有错误。
// but,你一定要淡定，不要烦躁
//
// 我看hanghang的代码, sum 就是存放节点的sum值，
// 和算法竞赛入门经典 训练指南是一致的，代码看起来比较清晰.
//
// 线段树的确很灵活，你丫的要搞清楚自己在里面存放了什么, 但是思想是一样的.
//
// 淡定下来，学习一个好的模板，还是很过瘾的吧.
// hanghang的代码，用了一些简单的宏， 代码看起来整齐不少。
//
// 这个题目，我是知道在线段树的分类下，然后用线段树去做的
// 分析一下时间复杂度
#include <stdio.h>
const int MAXN = 100005;

int n, q;

long long sum[MAXN << 2];
long long add[MAXN << 2];

void build(int l, int r, int rt);
void pushdown(int rt, int l, int r);
void pushup(int rt, int l, int r);
long long query(int l, int r, int L, int R, int rt);
void update(int l, int r, int v, int L, int R, int rt);
void traverse(int l, int r, int rt);

int main(int argc, const char *argv[])
{
    scanf("%d %d", &n, &q);
    build(1, n, 1);
    // traverse(1, n, 1);

    int i;
    for (i = 0; i < q; ++i) {
        char ch;
        int l, r, v;
        scanf("\n%c", &ch);
        if (ch == 'C') {
            scanf("%d %d %d", &l, &r, &v);
            update(l, r, v, 1, n, 1);
            // printf("after %d %d %d\n", l, r, v);
            // traverse(1, n, 1);
            // printf("\n");
        } else {
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
    // traverse(1, n, 1);

    return 0;
}

// 对[l,r] 建树
void build(int l, int r, int rt)
{
    if (l == r) {
        scanf("%lld", &sum[rt]);
    } else {
        int m = (l + r) >> 1;
        build(l, m, rt << 1);
        build(m+1, r, rt << 1 | 1);

        sum[rt] += sum[rt << 1];
        sum[rt] += sum[rt << 1 | 1];
    }
}

void update(int l, int r, int v, int L, int R, int rt)
{
    if (l <= L && r >= R) {
        add[rt] += v;
    } else {

        pushdown(rt, L, R); //这是上次的延迟标记
        int m = (L + R) >> 1;
        if (l <= m)
            update(l, r, v, L, m, rt << 1);
        if (r > m)
            update(l, r, v, m + 1, R, rt << 1 | 1);
        pushup(rt, L, R); //需要这个的原因是,更新了子节点,父节点信息需要更新
    }
}
//清除了延迟标记, 要更新的sum
//再次更新的时候, 路过ancestor节点的时候,才会把当前的标记忘下推
void pushdown(int rt, int l, int r)
{
    if (add[rt]) { //fuck...
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];

        sum[rt] += (r - l + 1) * add[rt];
        add[rt] = 0;
    }
}

void pushup(int rt, int l, int r)
{
    int m = (l + r) >> 1;
    sum[rt] = (sum[rt << 1] + (m - l + 1) * add[rt << 1]);
    sum[rt] += (sum[rt << 1 | 1] + (r - m) * add[rt << 1 | 1]);
}

long long query(int l, int r, int L, int R, int rt)
{
    long long ret = 0;

    if (l <= L && r >= R) {
        ret = sum[rt] + (R - L + 1) * add[rt];
    } else {

        pushdown(rt, L, R);
        int m = (L + R) >> 1;
        if (l <= m)
           ret += query(l, r, L, m, rt << 1);

        if (r > m)
           ret += query(l, r, m + 1, R, rt << 1 | 1);
    }

    return ret;
}

//前序遍历
void traverse(int l, int r, int rt)
{
    printf("%d %d %lld %lld\n", l, r, sum[rt], add[rt]);

    if ( l != r) {
        int m = (l + r) >> 1;
        if (l <= m)
            traverse(l, m, rt << 1);
        if ( m + 1 <= r)
            traverse(m + 1, r, rt << 1 | 1);
    }
}
