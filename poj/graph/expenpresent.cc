/*
 * poj 1062
 * memroy: 764K
 * time: 547MS //this is not accectable
 * complier: G++
 * code length: 2056B
 * date: 2012-11-03 11:50:19
 */
/*
 * dfs 裸搜，暴之。。。
 * 我很好奇的是，为什么我的时间是547MS，别人的dfs是0ms
 * 还有，这道题目，怎么dijkstra做。。。
 * 今天搞定～～
 * */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100 + 5;
const int MAX_EDGE_N = MAX_N * MAX_N;

int edgesnum = 0;
struct Edge
{
    int from;
    int to;
    int weight;
}edges[MAX_EDGE_N];

//临接表
vector<int> node[MAX_N];
int level[MAX_N];
int M;
int choosen[MAX_N];

int dfs(int x,int minl, int maxl);

int main(int argc, const char *argv[])
{
    int n;
    scanf("%d%d",&M,&n);

    Edge edge;

    for(int i = 1; i <= n; ++i){
        int p, l, x;
        scanf("%d%d%d", &p, &l, &x);

        edge.from = 0;
        edge.to = i;
        edge.weight = p;
        level[i] = l;

        node[0].push_back(edgesnum);
        edges[edgesnum++] = edge;

        for(int j = 0; j < x; ++j) {
            int t,v;
            scanf("%d%d", &t, &v);

            edge.from = t;
            edge.to = i;
            edge.weight = v;

            node[t].push_back(edgesnum);
            edges[edgesnum++] = edge;
        }
    }

    int result = dfs(0,-1,-1);
    cout << result << endl;

    return 0;
}

int dfs(int x,int minl, int maxl)
{
    if(x == 1)
        return 0;

    int min = 10000;

    for(int i = 0; i < node[x].size(); ++i){
        Edge & ei = edges[node[x][i]];
        int bakminl = minl;
        int bakmaxl = maxl;

        if (x == 0) {
            minl = level[ei.to];
            maxl = level[ei.to];
        } else {
            if(maxl < level[ei.to]) {
                maxl = level[ei.to];
            }
            if(minl > level[ei.to]) {
                minl = level[ei.to];
            }
        }

        if( choosen[ei.to] ==0 && maxl - minl <= M) {
            choosen[ei.to] = 1;

            int result = dfs(ei.to, minl, maxl);
            if(min > result + ei.weight ) {
                min = result + ei.weight;
            }

            choosen[ei.to] = 0;
        }

        maxl = bakmaxl;
        minl = bakminl;

    }
    return min;
}
