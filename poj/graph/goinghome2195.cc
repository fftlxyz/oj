/* poj 2195
 * memory: 472K
 * time: 0MS
 * complier: G++
 * code length: 4755B
 * date: 2012-11-14 07:44:50
 * 这个题是km第一题，确实交的蛮纠结。km的模板写的有问题。
 * 忽略的几个地方。
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))

const int N = 205;
int n;

int lx[N];
int ly[N];
int weight[N][N];

int s[N];
int t[N];

int xy[N];
int yx[N];
int prev[N];


int slack[N];
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
    int x, y, delta = INT_MAX;

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

            if ( y < n )
                break;
        }

        if (y < n)
            break;

        update();

        rd = wd = 0; //not necessary
        for ( y = 0; y < n; ++y) {
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

    int w = 0;
    for(int x = 0; x < n; ++x)
        w += weight[x][xy[x]];

    return w;

}

bool input()
{
    int row, column;
    char buf[N];
    int human[N];
    int home[N];
    int huc,hoc;
    huc = hoc = 0;

    scanf("%d%d\n", &row, &column);
    if ( row == 0 && column == 0)
        return false;

    for (int i = 0; i < row; ++i) {
        gets(buf);
        // printf("%s\n", buf);
        for (int j = 0; j < column; ++j) {
            if (buf[j] == 'm') {
                human[huc++] = i * column + j;
            }
            else if( buf[j] == 'H') {
                home[hoc++] = i * column + j;
            }
        }
    }

    n = huc;

    for (int i = 0; i < huc; ++i) {
        int mx = human[i] / column ;
        int my = human[i] % column ;

        for (int j = 0; j < hoc; ++j) {
            int hx = home[j] / column;
            int hy = home[j] % column;

            weight[i][j] = -abs(mx-hx) - abs(my-hy);

        }
    }
    // for (int i = 0; i < hoc; ++i) {

        // for (int j = 0; j < hoc; ++j) {
            // printf("%d ", weight[i][j]);
        // }
        // printf("\n");
    // }
    return true;
}

int main(int argc, const char *argv[])
{
    while(input()) {
        printf("%d\n", -hungarian());
    }
    return 0;
}
