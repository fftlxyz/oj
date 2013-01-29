/* poj 3686
 * memory: 1048K
 * time: 32MS
 * complier: G++
 * code length: 4213B
 * date: 2012-11-14 21:58:05
 * 见图的思路那确实是很巧妙
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))

const int N = 55;
const int M = 55 * 55;
int n, m;

int lx[N];
int ly[M];
int weight[N][M];

int s[N];
int t[M];

int xy[N];
int yx[M];
int prev[N];


int slack[M];
int slackx[M];

void initlabel()
{
    memset(ly, 0, sizeof(ly));

    for(int i = 0; i < n; ++i) {
        lx[i] = INT_MIN;
    }

    for (int i = 0; i < n; ++i) {
        for ( int j = 0; j < m; ++j) {
            lx[i] = max(lx[i], weight[i][j]);
        }
    }
}

void update()
{
    int x, y, delta = INT_MAX;

    for (y = 0; y < m; ++y)
        if (!t[y]) delta = min(delta, slack[y]);
    for (x = 0; x < n; ++x)
        if (s[x]) lx[x] -= delta;
    for (y = 0; y < m; ++y)
        if (t[y]) ly[y] += delta;
    for (y = 0; y < m; ++y)
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
    for (int y = 0; y < m; ++y) {
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
    for (y = 0; y < m; ++y) {
        slack[y] = lx[x] + ly[y] - weight[x][y];
        slackx[y] = x;
    }
    rd = wd = 0;
    q[wd++] = x;

    //find x match
    while (true){

        while (rd < wd) {
            x = q[rd++];
            for ( y = 0; y < m; ++y) {
                if (!t[y] &&  lx[x] + ly[y] == weight[x][y]) {
                    if ( yx[y] == -1 )
                        break;
                    else {
                        t[y] = true;
                        q[wd++] = yx[y];  //special bfs, when y is chosed, x is decided
                        addedge(yx[y], x);
                    }
                }
            }

            if ( y < m )
                break;
        }

        if (y < m)
            break;

        update();

        rd = wd = 0; //not necessary
        for ( y = 0; y < m; ++y) {
            if ( !t[y] && slack[y] == 0) {
                if (yx[y] == -1) {
                    x = slackx[y];
                    break;
                } else {
                    t[y] = true;
                    if(!s[yx[y]]) {
                        q[wd++] = yx[y];
                        addedge(yx[y], slackx[y]);
                    }
                }
            }
        }
        if (y < m)
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

    int w = 0;
    for(int x = 0; x < n; ++x)
        w += weight[x][xy[x]];

    return w;

}

void input()
{
    int nj, nw;
    scanf("%d%d", &nj, &nw);
    int z[N][N];

    for(int i = 0; i < nj; ++i)
        for(int j = 0; j < nw; ++j)
            scanf("%d", &z[i][j]);

    n = nj;
    m = nw * nj;

    for( int i = 0; i < nj; ++i) {
        for( int j = 0; j < nw; ++j){
            for( int k = 0; k < nj; ++k) {
                weight[i][j*nj+k] = -(k+1)*z[i][j];
            }
        }
    }
}


int main(int argc, const char *argv[])
{
    int ncase;
    scanf("%d", &ncase);

    for (int i = 0; i < ncase; ++i) {
        input();
        double w = -hungarian();
        printf("%.6f\n", w / n);
    }

    return 0;
}
