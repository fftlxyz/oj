#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100 + 5;
const int MAX_EDGE_N = MAX_N * MAX_N;
const int MAX_HEAP_SIZE = MAX_EDGE_N;

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
int dist[MAX_N];

//小顶堆
int heap[MAX_N];
int xposa[MAX_N];
int heapsize;

void decreasekey(int x);
void insert(int x);
int deletemin();
void makeheap(int n);
int key(int i);
void shiftdown(int x, int i);
void bubbleup(int x, int i);
int minchild(int i);
int& xpos(int x);

int main(int argc, const char *argv[])
{
    int M, n;
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

    for(int i = 0; i <= n; ++i)
        dist[i] = 10001;

    dist[0] = 0;

    makeheap(n+1);

    while( heapsize != 0 ){
        int x = deletemin();

        for(int j = 0; j < node[x].size(); ++j){

            const Edge& ei = edges[node[x][j]];
            if( dist[ei.to] > dist[x] + ei.weight && ( abs(level[ei.to] - level[x]) <= M || x == 0 )) {
                dist[ei.to] = dist[x] + ei.weight;

                decreasekey(ei.to);
            }
        }
    }

    cout << dist[1] << endl;
    return 0;
}

int& xpos(int x)
{
    return xposa[x];
}

int key(int i)
{
    return dist[i];
}

//元素不应改为负数
void insert(int x)
{
    heapsize += 1;
    xpos(x) = heapsize - 1;
    bubbleup(x, heapsize - 1);
}

//减小了权值，更新优先级队列
void decreasekey(int x)
{
    bubbleup(x, xpos(x));
}

//元素不应改为负数
int deletemin()
{
    int x = -1;
    if( heapsize != 0){
        x = heap[0];
        heap[0] = heap[heapsize - 1];
        xpos(heap[0]) = 0;
        --heapsize;
        shiftdown(heap[0], 0);
    }
    return x;
}
void makeheap(int n)
{
    heapsize = n;
    for (int i = 0; i < n; ++i){
        heap[i] = i;
        xpos(i) = i;
    }

    for (int i = n -1; i > -1; --i){
        shiftdown(heap[i],i);
    }
}

void bubbleup(int x, int i)
{
    int p = (i - 1)/2;
    while (i != 0 && key(heap[p]) > key(x)){
        heap[i] = heap[p];
        xpos(heap[p]) = i;
        i = p;
        p = (i -1)/2;
    }
    heap[i] = x;
    xpos(x) = i;
}

void shiftdown(int x, int i)
{
    int c = minchild(i);
    while (c != -1 && key(heap[c]) < key(x)) {
        heap[i] = heap[c];
        xpos(heap[c]) = i;
        i = c;
        c = minchild(i);
    }
    heap[i] = x;
    xpos(x) = i;
}

int minchild(int i)
{
    int leftchild = 2 * i + 1;
    int rightchild = 2 * i + 2;

    if ( leftchild > heapsize -1 )
        return -1;
    else if ( rightchild > heapsize -1) {
        return leftchild;
    } else {
        return key(heap[leftchild]) < key(heap[rightchild]) ? leftchild : rightchild;
    }
}


void testheap()
{


    // for(int i =0 ; i <= n; ++i) {
        // cout << heap[i] << " ";
    // }
    // cout << endl;
    // for(int i =0 ; i <= n; ++i) {
        // cout << dist[heap[i]] << " ";
    // }
    // cout << endl;


    // for(int i = 0; i < heapsize; ++i)
        // keya[i] = i;


    // makeheap(10);

    // for(int i = 0; i < heapsize; ++i)
        // cout << heap[i] << " ";
    // cout << endl;

    // for(int i = 0; i < heapsize; ++i)
        // cout << xpos(heap[i]) << " ";
    // cout << endl;


    // keya[5] = -100;

    // decreasekey(5);

    // // for(int i = 0; i < 3; ++i)
        // // deletemin();

    // for(int i = 0; i < heapsize; ++i)
        // cout << heap[i] << " ";
    // cout << endl;

    // for(int i = 0; i < heapsize; ++i)
        // cout << xpos(heap[i]) << " ";
    // cout << endl;

}
