
/* poj
 * fly2best
 * 2488
 * Accepted
 * 388K
 * 16MS
 * G++
 * 1784B
 * 2013-02-24 10:57:05
 */
#include <stdio.h>
#include <string.h>

int n;
int p, q;
int vis[36];
int prev[36];
int last;

bool dfs(int cur, int nums);
void output(int pos);

void test()
{
    for(int i = 1; i < 14; ++i)
        for(int j = 1; j< 14; ++j)
        {
            if ( i * j < 26)
                printf("%d %d\n", i, j);
        }
}

int main(int argc, const char *argv[])
{

    scanf("%d", &n);
    int i;

    for (i=0; i < n; ++i) {
        scanf("%d %d", &p, &q);
        memset(prev, -1, sizeof(prev));
        memset(vis, 0, sizeof(vis));

       printf("Scenario #%d:\n", i+1);
       vis[0] = true;
       last = -1;
       if(dfs(0, 1)) {
           output(last);
           printf("\n");
       } else {
           printf("impossible\n");
       }
       printf("\n");

    }

    return 0;
}

bool dfs(int cur, int nums)
{

    //已纪小心注意了，但还是搞错了 ,汗..
    static int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    static int dy[] = {-1, 1, -2, 2, -2, 2, -1 ,1};

    int i, x, y, nextx, nexty;

    x = cur % q;
    y = cur / q;

    for(i = 0; i < 8; ++i) {

        nextx = dx[i] + x;
        nexty = dy[i] + y;
        if ((nextx >=0 && nextx < q)
                && (nexty >= 0 && nexty < p)
                && !vis[nexty *q + nextx]) {

            vis[nexty*q + nextx] = true;
            prev[nexty*q + nextx] = cur;

            if (dfs(nexty*q + nextx, nums + 1)) {
                return true;
            }
            vis[nexty*q + nextx] = false; //回溯
        }
    }

    //已找到最后一个结点
    if (nums == p * q ) {
        last = cur;
        return true;
    }

    return false;

}

void output(int pos)
{
    if (prev[pos] != -1)
        output(prev[pos]);
    printf("%c%c", 'A' + (pos % q), pos / q + '1');
}
