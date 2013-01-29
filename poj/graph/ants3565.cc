/* poj 3565
 * memory: 472K
 * time: 0MS
 * complier: G++
 * code length: 4221B
 * date: 2012-11-14 19:57:00
 * km 思路，很巧妙
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))
#define dist(x1, y1, x2, y2) (sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)))
#define eps 1e-8

const int N = 105;
int n;

double lx[N];
double ly[N];
double weight[N][N];

int s[N];
int t[N];

int xy[N];
int yx[N];
int prev[N];


double slack[N];
int slackx[N];

void initlabel()
{
    memset(ly, 0, sizeof(ly));

    for(int i = 0; i < n; ++i) {
        lx[i] = INT_MIN;
    }

    for (int i = 0; i < n; ++i) {
        for ( int j = 0; j < n; ++j) {
            lx[i] = max(lx[i], weight[i][j]);
        }
    }
}

void update()
{
    int x, y;
    double delta = INT_MAX;

    for (y = 0; y < n; ++y)
        if (!t[y]) delta = min(delta, slack[y]);
    for (x = 0; x < n; ++x)
        if (s[x]) lx[x] -= delta;
    for (y = 0; y < n; ++y)
        if (t[y]) ly[y] += delta;
    for (y = 0; y < n; ++y)
        if (!t[y]) slack[y] -= delta;

}

//( prev[prevx], xy[x]) (x, xy[x])
// 1. update prev
// 2. update s
// 3. update slack, slackx
void addedge(int x, int prevx)
{
    prev[x] = prevx;
    s[x] = true;
    for (int y = 0; y < n; ++y) {
        if ( slack[y] > lx[x] + ly[y] - weight[x][y] ) {
            slack[y] = lx[x] + ly[y] - weight[x][y];
            slackx[y] = x;
        }
    }
}

// init s, t, bfs stuff
// bfs
//   if find augment path , argument
//   else
//      update, and get slack y = 0
//      is augmentable
//          yes, augment
//      no, add yx[y] to bfs queue, bfs
//argument, main reverse the path
void match(int i)
{
    int x, y;
    int q[N], rd , wd;

    memset(s, 0, sizeof(s));
    memset(t, 0, sizeof(t));
    memset(prev, -1, sizeof(prev));

    x = i;
    s[x] = true;
    for (y = 0; y < n; ++y) {
        slack[y] = lx[x] + ly[y] - weight[x][y];
        slackx[y] = x;
    }
    rd = wd = 0;
    q[wd++] = x;

    //find x match
    while (true){

        while (rd < wd) {
            x = q[rd++];
            for ( y = 0; y < n; ++y) {
                if (!t[y] &&  fabs(lx[x] + ly[y] - weight[x][y]) < eps) {
                    if ( yx[y] == -1 )
                        break;
                    else {
                        t[y] = true;
                        q[wd++] = yx[y];  //special bfs, when y is chosed, x is decided
                        addedge(yx[y], x);
                    }
                }
            }

            if ( y < n )
                break;
        }

        if (y < n)
            break;

        update();

        rd = wd = 0; //not necessary
        for ( y = 0; y < n; ++y) {
            if ( !t[y] && fabs(slack[y]) < eps ) {
                if (yx[y] == -1) {
                    x = slackx[y];
                    break;
                } else {
                    t[y] = true;
                    if(!s[yx[y]]) {
                        q[wd++] = yx[y];

                        //slackx[y] must be in the tree
                        //because the we we define slack[y]
                        addedge(yx[y], slackx[y]);
                    }
                }
            }
        }
        if (y < n)
            break;

    }

    //augment
    for( int cx = x, cy = y, txy; cx != -1; cx = prev[cx], cy = txy) {
        txy = xy[cx];
        xy[cx] = cy;
        yx[cy] = cx;
    }

}

int hungarian()
{
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    initlabel();

    for(int i = 0; i < n; ++i)
         match(i);

    return 0;
}

void input()
{
    scanf("%d", &n);
    int antx[N], anty[N], apptreex[N], apptreey[N];

    for (int i = 0 ; i < n; ++i)
        scanf("%d%d", &antx[i], &anty[i]);

    for (int i = 0 ; i < n; ++i)
        scanf("%d%d", &apptreex[i], &apptreey[i]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            weight[i][j] = -dist(antx[i], anty[i], apptreex[j], apptreey[j]);
        }

}

void output()
{
    for(int i = 0 ; i < n; ++i) {
        printf("%d\n", xy[i] + 1);
    }
}

int main(int argc, const char *argv[])
{

    input();
    hungarian();
    output();
    return 0;
}
