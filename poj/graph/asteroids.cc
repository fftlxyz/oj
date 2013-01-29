/*
 * poj 3041
 * memory: 1184K
 * time: 0MS
 * complier: G++
 * code length:1017B
 * date: 2012-11-04 20:02:41
 * */

// 很不错的二分图的最小覆盖=二分图的最大匹配的例子

#include <stdio.h>
#include <string.h>

const int MAX_N = 505;

int adjl[MAX_N][MAX_N];
int match[MAX_N];
int used[MAX_N];

int hungary();

int n, k;

int hungary();
bool crosspath(int k);
int main(int argc, const char *argv[])
{
    scanf("%d%d", &n, &k);
    int x, y;
    while(k--){
        scanf("%d%d", &x, &y);
        adjl[x][++adjl[x][0]] = y;
    }

    int maxmatch = hungary();

    printf("%d\n", maxmatch);

    return 0;
}

int hungary()
{
    int maxmatch = 0;
    for(int i = 1; i <= n; ++i){
        memset(used, 0, sizeof(used));
        if(crosspath(i))
            ++maxmatch;
    }
    return maxmatch;
}

bool crosspath(int k)
{
    for(int i = 1; i <= adjl[k][0]; ++i){
        int j = adjl[k][i];

        //used[j] 表示死胡同
        if(!used[j]){
            used[j] = true;
            if(match[j] ==0 || crosspath(match[j])){
                match[j] = k;
                return true;
            }
        }
    }
    return false;
}
