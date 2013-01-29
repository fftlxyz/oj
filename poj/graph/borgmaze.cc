/*
 * poj 3026
 * memory: 1096K
 * time: 47MS
 * complier: G++
 * codelength: 5621B
 * date: 2012-11-03 21:22:35
 * 最小生成树
 * ps: 套用1789的代码 1A
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
using std::queue;

const int MAX_MAZE_N = 55;
const int MAX_N = MAX_MAZE_N * MAX_MAZE_N;
const int MAX_EDGE_N = MAX_N * MAX_N;
const int MAX_HEAP_SIZE = MAX_EDGE_N;
const int MAX_EDGE_WEIGHT = MAX_N;

char maze[MAX_MAZE_N][MAX_MAZE_N];

int nodehash[MAX_MAZE_N][MAX_MAZE_N];
bool nodevis[MAX_MAZE_N][MAX_MAZE_N];
int dirx[] = {1, -1, 0, 0};
int diry[] = {0, 0, 1, -1};

int nodesnum = 0;
struct Node
{
    int x;
    int y;
    int step;
} nodes[MAX_N];

int edges[MAX_N][MAX_N];

int prev[MAX_N];
int cost[MAX_N];
int flag[MAX_N];

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
    int ncase;
    scanf("%d",&ncase);
    while (ncase--){
        int m, n;
        char buf[255] = {0};
        scanf("%d%d",&m,&n);

        memset(maze,0,sizeof(maze));
        nodesnum = 0;
        for(int i = 0; i < n; ++i){
            //pass white char
            while(getchar() != '#');
            buf[0] = '#';
            gets(buf+1);

            for(int j =0; (j < m) && (j < strlen(buf)); ++j) {
                maze[i][j] = buf[j];
                if(buf[j] == 'A' || buf[j] == 'S') {
                    Node node;
                    node.x = i;
                    node.y = j;
                    nodehash[i][j] = nodesnum;
                    nodes[nodesnum++] = node;
                }
            }
        }

        for(int i = 0; i < nodesnum; ++i) {
            for(int j = 0; j < nodesnum; ++j){
                edges[i][j] = MAX_EDGE_WEIGHT;
            }
        }

        for(int i = 0; i < nodesnum; ++i){
            //bfs
            //create graph
            queue<Node> nodeQueue;
            nodes[i].step = 0;
            nodeQueue.push(nodes[i]);
            memset(nodevis, 0, sizeof(nodevis));

            nodevis[nodes[i].x][nodes[i].y] = true;

            while(!nodeQueue.empty()) {
                Node node = nodeQueue.front();
                nodeQueue.pop();

                for(int j = 0; j < 4; ++j) {
                    int x = node.x + dirx[j];
                    int y = node.y + diry[j];

                    if( x >=0 && x < n && y >= 0 && y < m && !nodevis[x][y] && maze[x][y] != '#'){

                        nodevis[x][y] = true;

                        if( maze[x][y] == 'A' || maze[x][y] == 'S'){
                            int nodeto = nodehash[x][y];
                            edges[i][nodeto] = node.step + 1;
                        } else{
                            Node newNode;
                            newNode.x = x;
                            newNode.y = y;
                            newNode.step = node.step + 1;
                            nodeQueue.push(newNode);
                        }
                    }
                }
            }
        }

        // for(int i  = 0; i < nodesnum; ++i) {
            // for(int j  = 0; j < nodesnum; ++j) {
                // printf("%d ", edges[i][j]);
            // }
            // printf("\n");
        // }



        for(int i = 0; i < nodesnum; ++i){
            cost[i] = MAX_N * MAX_N;
        }
        memset(flag, 0, sizeof(flag));
        cost[0] = 0;

        makeheap(nodesnum);

        int sum = 0;
        while( heapsize != 0){
            int x = deletemin();
            flag[x] = 1;
            sum += cost[x];

            for(int j = 0; j < nodesnum; ++j){
                if( !flag[j] && cost[j] > edges[x][j] ){
                    cost[j] = edges[x][j];
                    prev[j] = x;
                    decreasekey(j);
                }
            }
        }

        printf("%d\n",sum);
    }

    return 0;
}

int& xpos(int x)
{
    return xposa[x];
}

int key(int i)
{
    return cost[i];
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
