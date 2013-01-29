/* poj 3253
 * memory: 876K
 * time: 32MS
 * complier: G++
 * code length: 2723B
 * date: 2012-11-19 20:38:23
 *
 * hufuman tree...
 * 本来想用贪心的，每次取最大的，测了几组数组，还没发现问题
 * 不过我有看到提示是hufuman树，灵光一想，就想起来了。
 * 这个题目用动态规划应该也能做
 *
 * 还有精度问题,我只注意到了，运算过程中不会溢出int，但是没考虑导运算结果会溢出
 */
#include <stdio.h>
#include <stdlib.h>

const int N = 20110;
struct Node
{
    int f;
    int len;
}nodes[2*N+1];

//小顶堆
int heap[N];
int xposa[2*N+1];
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
    int n = 0, ni = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        nodes[i].f = -1;
        scanf("%d", &nodes[i].len);
    }

    makeheap(n);
    ni = n;
    while( heapsize != 1 ) {
        int l = deletemin();
        int r = deletemin();
        nodes[ni].f = -1;
        nodes[ni].len = nodes[l].len + nodes[r].len;
        nodes[l].f = nodes[r].f = ni;
        insert(ni);
        ni++;
    }

    long long sum = 0;
    for(int i = 0; i < n; ++i) {
        int d = 0;
        int x = i;
        while ( nodes[x].f != -1 )
            ++d,  x = nodes[x].f;
        sum += (long long)nodes[i].len * d;
    }

    printf("%lld\n", sum);

    return 0;
}

int& xpos(int x)
{
    return xposa[x];
}

int key(int i)
{
    return nodes[i].len;
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
