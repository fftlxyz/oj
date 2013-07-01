#include <stdio.h>
#include <string.h>
#include <assert.h>

//可重叠的至少出现k次最长字串
//
// #define __DEBUG__
// #define assert(TEST) if(!(TEST)) asm("int $3");

// 汗啊，后缀数组模板找出了一个bug, 以前的题目都怎么过的....
// 11394937	fly2test	3261	Accepted	4456K	125MS	C++	4587B	2013-03-26 10:06:45
// 11394704	fly2best	3261	Accepted	4664K	141MS	G++	4275B	2013-03-26 08:32:22
// 11392104	fly2best	3261	Wrong Answer			G++	3134B	2013-03-25 17:26:41


const int MAXN = 20100;
const int MAXM = 1000100;

int a[MAXN];
int sa[MAXN];
int rank[MAXN];
int t2[MAXN];
int c[MAXM];

int height[MAXN];

void  build_sa(int *s, int n, int *sa, int *x, int *y, int *c, int m);
void get_height(int *str, int n,int *sa, int *height, int *rank);
bool is_len_p(int p, int k, int *sa, int *height, int n);

void print_int_array(int *p, int n);
void print_sa(int *s, int n, int *sa);

int main(int argc, const char *argv[])
{
    int n, k;
    scanf("%d%d", &n, &k);

    int i = 0;
    while (i < n) {
        scanf("%d", a + i);
        ++i;
    }

    build_sa(a, n, sa, rank, t2, c, MAXM);
    get_height(a, n, sa, height, rank);

    int l = 1;
    int r = n + 1;

    int maxlen = 0;
    while (l < r) {
        int m = l + (r - l) / 2;
        bool is_m_ok = is_len_p(m, k, sa, height, n);

        // printf("%d %d\n", m, is_m_ok);

        if (is_m_ok) {
            l = m + 1;
            maxlen = m;
        } else {
            r = m;
        }
    }

    printf("%d\n", maxlen);


    return 0;
}

bool is_len_p(int p, int k, int *sa, int *height, int n)
{

    bool is_p_ok = false;

    int s;
    int i;
    for (s = 0, i = 1; i < n; ++i) {

        if (height[i] < p) {
            int t = i;

            if (t - s >= k) {
                is_p_ok = true;
                break;
            }

            s = t;
        }
    }

    if (n - s >=k )
        is_p_ok = true;

    return is_p_ok;
}

void  build_sa(int *s, int n, int *sa, int *x, int *y, int *c, int m)
{
    int i;

    for (i = 0; i < m; ++i) { c[i] = 0; }

    for (i = 0; i < n; ++i) { c[x[i] = s[i]]++; }

    for (i = 1; i < m; ++i) { c[i] += c[i -1]; }

    for (i = n -1; i >= 0; --i) {
        sa[--c[x[i]]] = i;  //sa 是一个数组, sa[i] = j;  表示序为i是后缀j
    }

#ifdef __DEBUG__
    print_sa(s, n, sa);
    printf("x: ");
    print_int_array(x, n);
#endif

    for (int k = 1; k < n; k <<= 1) {   //如果k = n, 不应该继续循环, if k =n, 在循环里应该已经终止break了, bugfixed
        int p = 0;

        for (i = n - k; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) {
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        }

#ifdef __DEBUG__
        printf("y: ");
        print_int_array(y, n);
#endif

        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[y[i]]]++;
        for(i = 0; i < m; i++) c[i] += c[i - 1];
        for(i = n -1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];

#ifdef __DEBUG__
        print_sa(s, n, sa);
#endif

        int *t = x;
        x = y;
        y = t;

        memset(x, 0, sizeof(int) * MAXN);
        p = 1;
        x[sa[0]] = 0;
        for (i = 1; i < n; i++) {
            if ( y[sa[i - 1]] == y[sa[i]]
                    && (sa[i - 1] + k < n) && (sa[i] + k < n)  //bugfixed
                    && y[sa[i - 1] + k] == y[sa[i] + k]) {
                x[sa[i]] = p - 1;
            } else {
                x[sa[i]] = p++;
            }
        }
#ifdef __DEBUG__
        printf("x: ");
        print_int_array(x, n);

        printf("p:%d, k:%d\n", p, k);
#endif
        if (p >= n)
            break;
        m = p;
    }


    // for (int i = 0; i <n; ++i) {
        // for(int j = sa[i]; j < n; ++j) {
            // printf("%d ", a[j]);
        // }
        // printf("\n");
    // }

    //这个assert帮了我多少忙~~
    for (i = 0; i < n; ++i) {
        assert( x[sa[i]] == i );
        assert( sa[x[i]] == i );
    }
}

void get_height(int *str, int n,int *sa, int *height, int *rank)
{
    int i, j, k = 0;

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

void print_sa(int *s, int n, int *sa)
{
    printf("sa:");
    int i, j;
    for (i = 0; i < n; ++i) {
        printf("%d ", sa[i]);
    }
    printf("\n");

    for (i = 0; i < n; ++i) {
        for (j = sa[i]; j < n; ++j) {
            printf("%d ", s[j]);
        }
        printf("\n");
    }
}

void print_int_array(int *p, int n)
{
    int i = 0;
    for (i =0; i < n; ++i) {
        printf("%d ", p[i]);
    }
    printf("\n");
}

