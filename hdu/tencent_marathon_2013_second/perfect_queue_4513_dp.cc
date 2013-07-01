
#include <stdio.h>
#include <string.h>
#include <algorithm>
using std::max;
using std::min;

const int N = 100100;

unsigned char a[N];
unsigned char b[N << 1];

int lis[N];
int p[N << 1];
int n;

void lis_str();
void manacher(unsigned char * str, int n);

int main(int argc, const char *argv[])
{
    int casenum;
    int i;

    scanf("%d", &casenum);

    while (casenum--) {
        scanf("%d", &n);

        for (i = 0; i < n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            *(a + i) = (unsigned char)tmp;
        }

        lis_str();

        b[0] = '$';
        for (i = 0; i < n; ++i) {
            b[2*i + 1] = '#';
            b[2*i + 2] = a[i];
        }
        b[2*i + 1] = '#';
        b[2*i + 2] = '\0';

        manacher(b, 2*n + 2);

        int k;
        int maxl = 1;

        for (i = 1; i < 2*n + 2; ++i) {
            k = i / 2 -1;

            if (lis[k] * 2 >= p[i] - 1) {
                if (p[i] - 1 > maxl)
                    maxl = p[i] - 1;
            }
        }

        printf("%d\n", maxl);

    }

    return 0;
}

//最长上升子串
//lis, 记录到此结束的最长上升子串的长度
void lis_str()
{
    lis[0] = 1;
    for (int i = 1; i < n; ++i) {

        lis[i] = 1;
        if (a[i] >= a[i - 1]) {
            lis[i] += lis[i - 1];
        }
    }
}

void manacher(unsigned char * str, int n)
{
    int id;
    int i;
    int mx = 0;

    for (i = 1; i <= n; ++i) {
        p[i] = 1;
        if (mx > i) {
            p[i] = min(p[2*id -i], mx -i);
        }

        while (str[i + p[i]] == str[i - p[i]])
            p[i]++;

        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }
}
