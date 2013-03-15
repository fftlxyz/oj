// 11351027	fly2best	2492	Accepted	16048K	1297MS	G++	3443B	2013-03-15 08:56:31
// 改了改1703的输出,1A
// 我的并查集写的比较简单, 没有用按rank合并,只是用了简单的路径压缩
// 这个题目的时间要求是10s， 有个牛人0s.....
// 我是用了两个并查集来解决这个问题的, 改天去看看别人的思路.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int MAXN = 1000100;

int scc[MAXN];
int color[MAXN];
int scc_color[MAXN][2]; //同一个scc内两种颜色

int find_scc(int i);
int find_color(int i);
bool insert(int a, int b);

int main(int argc, const char *argv[])
{
    int casenum;
    scanf("%d", &casenum);

    for (int casei = 1; casei <= casenum; ++casei) {

        memset(scc, -1, sizeof(scc));
        memset(color, -1, sizeof(color));
        memset(scc_color, -1, sizeof(scc_color));

        int n, m;
        scanf("%d%d\n", &n, &m);

        bool foundSuspicious = false;
        for(int i = 0; i < m; ++i) {
            int a, b;
            scanf("%d%d\n", &a, &b);

            //过掉输入
            if (foundSuspicious)
                continue;

            if(!insert(a, b)) {
                foundSuspicious = true;
            }

        }

        printf("Scenario #%d:\n", casei);
        if (foundSuspicious) {
            printf("Suspicious bugs found!\n\n");
        }
        else {
            printf("No suspicious bugs found!\n\n");
        }

    }


    return 0;
}

int find_scc(int i)
{
    if (scc[i] == -1)
        return i;

    scc[i] = find_scc(scc[i]);
    return scc[i];
}

int find_color(int i)
{
    if (color[i] == -1)
        return i;
    color[i] = find_color(color[i]);
    return color[i];
}

bool insert(int a, int b)
{
    int scca = find_scc(a);
    int sccb = find_scc(b);

    //怎么设置color
    int colora = find_color(a);
    int colorb = find_color(b);

    if (scca != sccb) {

        // 这个地方有四种情况要处理
        // 我最开始的思路是对的
        //都等于-1, 相等只有这一种情况
        //
        //1. 左边是一个结点, 右边是一个结点
        //2. 左边是一个结点, 右边是一个结点以上
        //3. 左边是一个结点以上, 右边是一个结点
        //4. 左边是一个结点以上,右边是一个结点以上
        //
        bool isalonea = scc_color[scca][0] == scc_color[scca][1];
        bool isaloneb = scc_color[sccb][0] == scc_color[sccb][1];

        if (isalonea && isaloneb) {
            //把b连过来
            scc[sccb] = scca;
            //设置colora 和 colorb 为本scc内的代表
            scc_color[scca][0] = colora;
            scc_color[scca][1] = colorb;
        }

        if (isalonea && !isaloneb) {
            scc[scca] = sccb;

            color[a] = scc_color[sccb][0];
            if (colorb == scc_color[sccb][0]) {
                color[a] = scc_color[sccb][1];
            }
        }

        if (!isalonea && isaloneb) {
            scc[sccb] = scca;

            color[b] = scc_color[scca][0];
            if (colora == scc_color[scca][0]) {
                color[b] = scc_color[scca][1];
            }
        }

        if (!isalonea && !isaloneb) {
            scc[sccb] = scca;

            color[colorb] = scc_color[scca][0];
            bool iszero = true;
            if (scc_color[scca][0] == colora) {
                color[colorb] = scc_color[scca][1];
                iszero = false;
            }

            int other = 0;
            if( colorb == scc_color[sccb][0]) {
                other = 1;
            }
            color[scc_color[sccb][other]] = scc_color[scca][1];
            if (!iszero) {
                color[scc_color[sccb][other]] = scc_color[scca][0];
            }

        }

        return true;

    } else {

        if (colora == colorb)
            return false;
    }

    return true;
}
