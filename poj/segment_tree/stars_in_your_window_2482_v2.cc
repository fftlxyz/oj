// There are several test cases in the input.
// The first line of each case contains 3 integers: n, W, H,
// indicating the number of stars,
// the horizontal length and the vertical height of the rectangle-shaped window.
// Then n lines follow, with 3 integers each: x, y, c,
// telling the location (x, y) and the brightness of each star. No two stars are on the same point.
// There are at least 1 and at most 10000 stars in the sky. 1<=W，H<=1000000, 0<=x，y<2^31.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point
{
    int x; int y; int brightness;
};

const int MAXN = 10010;

int sum[MAXN << 3];
int add[MAXN << 3];

Point points[MAXN << 1];
int X[MAXN << 1];

void pushup(int rt);
void pushdown(int rt);
int compare_int(const void *p1, const void *p2);
int compare_point(const void *p1, const void *p2);
int binary_search(int key, int *p, int n);
void update(int y1, int y2, int c, int l, int r, int rt);
static int inline max(int a, int b) { return a >b ? a: b; }

int main(int argc, const char *argv[])
{
    int n, H, W;
    int i, j, k, m, maxbrightness;
    while( scanf("%d%d%d", &n, &W, &H) != EOF ) {

        for (i = 0; i < n; ++i) {
            scanf("%d%d%d", &(points[i].x), &(points[i].y), &(points[i].brightness));
            X[i] = points[i].x;
            X[i + n] = X[i] + W - 1;
            // points[i].flag = 1;
            // points[i + n] = points[i];  // set y and brightness
            // points[i + n].x = x + W;
            // points[i + n].flag = -1;
        }
        qsort(points, n, sizeof(Point), compare_point);
        qsort(X, 2*n, sizeof(int), compare_int);

        maxbrightness = -1;
        memset(sum,0, sizeof(sum));
        memset(add,0, sizeof(add));

        // for (i = 0; i < n; ++i) {
            // printf("%d %d %d\n", points[i].x, points[i].y, points[i].brightness);
        // }

        m = 1;
        for (i = 1; i < 2*n; ++i)
            if (X[i] != X[i - 1]) X[m++] = X[i];

        i = j = 0;
        while (i < n) {

            //只有第一次,添加H-1层, 以后都是添加一层
            while ( j < n && points[j].y - points[i].y < H ) {
                int x1 = binary_search(points[j].x, X, m);
                int x2 = binary_search(points[j].x + W - 1, X, m);
                update(x1, x2, points[j].brightness, 0, m - 1, 1); //x上增加亮度;
                ++j;
            }

            maxbrightness = max(sum[1], maxbrightness);

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
                int x1 = binary_search(points[k].x, X, m);
                int x2 = binary_search(points[k].x + W - 1, X, m);
                update(x1, x2, -points[k].brightness, 0, m - 1, 1); //x上增加亮度;
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

void update(int y1, int y2, int c, int l, int r, int rt)
{
    if (y1 <= l && r <= y2) {
        sum[rt] += c;
        add[rt] += c;
    }
    else {
        pushdown(rt);
        int m = (l + r) >> 1;
        if (y1 <= m)
            update(y1, y2, c, l, m, rt << 1);
        if (m + 1 <= y2)
            update(y1, y2, c, m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}
void pushdown(int rt)
{
    int lc = rt << 1;
    int rc = lc + 1;

    if (add[rt]) {

        sum[lc] += add[rt];
        sum[rc] += add[rt];
        add[lc] += add[rt];
        add[rc] += add[rt];
        add[rt] = 0;
    }
}

void pushup(int rt)
{
    sum[rt] = max(sum[rt << 1] , sum[rt << 1 | 1]);
}
