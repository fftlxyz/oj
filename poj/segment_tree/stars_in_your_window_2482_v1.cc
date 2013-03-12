// There are several test cases in the input.
// The first line of each case contains 3 integers: n, W, H,
// indicating the number of stars,
// the horizontal length and the vertical height of the rectangle-shaped window.
// Then n lines follow, with 3 integers each: x, y, c,
// telling the location (x, y) and the brightness of each star. No two stars are on the same point.
// There are at least 1 and at most 10000 stars in the sky. 1<=W，H<=1000000, 0<=x，y<2^31.


// 这个题目的思路
// 我受到poj2352的启发, 可以转化为一维的
// 先对start排序, 按照, y 递增的顺序, 如果y相同, 按x递增的顺序
//
// 如果 W, H
// 1.加入(H-1)行数据, 然后, 看W - 1的线段能覆盖的最大亮度
// 2.删除第1 行的数据, 加入先一行, 重复
//
// W - 1 的线段能覆盖的最大亮度的计算方法
// 用扫描线的方法
// 先转化成, W - 1 线段，覆盖尽量多的点, 然后求亮度和
//
// 亮度和, 用线段树
// 需要离散化处理, 因为x的范围很大, 但是点不多.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point
{
    int x;
    int y;
    int brightness;
};

const int MAXN = 10010;

int sum[MAXN << 2];

Point points[MAXN];
int X[MAXN];

int compare_int(const void *p1, const void *p2);
int compare_point(const void *p1, const void *p2);
int binary_search(int key, int *p, int n);
void update(int p, int c, int l, int r, int rt);
int query(int y1, int y2, int l, int r, int rt);
static int inline max(int a, int b) { return a >b ? a: b; }

int main(int argc, const char *argv[])
{
    int n, H, W;
    int i, j, k, m, maxbrightness;
    while( scanf("%d%d%d", &n, &W, &H) != EOF ) {

        for (i = 0; i < n; ++i) {
            scanf("%d%d%d", &(points[i].x), &(points[i].y), &(points[i].brightness));
            X[i] = points[i].x;
        }
        qsort(points, n, sizeof(Point), compare_point);
        qsort(X, n, sizeof(int), compare_int);

        maxbrightness = -1;
        memset(sum,0, sizeof(sum));

        // for (i = 0; i < n; ++i) {
            // printf("%d %d %d\n", points[i].x, points[i].y, points[i].brightness);
        // }

        m = 1;
        for (i = 1; i < n; ++i)
            if (X[i] != X[i - 1]) X[m++] = X[i];

        i = j = 0;
        while (i < n) {

            //只有第一次,添加H-1层, 以后都是添加一层
            while ( j < n && points[j].y - points[i].y < H ) {
                int dx = binary_search(points[j].x, X, m);
                update(dx, points[j].brightness, 0, m, 1); //x上增加亮度;
                ++j;
            }

            // 扫描线
            // int l1 , l2 = 0;

            // for ( l1 = 0; l1 < m; ++l1) {
                // while ( l2 < m && X[l2] - X[l1] < W)
                    // ++l2;
                // --l2;
                // maxbrightness = max(query(l1, l2, 0, m, 1), maxbrightness);
            // }

            // 最后一层已经被考虑, 那么终止吧
            if (j == n)
                break;

            //删掉i所在层
            k = i;
            while (points[k].y == points[i].y) {
                int dx = binary_search(points[k].x, X, m);
                update(dx, -points[k].brightness, 0, m, 1); //减少x上的亮度
                ++k;
            }
            i = k; //i变成下一层
        }

        printf("%d\n", maxbrightness);
    }
    return 0;
}

int binary_search(int key, int *p, int n)
{
    int l = 0;
    int r = n;
    int m;

    //[l, r)
    while (l < r) {
        m = (l + r) >> 1;
        if (p[m] == key)
            break;
        else if (key < p[m])
            r = m;
        else
            l = m + 1;
    }

    return m;
}

int compare_point(const void *p1, const void *p2)
{
    const Point *pl = (const Point *)p1;
    const Point *pr = (const Point *)p2;
    if ( pl-> y == pr->y)
        return pl->x - pr->x;
    else
        return pl->y - pr->y;
}
int compare_int(const void *p1, const void *p2)
{
    return (*(int *)p1) - (*(int *)p2);
}

void update(int p, int c, int l, int r, int rt)
{
    if (l == r)
        sum[rt] += c;
    else {
        int m = (l + r) >> 1;

        if (p <= m)
            update(p, c, l, m, rt << 1);
        else
            update(p, c, m + 1, r, rt << 1 | 1);
        sum[rt] = sum[rt << 1]  + sum[rt << 1 | 1];
    }
}

int query(int y1, int y2, int l, int r, int rt)
{
    if (y1 <= l && r <= y2)
        return sum[rt];
    else {
        int m = (l + r) >> 1;
        int ret = 0;
        if (y1 <= m)
            ret += query(y1, y2, l, m, rt << 1);
        if ( m + 1 <= y2)
            ret += query(y1, y2, m + 1, r , rt << 1 | 1);
        return ret;
    }
}

