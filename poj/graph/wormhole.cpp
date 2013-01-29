/*
 * poj 3259
 * memory: 1856K
 * time: 922MS(wormhole0) -> 625MS(wormhole)
 * code length: 5191B
 * date: 2012-10-31 09:42:27
 * */

/*
 * 水题目：说白了就是判断有没有负权环
 * 思路: 1.求SCC
 *       2.在每个SCC上，跑bellman-ford
 *       3.bugfix: 2012-10-31 14:00
 *         中午睡觉的时候,想了想，不用求scc了
 *         1)找一个没有被访问的节点，开始bellman-ford;
 *         2)重复1，知道没有剩余
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
 *
 *     bugfix: 时间还是有625MS，郁闷啊～～
 * */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = 500;
const int MAX_D = 25000001;

struct Node
{
    int nodeindex;
    int weight;
};

vector<Node> vertex[MAX_N+1];
bool visited[MAX_N + 1];
int dist[MAX_N + 1];

int nnodes;
int npaths;
int nholes;


bool bellman_ford(int nodei);
int main(int argc, const char *argv[])
{

    int ncase;
    cin >> ncase;
    while (ncase--) {


        cin >> nnodes >> npaths>> nholes;

        int e1, e2, w;
        Node node;

        for(int i = 0; i < MAX_N + 1; ++i)
            vertex[i].clear();

        for (int i = 0; i < npaths; ++i) {
            cin >> e1 >> e2 >> w;

            node.nodeindex = e2;
            node.weight = w;
            vertex[e1].push_back(node);

            node.nodeindex = e1;
            vertex[e2].push_back(node);
        }

        for (int i =0; i < nholes; ++i){
            cin >> e1 >> e2 >> w;

            node.nodeindex = e2;
            node.weight = -w;
            vertex[e1].push_back(node);
        }

        bool iscircle = false;
        memset(visited, 0, sizeof(visited[0])*(nnodes + 1));
        for(int i = 1; i <= nnodes; ++i) {

            if(!visited[i]) {
                bool isok = bellman_ford(i);
                iscircle = !isok;

                if(iscircle)
                    break;
            }
        }

        cout << (iscircle? "YES": "NO") << endl;
    }

    return 0;
}

bool bellman_ford(int nodei)
{
    memset(dist, MAX_D, sizeof(dist[0])*(nnodes+1));
    dist[nodei] = 0;

    for(int i = 0; i< nnodes - 1; ++i){
        for(int nodei = 1; nodei <= nnodes; ++nodei){
            if( dist[nodei] != MAX_D ){

                int edgesize = vertex[nodei].size();
                for(int edgei = 0; edgei < edgesize; ++edgei){

                    int nodej = vertex[nodei][edgei].nodeindex;
                    int edgew = vertex[nodei][edgei].weight;

                    visited[nodej] = true;

                    if( dist[nodej] > dist[nodei] + edgew ){
                        dist[nodej] = dist[nodei] + edgew;
                    }
                }
            }
        }
    }

    for(int nodei = 1; nodei <= nnodes; ++nodei){
        if( dist[nodei] != MAX_D ){

            int edgesize = vertex[nodei].size();
            for(int edgei = 0; edgei < edgesize; ++edgei){

                int nodej = vertex[nodei][edgei].nodeindex;
                int edgew = vertex[nodei][edgei].weight;


                if( dist[nodej] > dist[nodei] + edgew ){
                    return false;
                }
            }
        }
    }

    return true;
}
