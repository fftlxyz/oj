//
// 11301378	fly2best	2777	Accepted	2448K	407MS	G++	2716B	2013-03-02 09:38:24
// 没有注意swap
// 11301309	fly2best	2777	Wrong Answer			G++	2711B	2013-03-02 09:06:08
// 局部变量的初始化，我放在了一个分支里， 但是这个分支不一定执行
// 11301299	fly2best	2777	Wrong Answer			G++	2499B	2013-03-02 09:02:32
// 总体来说，这次写线段树，已经流畅多了，想的很清楚，大的逻辑没出问题，阴沟里翻船....
#include <stdio.h>

const int MAXN = 100005;

int color[MAXN << 2]; //表示整个区间上的颜色
int colors[MAXN << 2]; //表示区间上的有哪些颜色 才用bitmap

void pushup(int rt);
void pushdown(int rt);
void build(int l ,int r, int rt);
void update(int l, int r, int c, int L, int R, int rt);
int query(int l, int r, int L, int R, int rt);
int count_bit_one(int n);
void swap(int& a, int& b);

int main(int argc, const char *argv[])
{
    int n, colornum, opernum;
    scanf("%d%d%d\n", &n, &colornum, &opernum);
    build(1, n, 1);
    while (opernum--) {
        char oper;
        int a, b, c;
        scanf("%c", &oper);
        if (oper == 'C') {
            scanf("%d%d%d\n", &a, &b, &c);
            if (a > b)
                swap(a, b);
            update(a, b, c, 1, n, 1);
        } else {
            scanf("%d%d\n", &a, &b);
            if (a > b)
                swap(a,b);
            printf("%d\n", count_bit_one(query(a, b, 1, n, 1)));
        }
    }
    return 0;
}

void build(int l ,int r, int rt)
{
    if (l == r ) {
        color[rt] = 1;
        colors[rt] = 1 << 1;
    } else {
        int m = (l + r) >> 1;
        build(l, m , rt << 1);
        build(m + 1, r , rt << 1 | 1);
        pushup(rt);
    }
}

void update(int l, int r, int c, int L, int R, int rt)
{
    if (l <= L && R <= r) {
        color[rt] = c; //
        colors[rt] = 1 << c;
    } else {
        pushdown(rt);

        int m = (L + R) >> 1;
        if ( l <= m)
            update(l, r, c, L, m, rt << 1);
        if ( m+1 <= r)
            update(l, r, c, m + 1, R, rt << 1 |1);

        pushup(rt); //更新当前结点颜色
    }
}

//本结点的颜色是子结点颜色的或
void pushup(int rt)
{
    colors[rt] = colors[rt << 1] | colors[rt << 1 | 1];

    //没想到啊还有一个区间合并的问题
    //写build函数的时候才想起来
    if (color[rt << 1] == color[rt << 1 | 1]) {
        color[rt] = color[rt << 1];
    }
}

//把本结点的颜色传给子结点
void pushdown(int rt)
{
    if (color[rt] != 0) {
        color[rt << 1] = color[rt << 1 | 1]  = color[rt];
        colors[rt << 1] = colors[rt << 1 | 1] = 1 << color[rt];
        color[rt] = 0;
    }
}

int query(int l, int r, int L, int R, int rt)
{
    int ret = 0;
    if (l <= L && R <= r) {
        ret = colors[rt];
    } else {
        pushdown(rt);
        int m = (L + R) >> 1;
        if ( l <= m)
            ret |= query(l, r, L, m, rt << 1);
        if ( m+1 <= r)
            ret |= query(l, r, m + 1, R, rt << 1 |1);
    }

    return ret;
}

int count_bit_one(int n)
{
    int cnt = 0;
    while(n) {
        n = n & (n - 1);
        ++cnt;
    }
    return cnt;
}

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
