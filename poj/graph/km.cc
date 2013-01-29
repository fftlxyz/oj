// poj 2195
// 428K
// 0MS
// G++
// 8020B
// 2012-11-13 08:53:49
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))
#define N 105             //max number of vertices in one part
#define INF 100000000    //just infinity

int cost[N][N];          //cost matrix
int n, max_match;        //n workers and n jobs
int lx[N], ly[N];        //labels of X and Y parts
int xy[N];               //xy[x] - vertex that is matched with x,
int yx[N];               //yx[y] - vertex that is matched with y
bool S[N], T[N];         //sets S and T in algorithm
int slack[N];            //as in the algorithm description
int slackx[N];           //slackx[y] such a vertex, that
// l(slackx[y]) + l(y) - w(slackx[y],y) = slack[y]
int prev[N];             //array for memorizing alternating paths

int hungarian();


void init_labels()
{
    memset(ly, 0, sizeof(ly));
    for (int x = 0; x < n; x++)
        lx[x] = INT_MIN;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
            lx[x] = max(lx[x], cost[x][y]);
}

void update_labels()
{
    int x, y, delta = INF;             //init delta as infinity
    for (y = 0; y < n; y++)            //calculate delta using slack
        if (!T[y])
            delta = min(delta, slack[y]);
    for (x = 0; x < n; x++)            //update X labels
        if (S[x]) lx[x] -= delta;
    for (y = 0; y < n; y++)            //update Y labels
        if (T[y]) ly[y] += delta;
    for (y = 0; y < n; y++)            //update slack array
        if (!T[y])
            slack[y] -= delta;
}

void add_to_tree(int x, int prevx)
    //x - current vertex,prevx - vertex from X before x in the alternating path,
    //so we add edges (prevx, xy[x]), (xy[x], x)
{
    S[x] = true;                    //add x to S
    prev[x] = prevx;                //we need this when augmenting
    for (int y = 0; y < n; y++)    //update slacks, because we add new vertex to S
        if (lx[x] + ly[y] - cost[x][y] < slack[y])
        {
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
}

void augment()                         //main function of the algorithm
{
    if (max_match == n) return;        //check wether matching is already perfect
    int x, y, root;                    //just counters and root vertex
    int q[N], wr = 0, rd = 0;          //q - queue for bfs, wr,rd - write and read
    //pos in queue
    memset(S, false, sizeof(S));       //init set S
    memset(T, false, sizeof(T));       //init set T
    memset(prev, -1, sizeof(prev));    //init set prev - for the alternating tree
    for (x = 0; x < n; x++)            //finding root of the tree
        if (xy[x] == -1) {
            q[wr++] = root = x;
            prev[x] = -2;
            S[x] = true;
            break;
        }

    for (y = 0; y < n; y++) {           //initializing slack array
        slack[y] = lx[root] + ly[y] - cost[root][y];
        slackx[y] = root;
    }
    //second part of augment() function
    while (true) {                                                       //main cycle
        while (rd < wr) {                                               //building tree with bfs cycle
            x = q[rd++];                                                //current vertex from X part
            for (y = 0; y < n; y++)                                     //iterate through all edges in equality graph
                if (cost[x][y] == lx[x] + ly[y] &&  !T[y]) {
                    if (yx[y] == -1) break;                             //an exposed vertex in Y found, so
                    //augmenting path exists!
                    T[y] = true;                                        //else just add y to T,
                    q[wr++] = yx[y];                                    //add vertex yx[y], which is matched
                    //with y, to the queue
                    add_to_tree(yx[y], x);                              //add edges (x,y) and (y,yx[y]) to the tree
                }
            if (y < n) break;                                           //augmenting path found!
        }
        if (y < n) break;                                               //augmenting path found!

        update_labels();                                                //augmenting path not found, so improve labeling
        wr = rd = 0;
        for (y = 0; y < n; y++)
            //in this cycle we add edges that were added to the equality graph as a
            //result of improving the labeling, we add edge (slackx[y], y) to the tree if
            //and only if !T[y] &&  slack[y] == 0, also with this edge we add another one
            //(y, yx[y]) or augment the matching, if y was exposed
            if (!T[y] &&  slack[y] == 0) {
                if (yx[y] == -1) {                                      //exposed vertex in Y found - augmenting path exists!
                    x = slackx[y];
                    break;
                }
                else {
                    T[y] = true;                                        //else just add y to T,
                    if (!S[yx[y]]) {
                        q[wr++] = yx[y];                                //add vertex yx[y], which is matched with
                        //y, to the queue
                        add_to_tree(yx[y], slackx[y]);                  //and add edges (x,y) and (y,
                        //yx[y]) to the tree
                    }
                }
            }
        if (y < n) break;                                               //augmenting path found!
    }

    if (y < n)                                                          //we found augmenting path!
    {
        max_match++;                                                    //increment matching
        //in this cycle we inverse edges along augmenting path
        for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty)
        {
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
        augment();                                                      //recall function, go to step 1 of the algorithm
    }
}//end of augment() function

int hungarian()
{
    int ret = 0;                      //weight of the optimal matching
    max_match = 0;                    //number of vertices in current matching
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    init_labels();                    //step 0
    augment();                        //steps 1-3
    for (int x = 0; x < n; x++)       //forming answer there
        ret += cost[x][xy[x]];
    return ret;
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

            cost[i][j] = -abs(mx-hx) - abs(my-hy);

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
