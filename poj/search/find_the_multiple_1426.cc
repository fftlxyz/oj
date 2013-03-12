// poj
// fly2best
// 1426
// Accepted
// 388K
// 16MS
// G++
// 1309B
// 2013-02-23 09:10:42
// 思想的力量 很强大 很强大
// 这个题目要总结总结

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXN = 205; // n !< 200
int queue[MAXN];  //bfs 队列
int head, tail;

int save[MAXN];   //是从父节点选的0 还是1, -1, 表示还没访问到
int father[MAXN];  //把树构造起来, 指向了父节点


void bfs(int n);
void print_multiple(int p);


int main(int argc, const char *argv[])
{
    int n;

    while (scanf("%d", &n) != EOF && n != 0) {
        bfs(n);
        print_multiple(0);
        printf("\n");
    }

    return 0;
}

//用同余关系来进行剪枝是再好不过的事情了
// (A - B) % N = 0
// 如果(A*10^k + X) % N = 0
// 那么(B*10^k + X) % N = 0
// 把同余总结一下
//
void bfs(int n)
{
    head = tail = 0;
    int p, l, r;
    memset(save, -1, sizeof(save));
    memset(father, -1, sizeof(father));

    save[1 % n] = 1;
    queue[tail++] = save[1 % n];
    tail = tail % MAXN;

    while (save[0] == -1) {  //题目保证循环会终止
        p = queue[head++];
        head = head % MAXN;

        l = (p * 10) % n;
        r = (l + 1) % n;

        if (save[l] == -1) {
            save[l] = 0;

            queue[tail++] = l;
            tail = tail % MAXN;
            father[l] = p;
        }

        if (save[r] == -1) {
            save[r] = 1;

            queue[tail++] = r;
            tail = tail % MAXN;
            father[r] = p;
        }
    }
}

void print_multiple(int p)
{
    if ( father[p] != -1)
        print_multiple( father[p]);

    printf("%d", save[p]);
}
