// poj 2482
// 11318827	fly2best	2482	Time Limit Exceeded			G++	3669B	2013-03-06 19:45:43
// 思路是对的时间复杂度是 O(n^2log(n))
// 11322167	fly2best	2482	Wrong Answer			G++	4219B	2013-03-07 18:23:29
// 思路是对的时间复杂度是 O(nlog(n)), 不知道哪里溢出了, int全换成long long, 过了.
// 11322198	fly2best	2482	Accepted	1412K	157MS	G++	4534B	2013-03-07 18:32:43

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point
{
    long long x; long long y; long long brightness;
};

const long long MAXN = 10010;

long long sum[MAXN << 2];
long long add[MAXN << 2];

Point points[MAXN];
long long X[MAXN << 1];

void pushup(long long rt);
void pushdown(long long rt);
int compare_llong(const void *p1, const void *p2);
int compare_point(const void *p1, const void *p2);
long long binary_search(long long key, long long *p, long long n);
void update(long long y1, long long y2, long long c, long long l, long long r, long long rt);
static long long inline max(long long a, long long b) { return a >b ? a: b; }

int main(int argc, const char *argv[])
{
    long long n, H, W;
    long long i, j, k, m, maxbrightness;
    while( scanf("%lld%lld%lld", &n, &W, &H) != EOF ) {

        for (i = 0; i < n; ++i) {
            scanf("%lld%lld%lld", &(points[i].x), &(points[i].y), &(points[i].brightness));
            X[i] = points[i].x;
            X[i + n] = X[i] + W - 1;
            // points[i].flag = 1;
            // points[i + n] = points[i];  // set y and brightness
            // points[i + n].x = x + W;
            // points[i + n].flag = -1;
        }
        qsort(points, n, sizeof(Point), compare_point);
        qsort(X, 2*n, sizeof(long long), compare_llong);

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
                long long x1 = binary_search(points[j].x, X, m);
                long long x2 = binary_search(points[j].x + W - 1, X, m);
                update(x1, x2, points[j].brightness, 0, m - 1, 1); //x上增加亮度;
                ++j;
            }

            maxbrightness = max(sum[1], maxbrightness);

            // 扫描线
            // long long l1 , l2 = 0;

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
                long long x1 = binary_search(points[k].x, X, m);
                long long x2 = binary_search(points[k].x + W - 1, X, m);
                update(x1, x2, -points[k].brightness, 0, m - 1, 1); //x上增加亮度;
                ++k;
            }
            i = k; //i变成下一层
        }

        printf("%lld\n", maxbrightness);
    }
    return 0;
}

long long binary_search(long long key, long long *p, long long n)
{
    long long l = 0;
    long long r = n;
    long long m;

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
int compare_llong(const void *p1, const void *p2)
{
    return (*(long long *)p1) - (*(long long *)p2);
}

void update(long long y1, long long y2, long long c, long long l, long long r, long long rt)
{
    if (y1 <= l && r <= y2) {
        sum[rt] += c;
        add[rt] += c;
    }
    else {
        pushdown(rt);
        long long m = (l + r) >> 1;
        if (y1 <= m)
            update(y1, y2, c, l, m, rt << 1);
        if (m + 1 <= y2)
            update(y1, y2, c, m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}
void pushdown(long long rt)
{
    long long lc = rt << 1;
    long long rc = lc + 1;

    if (add[rt]) {

        sum[lc] += add[rt];
        sum[rc] += add[rt];
        add[lc] += add[rt];
        add[rc] += add[rt];
        add[rt] = 0;
    }
}

void pushup(long long rt)
{
    sum[rt] = max(sum[rt << 1] , sum[rt << 1 | 1]);
}
