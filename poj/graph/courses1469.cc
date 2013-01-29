/* poj 1469
 * memory: 508K
 * time: 375MS
 * complier: G++
 * code length: 1412B
 * date: 2012-11-11 10:00:52
 * 套的模板 poj3041 asteriod的 。
 * 1A
 * 二分图的最大匹配
 * */


#include <stdio.h>
#include <string.h>

const int MAX_N = 305;
const int MAX_P = 105;

int adjl[MAX_P][MAX_N];
int match[MAX_N];
int used[MAX_N];

int hungary(int n);

int hungary();
bool crosspath(int k);
int main(int argc, const char *argv[])
{
    int casenum;
    scanf("%d", &casenum);

    while(casenum--) {
        int p, n, count, s;
        scanf("%d%d", &p, &n);
        for (int i =1; i <= p; ++i) {
            scanf("%d", &count);
            adjl[i][0] = 0;
            for (int j = 1; j <= count; ++j) {
                scanf("%d", &s);
                adjl[i][++adjl[i][0]] = s;
            }
        }
        int maxmatch = hungary(p);

        if( maxmatch == p)
            printf("YES\n");
        else
            printf("NO\n");

    }


    return 0;
}

int hungary(int n)
{
    int maxmatch = 0;
    memset(match, 0, sizeof(match));
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
