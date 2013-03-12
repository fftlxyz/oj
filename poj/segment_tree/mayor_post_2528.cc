// 郁闷啊，这题如果按照普通的方法
// 内存要报掉....
// 先不管内存，把线段树熟悉起来再说
// 找到方法了, 离散化
// run time error, 没道理,数组我都开足空间了
// 叶子节点可能没有标记的亲
// 11297996	fly2best	2528	Accepted	944K	79MS	G++	4194B	2013-03-01 10:56:15
// 11297937	fly2best	2528	Runtime Error			G++	4105B	2013-03-01 10:26:04
// 这道题,线段树,第一题
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 10005;
short int poster[N << 4];

int start[N];
int end[N];

int origin[N<<1];
int transport[N<<1];
int range;

bool isposter[N];

int binary_search(int *p, int n, int x);
int compare (const void * a, const void * b);
void pushdown(int rt);
void count_color(int rt);
void count_color2(int rt, int l, int r);
void update(int y1, int y2, int v, int rt, int L, int R);
void input();
void process();

int casenum;
int n;

int main(int argc, const char *argv[])
{
    scanf("%d", &casenum);
    int i;

    while (casenum--) {

        memset(poster, -1, sizeof(poster));
        memset(isposter, 0, sizeof(isposter));

        input();
        process();
        count_color2(1, 1, range);
        int count = 0;
        for (i = 0; i < n; ++i) {
            count += isposter[i];
        }
        printf("%d\n", count);
    }

    return 0;
}

// 将[y1,y2]设置成v
// rt表示当前结点, L, R,表示rt的范围
void update(int y1, int y2, int v, int rt, int L, int R)
{

    if (y1 <= L && y2 >= R) {
        // printf("%d %d %d %d\n", y1, y2, L, R);
        poster[rt] = v;
    } else {

        int lc = rt << 1;
        int rc = (rt << 1) | 1;
        int m = (L + R) >> 1;

        pushdown(rt);

        if (y1 <= m)
            update(y1, y2, v, lc, L, m);

        if (y2 > m)
            update(y1, y2, v, rc, m + 1, R);
    }
}

void pushdown(int rt)
{
    if (poster[rt] != -1) {
        int lc = rt << 1;
        int rc = lc + 1;

        poster[lc] = poster[rc] = poster[rt];
        poster[rt] = -1;
    }
}

void count_color(int rt)
{
    if ( poster[rt] != -1) {
        isposter[poster[rt]] = 1;
    } else {
        count_color(rt << 1);
        count_color(rt << 1 | 1);
    }
}

void count_color2(int rt, int l, int r)
{
    if ( poster[rt] != -1) {
        isposter[poster[rt]] = 1;
        // printf("%d %d %d\n", l, r, poster[rt]);
    } else {
        //叶子节点可能没有标记, 老子汗
        if (l == r)
            return;
        int m = (l + r) >> 1;
        count_color2(rt << 1, l, m);
        count_color2(rt << 1 | 1, m + 1, r);
    }
}


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void input()
{

    scanf("%d", &n);

    int i;
    for (i = 0; i < n; ++i) {
        scanf("%d %d", &start[i], &end[i]);
        origin[2*i] = start[i];
        origin[2*i + 1] = end[i];
    }
}

void process()
{
    int i;
    //process
    qsort (origin, 2 * n, sizeof(int), compare);

    // for (i = 0; i < 2 * n; ++i) {
        // printf("%d ", origin[i]);
    // }
    // printf("\n");

    int prev = origin[0];
    int j = 1;
    transport[0] = j;

    for (i = 1; i < 2 * n; ++i) {

        if (origin[i] == origin[i - 1]) {
            // transport[i] = transport[i - 1];
        } else if (origin[i] > prev + 1) {
            j += 2;
            prev = origin[i];
            // transport[i] = j;
        } else {
            j += 1;
            prev = origin[i];
            // transport[i] = j;
        }

        transport[i] = j;
    }

    range = j;

    // for (i = 0; i < 2 * n; ++i) {
        // printf("%d ", transport[i]);
    // }
    // printf("\n");

    for (i = 0; i < n; ++i) {
        int li, ri, l, r;
        li = binary_search(origin, 2*n, start[i]);
        l = transport[li];
        ri = binary_search(origin, 2*n, end[i]);
        r = transport[ri];

        update(l,r, i, 1, 1, range);
    }

}


// 听说二分是个坑
// int a[] = { -2 , 0, 1, 2, 3, 3 , 5, 6, 7, 8, 9, 10, 156};

// for (int i = 0; i < sizeof(a) / sizeof(a[0]) ; ++i) {
// int index = binary_search(a, sizeof(a) / sizeof(a[0]), i);
// printf("%d %d\n", i, index);
// }
int binary_search(int *p, int n, int x)
{
    int l = 0, r = n;
    int m;

    // [l, r)
    while( l < r) {
        m = (l + r) / 2;
        if (p[m] == x)
            return m;
        else if (p[m] > x) {
            r = m;
        } else if (p[m] < x) {
            l = m + 1;
        }
    }
    return -1;
}
