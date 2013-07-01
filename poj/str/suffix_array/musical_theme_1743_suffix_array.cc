#include <stdio.h>
#include <string.h>
#include <assert.h>

//不可重叠的至少出现2次, 长度大于5最长字串
//
// #define __DEBUG__
// #define assert(TEST) if(!(TEST)) asm("int $3");


const int MAXN = 20100;
const int MAXM = 200;

int a[MAXN];
int sa[MAXN];
int rank[MAXN];
int t2[MAXN];
int c[MAXM];

int b[MAXN];

int height[MAXN];

void  build_sa(int *s, int n, int *sa, int *x, int *y, int *c, int m);
void get_height(int *str, int n,int *sa, int *height, int *rank);
bool is_len_p(int p, int k, int *sa, int *height, int n);

void print_int_array(int *p, int n);
void print_sa(int *s, int n, int *sa);

int main(int argc, const char *argv[])
{
    int n;

    while (scanf("%d", &n) != EOF && n != 0) {

        int i = 0;
        while (i < n) {
            scanf("%d", a + i);
            ++i;
        }

        for (int i = 0;i < n -1; ++i) {
            b[i] = a[i + 1] - a[i] + 100;
        }

        n--;

        build_sa(b, n, sa, rank, t2, c, MAXM);
        get_height(b, n, sa, height, rank);

        int l = 4;
        int r = (n + 1) / 2;

        int maxlen = 0;
        int k = 2;

        if(!is_len_p(4, k, sa, height, n) || n == 8) {
            printf("0\n");
            continue;
        }


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

        printf("%d\n", maxlen + 1);
    }

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

                int minsai = 1000000;
                int maxsai = -1000000;

                for (int j = s; j < t; ++j) {
                    if (sa[j] < minsai)
                        minsai = sa[j];
                    if (sa[j] > maxsai)
                        maxsai = sa[j];
                }

                if (maxsai - minsai >= p) {
                    is_p_ok = true;
                    break;
                }
            }

            s = t;
        }
    }

    if (n - s >=k ) {
        int minsai = 1000000;
        int maxsai = -1000000;
        for (int j = s; j < n; ++j) {
            if (sa[j] < minsai)
                minsai = sa[j];
            if (sa[j] > maxsai)
                maxsai = sa[j];
        }

        if (maxsai - minsai >= p) {
            is_p_ok = true;
        }

    }

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
    if (n != 1)  {
        for (i = 0; i < n; ++i) {
            assert( x[sa[i]] == i );
            assert( sa[x[i]] == i );
        }
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

