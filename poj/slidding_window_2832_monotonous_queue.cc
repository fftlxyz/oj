#include <stdio.h>

const int MAXN = 1000100;
//nnd, 这个我少写了一个0, 我说怎么TLE, runtime error, fuck...

struct Node {
    int v;
    int index;
} queue[MAXN];


int input[MAXN];

int head, tail;
void input_max(int i, int key);
void input_min(int i, int key);

int n, k;
int main(int argc, const char *argv[])
{
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf("%d", input + i);
    }

    for (int i = 0; i < k -1; ++i) {
        input_min(i, input[i]);
    }

    for (int i = k - 1; i < n; ++i) {
        input_min(i, input[i]);
        printf("%d ", queue[head].v);
    }
    printf("\n");

    head = tail = 0;

    for (int i = 0; i < k - 1; ++i) {
        input_max(i, input[i]);
    }

    for (int i = k -1; i < n; ++i) {
        input_max(i, input[i]);
        printf("%d ", queue[head].v);
    }
    printf("\n");

    return 0;
}


void input_max(int i, int key)
{
    while (head != tail && queue[tail - 1].v <= key) {
        --tail;
    }

    queue[tail].v = key;
    queue[tail].index = i;
    ++tail;

    while (head != tail && (i - queue[head].index >= k)) {
        ++head;
    }


}

void input_min(int i, int key)
{
    while (head != tail && queue[tail - 1].v >= key) {
        --tail;
    }

    queue[tail].v = key;
    queue[tail].index = i;
    ++tail;

    while (head != tail && (i - queue[head].index >= k)) {
        ++head;
    }
}
