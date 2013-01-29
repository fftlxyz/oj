/*
 * poj 3259
 * memory: 1856K
 * time: 922MS
 * code length: 5191B
 * date: 2012-10-31 09:42:27
 * */

/*
 * 水题目：说白了就是判断有没有负权环
 * 思路: 1. 求SCC
 *       2. 在每个SCC上，跑bellman-ford
 * 看到discuss里，有人说，这个从node1，开始是连通的，老子汗。。。。
 * 这题目，我WA了几次
 * 原因:1.没有考虑重边，我昨天想的时候想过的的，但是今天写的时候忘了,囧
 *      2.多个测试用例的时候，状态没有正确的初始化；
 * 超时:
 *      用的临接矩阵
 *      有500个点, bell-ford O(VE) = O(V^3) = 3*10^9 这个数据量大了
 * AC: 在跑Bellman-Ford的时候，换成了临接表, 求scc的时候还是用的临接矩阵
 *     所以虽然过了，还是时间开销还是很大。。。。。
 *     但是，懒得改了，这个程序都被我改成了一陀了。。。
 *     编码规范，求编码规范。。。。
 * */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 500;
const int MAXD = 25000001;
int graph[MAXN][MAXN];

vector<int> graphList[MAXN];

int d[MAXN];
int postNum[MAXN];
int ccNum[MAXN];
int ccSize[MAXN];
bool visited[MAXN];
int nNodes, nPaths, nHoles;

int g_sccNum;
int g_postNum;
void findscc();
void explore(int nodei);
void dfs_r();
void explore_r(int nodei);
bool bellman_ford(int cciNum);

int main(int argc, const char *argv[])
{

    int nCase;
    cin >> nCase;
    while( nCase-- )
    {
        cin >> nNodes >> nPaths >> nHoles;

        int e1, e2, w;

        memset(graph,0,sizeof(graph));

        for(int i = 0; i < nPaths; ++i) {
            cin >> e1 >> e2 >> w;
            bool isFirst =(graph[e1-1][e2-1] == 0);

            if(isFirst || graph[e1-1][e2-1] > w) {
                graph[e1-1][e2-1] = w;
                graph[e2-1][e1-1] = w;
            }

            if( isFirst ) {
                graphList[e1-1].push_back(e2-1);
                graphList[e2-1].push_back(e1-1);
            }
        }

        for(int i = 0; i < nHoles;++i){
            cin >> e1 >> e2 >> w;
            bool isFirst =(graph[e1-1][e2-1] == 0);
            graph[e1-1][e2-1] = -w;

            if( isFirst ) {
                graphList[e1-1].push_back(e2-1);
            }
        }

        findscc();

        bool isOk = false;
        for(int i = 1; i < g_sccNum; ++i){
            if(!bellman_ford(i)) {
                isOk = true;
                break;
            }
        }

        cout << (isOk ? "YES" : "NO") << endl;
    }

    return 0;
}

bool bellman_ford(int cciNum)
{
    int cciSize = ccSize[cciNum];

    int start;

    for(int i = 0; i < nNodes; ++i){
        if( ccNum[i] == cciNum ) {
            start = i;
            break;
        }
    }

    for(int i =0; i < nNodes; ++i) {
        d[i] = MAXD;
    }

    d[start] = 0;

    for(int i = 0; i < cciSize - 1; ++i) {
        for(int j  = 0; j < nNodes; ++j) {
            if( ccNum[j] == cciNum && d[j] != MAXD ) {
                for(int k = 0; k < graphList[j].size(); ++k) {
                    int m = graphList[j][k];
                    if( j!=m && ccNum[m] == cciNum ) {
                        if( graph[j][m]  ) {
                            //relax
                            if( d[m] > d[j] + graph[j][m])
                                d[m] = d[j] + graph[j][m];
                        }
                    }
                    // for(int k = 0; k < nNodes; ++k) {
                    // if( j!=k && ccNum[k] == cciNum ) {
                    // if( graph[j][k]  ) {
                    // //relax
                    // if( d[k] > d[j] + graph[j][k])
                    // d[k] = d[j] + graph[j][k];
                    // }
                    // }
                    // }
                }
            }
        }
    }


    for(int j  = 0; j < nNodes; ++j) {
        if( ccNum[j] == cciNum && d[j] != MAXD) {

            for(int k = 0; k < graphList[j].size(); ++k) {

                int m = graphList[j][k];
                if( j!=m && ccNum[m] == cciNum ) {
                    if( graph[j][m]  ) {
                        //relax
                        if( d[m] > d[j] + graph[j][m])
                            return false;
                    }
                }
                // for(int k = 0; k < nNodes; ++k) {
                // if( j!=k && ccNum[k] == cciNum ) {

                // if( graph[j][k]) {
                // //relax
                // if( d[k] > d[j] + graph[j][k])
                // return false;
                // }
                // }
                // }
            }
        }
    }

    return true;

}

//在reverse上的dfs
void dfs_r()
{
    g_postNum = 0;
    memset(visited,0,sizeof(visited));
    for(int i = 0; i < nNodes; ++i) {

        if(!visited[i]) {
            visited[i] = true;
            explore_r(i);
        }
    }
}

void explore_r(int nodei)
{
    for(int i = 0; i < nNodes; ++i){

        if( graph[i][nodei] && !visited[i] ) {
            visited[i] = true;
            explore_r(i);
        }

    }
    postNum[nodei] = ++g_postNum;
}

void findscc()
{
    //在逆图上求postNum
    dfs_r();
    g_sccNum = 0;
    memset(ccSize, 0, sizeof(ccSize));
    memset(visited, 0, sizeof(visited));
    while(1) {
        ++g_sccNum;
        int maxPostNum = -1;
        int nodei;
        for(int i = 0; i < nNodes; ++i){

            if(!visited[i] && postNum[i] > maxPostNum) {
                nodei =  i;
                maxPostNum = postNum[i];
            }
        }

        if(maxPostNum == -1)
            break;
        else {
            visited[nodei] = true;
            explore(nodei);
        }
    }


}

void explore(int nodei)
{
    ccNum[nodei] = g_sccNum;
    ++ccSize[g_sccNum];
    for(int i = 0; i < nNodes; ++i){

        if( graph[nodei][i] && !visited[i] ) {
            visited[i] = true;
            explore(i);
        }
    }
}
