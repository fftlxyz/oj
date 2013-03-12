// fly2best
// 3126
// Accepted
// 2728K
// 94MS
// G++
// 3166B
// 2013-02-22 21:40:58
// 郁闷的一个小错误阿。。。。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash[10000];
bool isprime[10000];

short int primers[1100];
short int graph[1100][1100];
short int primers_cnt = 0;

short int father[1100];
bool isvisit[1100];
short int queue[1100];
int head = 0;
int tail = 0;


void getprimers();
bool isconnected(short int x, short int y);
void construct_graph();
int bfs(int u, int v);

int main(int argc, const char *argv[])
{
    getprimers();
    construct_graph();

    // for (int i = 0; i < primers_cnt; ++i) {
        // for (int j = i; j < primers_cnt; ++j) {
            // printf("%d %d\n", primers[i], primers[j]);
        // }
    // }


    int n ,u ,v, dist;

    scanf("%d", &n);

    while(n--) {

        scanf("%d %d", &u, &v);

        if (u == v) {
            printf("%d\n", 0);
            continue;
        }

        dist = bfs(hash[u], hash[v]);
        if (dist) {
            printf("%d\n", dist);
        } else {
            printf("impossible\n");
        }
    }

    return 0;
}

int bfs(int u, int v)
{
    int p, dist = 0;
    bool isok = false;
    head = tail = 0;
    memset(isvisit, 0, sizeof(isvisit));
    memset(father, -1, sizeof(father));

    queue[tail++] = u;
    isvisit[u] = true;

    while ( head != tail) {

        p = queue[head++];

        head = head % 1100;

        for (int i = 0; i < primers_cnt; ++i) {

            if ( graph[p][i] && !isvisit[i]) {

                queue[tail++] = i;
                tail = tail % 1100;

                father[i] = p;
                isvisit[i] = true;

                if (i == v) {
                    isok = true;
                    break;
                }

            }
        }

        if (isok)
            break;
    }

    if (isok) {
        p = v;
        // printf("%d ", primers[p]);
        p = father[p];
        while(p != -1) {
            ++dist;
            // printf("%d ", primers[p]);
            p = father[p];
        }
    }

    return dist;

}

void construct_graph()
{
    for(int i = 0; i < primers_cnt; ++i) {
        for(int j = i; j < primers_cnt; ++j) {
            graph[i][j] =  isconnected(primers[i], primers[j]);
            graph[j][i] = graph[i][j];
        }
    }
}

bool isconnected(short int x, short int y)
{
    int diff = 0;

    for( int i = 0; i < 4; ++i) {

        if ((x % 10) != (y % 10)) {
            diff++;
        }
        x /= 10;
        y /= 10;
    }

    return diff == 1;
}

void getprimers()
{

    memset(primers, -1, sizeof(primers));
    memset(isprime, 1, sizeof(isprime));

    int s = 2;

    for(int i = s; i < 10000; ++i) {
        if(isprime[s]) {
            for(int j = 2; i * j < 10000; ++j) {
                isprime[i * j] = false;
            }
        }
    }

    int index = 0;
    for(int i=1000; i < 10000; ++i){
        if( isprime[i]) {
            hash[i] = index;
            primers[index] = i;
            // printf("%d %d\n", index, i);
            index++;
        }
    }
    primers_cnt = index;

}
