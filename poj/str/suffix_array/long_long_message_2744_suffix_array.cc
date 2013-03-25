
//这个题目是裸的最长公共字串
//n的范围是10^5,
//用O(n^2)的动态规划，估计是要超时的
//虽然时间给了4s
//所以要用后缀数组来做
//时间复杂度是O(nlogn)
//
//后缀数组有O(n)的方法,不过我还没学
//先用O(nlogn)的吧,我觉得没问题
//果然1A..., 不过641MS似乎多了点
//11386465	fly2best	2774	Accepted	3380K	641MS	G++	2888B	2013-03-23 22:37:48
//今天看了一天的后缀数组, 值了....

#include <stdio.h>
#include <string.h>
#include <assert.h>

const int MAXN = 100100;
const int MAXM = 255;

char str1[MAXN];
char str2[MAXN];

char str[MAXN << 1];

int sa[MAXN << 1];
int rank[MAXN << 1];
int t2[MAXN << 1];

int c[MAXM];

int height[MAXN << 1];

void  build_sa(char *s, int *sa, int *x, int *y, int *c, int m);
void get_height(char *str, int *sa, int *height, int *rank);

int main(int argc, const char *argv[])
{
    scanf("%s", str1);
    scanf("%s", str2);

    int str1len = strlen(str1);
    int str2len = strlen(str2);

    strcpy(str, str1);
    str[str1len] = '$';
    strcpy(str + str1len + 1, str2);


    build_sa(str, sa, rank, t2, c, MAXM);

    get_height(str, sa, height, rank);

    int maxsubstr = -1;

    for (int i = 1; i < str1len + str2len + 1; i++) {

        // 属于两个不同的数组
        if ((sa[i] < str1len && sa[i-1] > str1len)
                ||(sa[i-1] < str1len && sa[i] > str1len) ) {

            if (height[i] > maxsubstr)
                maxsubstr = height[i];
        }
    }

    printf("%d\n", maxsubstr);


    return 0;
}


void  build_sa(char *s, int *sa, int *x, int *y, int *c, int m)
{
    int i;
    int n = strlen(s);

    for (i = 0; i < m; ++i) { c[i] = 0; }

    for (i = 0; i < n; ++i) { c[x[i] = s[i]]++; }

    for (i = 1; i < m; ++i) { c[i] += c[i -1]; }

    for (i = n -1; i >= 0; --i) {
        sa[--c[x[i]]] = i;  //sa 是一个数组, sa[i] = j;  表示序为i是后缀j
    }


    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;

        for (i = n - k; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) {
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        }

        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[y[i]]]++;
        for(i = 0; i < m; i++) c[i] += c[i - 1];
        for(i = n -1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];

        int *t = x;
        x = y;
        y = t;

        p = 1;
        x[sa[0]] = 0;
        for (i = 1; i < n; i++) {
            if ( y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) {
                x[sa[i]] = p - 1;
            } else {
                x[sa[i]] = p++;
            }
        }


        if (p >= n)
            break;
        m = p;
    }

    for (i = 0; i < n; ++i) {
        assert( x[sa[i]] == i );
        assert( sa[x[i]] == i );
    }
}

void get_height(char *str, int *sa, int *height, int *rank)
{
    int i, j, k = 0;

    int n = strlen(str);

    for (i = 0; i < n; ++i)
        rank[sa[i]] = i;

    for (i = 0; i < n; ++i) {
        if (k)
            k--;

        if (!rank[i]) {
            continue;
        }

        j = sa[rank[i] - 1];  //当rank[i] = 0 时, 汗啊~~

        while (str[i + k] == str[j + k])
            k++;
        height[rank[i]] = k;
    }
}
