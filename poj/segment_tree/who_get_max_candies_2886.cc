// fly2best	2886	Accepted	16048K	1500MS	G++	2997B	2013-03-05 23:00:16
//
#include <stdio.h>
#include <string.h>

const int MAXN = 500050;
char name[MAXN][12];
int  card[MAXN];
int sum[MAXN << 2];

int max_turn[40]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400};
int max_candy[40]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,216};

void pushup(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void build(int l, int r, int rt)
{
    if (l == r) {
        sum[rt] = 1;
    } else {
        int m = (l + r) /2;
        build(l, m, rt << 1);
        build(m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}

void update(int p, int l, int r, int rt)
{
    if (l == r) {
        sum[rt] = 0;
    } else {

        int m = (l + r) >> 1;
        if (p <= m)
            update(p, l, m, rt << 1);
        else
            update(p, m + 1, r, rt << 1 | 1);
        pushup(rt);
    }
}

// 第p个数, flag = 1 所在的下标
int query(int p, int l, int r, int rt)
{
    if (l == r)
        return l;
    else {
        int m = (l + r) >> 1;
        if ( sum[rt << 1] >= p )
            return query(p, l, m , rt << 1);
        else
            return query(p - sum[rt << 1], m + 1, r , rt << 1 | 1);
    }
}

int main(int argc, const char *argv[])
{
    int n, k;
    int casei = 0;
    int turni, turn, candy;
    while(scanf("%d%d", &n, &k) != EOF)  {
        memset(name, 0, sizeof(name));
        memset(card, 0, sizeof(card));
        memset(sum, 0, sizeof(sum));

        // printf("case%d:\n", casei++);

        build(1, n, 1);

        for(int i = 0; i < n ; ++i) {
            scanf("%s %d", name[i], card + i);
            // printf("%s %d\n", name[i], card[i]);
        }

        turni=0;
        while(max_turn[turni]<=n) //寻找最大的n'
            turni++;
        turni--;

        candy = max_candy[turni];
        turn = max_turn[turni] - 1;

        int korder, nextk, nextkorder;
        korder = k;

        for (int i = n - 1; i >= 1 && turn; --i) {
            // printf("%s %d\n", name[k-1], card[k-1]);
            update(k, 1, n, 1); //删掉k
            nextk = card[k-1]; //下一个k的
            if (nextk > 0) //因为这个数去掉了,影响了其后面的数的序, 对其前面的数没有影响.
                nextkorder = korder + nextk - 1;
            else
                nextkorder = korder + nextk;
            while (nextkorder < 0)
                nextkorder += i;
            nextkorder = nextkorder % i;

            if (nextkorder == 0)
                nextkorder = i;
            k = query(nextkorder, 1, n, 1); //找出nextkorder, 所在的下标
            korder = nextkorder;
            --turn;
        }
        // printf("%s %d\n", name[k-1], card[k-1]);
        if (turn)
            k = query(1, 1, n, 1); //找出nextkorder, 所在的下标
        printf("%s %d\n", name[k-1], candy);
    }

    return 0;
}

