
//思路是这样子的
//
//判断两个点是否属于一个颜色
//1. 两个点是是一个scc,  返回颜色相同与否即可
//2. 若两个点不是一个scc，则无法确定颜色是否相同.
//
//解决思路:
//判是否是一个scc, 用并查集
//一个颜色内是否颜色相同, 用并查集
// 11350980	fly2best	1703	Accepted	1944K	688MS	G++	4086B	2013-03-15 08:37:12
// 11347247	fly2best	1703	Wrong Answer			G++	2648B	2013-03-14 09:54:54
// 11347237	fly2best	1703	Time Limit Exceeded			G++	2594B	2013-03-14 09:49:14

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int MAXN = 100100;

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

    while (casenum--) {
        memset(scc, -1, sizeof(scc));
        memset(color, -1, sizeof(color));
        memset(scc_color, -1, sizeof(scc_color));

        int n, m;
        scanf("%d%d\n", &n, &m);

        for(int i = 0; i < m; ++i) {
            char oper;
            int a, b;
            scanf("%c%d%d\n", &oper, &a, &b);
            if (oper == 'A') {

                int scca = find_scc(a);
                int sccb = find_scc(b);
                if (scca != sccb) {
                    printf("Not sure yet.\n");
                } else
                {
                    int colora = find_color(a);
                    int colorb = find_color(b);
                    if (colora == colorb) {
                        printf("In the same gang.\n");
                    } else {
                        printf("In different gangs.\n");
                    }
                }

            } else if (oper == 'D') {
                if(!insert(a, b))
                    printf("error\n");
            } else {
                printf("%c: error\n", oper);
            }

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
