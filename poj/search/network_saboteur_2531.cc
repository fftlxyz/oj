// 11294165	fly2best	2531	Accepted	5440K	750MS	G++	2308B	2013-02-28 10:13:05
// 11294141	fly2best	2531	Accepted	44224K	1032MS	G++	2161B	2013-02-28 10:09:49
// 汗数组开大了，多写了一个0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_QUEUE = 190000;
const int MAX_N = 21;

int traffic[MAX_N][MAX_N];

int queue[MAX_QUEUE];
int head , tail;
static inline void push(int x);
static inline int pop();
static inline bool is_empty();

int cut[1100000];

int main(int argc, const char *argv[])
{

    int i, j, n, mask;
    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &traffic[i][j]);
        }
    }

    int max = 0;
    memset(cut, -1, sizeof(cut));

    mask = ((1 << n) - 1);
    // printf("mask:%d\n", mask);
    push(0); //根结点
    cut[0] = 0;
    while (!is_empty()) {
        int p = pop();
        bool seti[MAX_N] = {0};

        for ( i = 0; i < n; ++i) {
            if (p & (1 << i)) {
                seti[i] = true;
            }
        }

        for ( i = 0; i < n; ++i) {

            if (!seti[i]) {

                int c = p | (1 << i);  //放入第i个结点
                // printf("c:%d\n", c);

                //若n = 5 ,可以认为位 11100 与 00011是一个状态, 因为图是对称的
                //is_set(c) && !is_set(~c & mask)
                if ((cut[c] == -1) && (cut[~c & mask] == -1)) {
                    int delta =0;
                    for ( j = 0; j < n; ++j) {
                        if (seti[j])
                            delta -= traffic[i][j];
                        else
                            delta += traffic[i][j];
                    }

                    cut[c] = cut[p] + delta;
                    // printf("cut[%d]=%d\n", c, cut[c]);
                    push(c);

                    if (max < cut[c])
                        max = cut[c];
                }
            }
        }
    }

    printf("%d\n", max);

    return 0;
}

static inline void push(int x)
{
    queue[tail++] = x;
    if (tail >= MAX_QUEUE)
        tail -= MAX_QUEUE;
}

static inline int pop()
{
    int front = queue[head++];
    if (head >= MAX_QUEUE)
        head -= MAX_QUEUE;

    return front;
}

static inline bool is_empty()
{
    return head == tail;
}

// int c, k, n;
// n = 20;
// c = 1;

// for (k = 1; k <= 10; ++k) {
    // c = c * (n - k + 1) / k;
    // printf("%d %d\n", k, c);
// }
