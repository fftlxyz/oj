
// 算法竞赛入门经典 训练指南上的习题
// 后缀数组-字符串处理的有力工具中 也有提到
// 你妹啊...
// 11389773	fly2best	3294	Accepted	2156K	1125MS	G++	6091B	2013-03-24 20:15:49
// 11389697	fly2best	3294	Wrong Answer			G++	5879B	2013-03-24 19:56:29
// 11389648	fly2test	3294	Wrong Answer			C++	5761B	2013-03-24 19:42:58
// 11389644	fly2test	3294	Wrong Answer			G++	5833B	2013-03-24 19:41:50
// 11389631	fly2best	3294	Wrong Answer			G++	5754B	2013-03-24 19:39:14
// 11388372	fly2best	3294	Wrong Answer			G++	5698B	2013-03-24 15:15:19
// 11388270	fly2best	3294	Wrong Answer			G++	5610B	2013-03-24 14:55:23
//
// 除了空间开小了以外，还犯了一个没注意的错误
// 就是如果 char 大于127, 是个负数
// 在计数排序的时候就挂了, 数组下标成负数了...
//
// ps: 有空再回来优化时间吧，我已经注意到有些地方可以优化了
// 比如: s, t的范围不大于n/2, 下面就不用算了...
//      我用的后缀数组是O(nlogn)的
//

#include <stdio.h>
#include <string.h>
#include <assert.h>

const int MAXN = 101000;
const int MAXM = 255;


char str[MAXN];

char lifeform[110][1100];
int lifelen[110];

int sa[MAXN];
int rank[MAXN];
int t2[MAXN];

int c[MAXM];

int height[MAXN];

void  build_sa(char *s, int *sa, int *x, int *y, int *c, int m);
void get_height(char *str, int *sa, int *height, int *rank);
int get_stri(int si, int * lifelen, int n);
bool is_len_p(int p, int *sa, int *height, int strlen, int *lifelen, int n);
void print_len_p(int p, char * str, int *sa, int *height, int strlen, int *lifelen, int n);

int main(int argc, const char *argv[])
{

    int n, i, len;

    while (scanf("%d", &n) != EOF && n != 0) {

        len = 0;
        for (i = 0; i < n; ++i) {
            scanf("%s",lifeform[i]);
            lifelen[i] = strlen(lifeform[i]);
            strcpy(str + len, lifeform[i]);
            len += lifelen[i];
            str[len] = 'z' + 1 + i; //不会溢出, 我算过了
            len++;
            str[len] = '\0'; //这个地方如果不是我想吧字符长打印出来怎么会想到这里呢?
        }

        build_sa(str, sa, rank, t2, c, MAXM);
        get_height(str, sa, height, rank);

        int l = 0;
        int r = 1000000;

        for (int i = 0; i < n; i++)
            if (r > lifelen[i])
                r = lifelen[i];

        int maxlen = 0;

        while (l <= r) {
            int m = l + (r - l) / 2;

            bool is_m_ok = is_len_p(m, sa, height, len, lifelen, n);

            // printf("%d %d\n", m, is_m_ok);

            if (is_m_ok) {
                maxlen = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        // printf("%d\n", maxlen);

        if (maxlen != 0) {
            print_len_p(maxlen, str, sa, height, len,lifelen, n);
        } else {
            printf("?\n\n");
        }


    }

    return 0;
}


bool is_len_p(int p, int *sa, int *height, int strlen, int *lifelen, int n)
{

    if (p == 0 || n == 1)
        return true;

    bool flag[110] = {0};

    bool is_m_ok = false;

    for (int s = 0, i = 1; i < strlen; ++i) {

        if (height[i] < p) {
            int t = i;

            memset(flag, 0, sizeof(flag));
            for (int j = s; j < t; ++j) {
                flag[get_stri(sa[j], lifelen, n)] = true;
            }

            int cnt = 0;
            for (int j = 0; j < n; ++j)
                cnt += flag[j];

            if (cnt > n / 2) {
                is_m_ok = true;
                break;
            }
            s = t;
        }
    }
    return is_m_ok;
}

void print_len_p(int p, char * str, int *sa, int *height, int strlen, int *lifelen, int n)
{
    bool flag[110] = {0};

    if (n == 1) {
        str[strlen-1] = '\0';
        printf("%s\n\n", str);
        return;
    }

    for (int s = 0, i = 1; i < strlen; ++i) {

        if (height[i] < p) {
            int t = i;

            memset(flag, 0, sizeof(flag));
            for (int j = s; j < t; ++j) {
                flag[get_stri(sa[j], lifelen, n)] = true;
            }

            int cnt = 0;
            for (int j = 0; j < n; ++j)
                cnt += flag[j];

            if (cnt > n / 2) {
                for( int j = 0; j < p; ++j) {
                    putchar(str[sa[s] + j]);
                }
                putchar('\n');
            }

            s = t;
        }
    }

    printf("\n");
}


//这个当然可以用二分查找来处理
//因为n最大为100, 没必去用二分
// printf("%s\n", str);
// for (int i = 0; i < len; ++i)
// printf("%d", get_stri(i, lifelen, n));
// printf("\n");
int get_stri(int si, int * lifelen, int n)
{
    int len = 0;
    int i = 0;

    len += lifelen[i];
    len += 1;

    while (si >= len) {

        i++;
        len += lifelen[i];
        len += 1; //填补的字符
    }

    return i;
}


void  build_sa(char *s, int *sa, int *x, int *y, int *c, int m)
{
    int i;
    int n = strlen(s);

    for (i = 0; i < m; ++i) { c[i] = 0; }

    for (i = 0; i < n; ++i) { c[x[i] = (unsigned char)s[i]]++; }

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
        if( x[sa[i]] != i ) {
            fprintf(stderr, "%s\n", str);
            break;
        }
        if ( sa[x[i]] != i ) {
            fprintf(stderr, "%s\n", str);
            break;
        }
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
