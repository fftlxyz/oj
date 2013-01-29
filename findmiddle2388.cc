/* poj 2388
 * memory: 416K
 * time: 16MS
 * complier: G++
 * code length: 1885B
 * date: 2012-12-06 21:41:58
 * 1 A, findk... O(n)
 */
#include <stdio.h>
#include <stdlib.h>

const int N = 10005;

int a[N] ; //= {9,3,2,3,3,10,-1,98,0};
struct Range
{
    int start;
    int end;
};

void swap(int &a, int &b);
int findk(int *p, int n, int k);
Range partion(int *p, int n);

int main(int argc, const char *argv[])
{
    // int a[] = {9,3,2,3,3,8,3};
    // int n = sizeof(a) / sizeof(int);
    int n, i, k;

    scanf("%d", &n);

    i = 0;
    while(i < n) {
        scanf("%d", &a[i++]);
    }

    k = n / 2;

    printf("%d\n", findk(a, n, k));

    // Range range = partion(a, n);

    // printf("%d %d\n", range.start, range.end);

    // for(int i = 0; i < n; ++i)
        // printf("%d ", a[i]);
    // printf("\n");

    return 0;
}


/*找第k大数*/
int findk(int *p, int n, int k)
{
    Range range = partion(p, n);

    if (k >= range.start && k < range.end )
        return p[k];

    if (k < range.start) {
        return findk(p,range.start, k);
    }

    if ( k >= range.end) {
        return findk(p + range.end, n - range.end, k - range.end);
    }
}

Range partion(int *p, int n)
{
    int key = p[n-1];
    int i = 0;
    int j = 0;
    int k = 0;

    // p[0,i) < key ; [i,j) = key ; [j,k) > key

    while( k < n ) {

        if(p[k] > key) {
            k++;
        } else if(p[k] < key) {

            swap(p[i], p[k]);
            if (i != j)
                swap(p[j], p[k]);
            i++, j++, k++;

        } else {
            swap(p[j], p[k]);
            j++, k++;
        }


        // printf("%d %d %d %d:", key, i, j, k);
        // for(int ki = 0; ki < k; ++ki)
            // printf("%d ", p[ki]);
        // printf("\n");

    }

    Range ret;
    ret.start = i;
    ret.end = j;

    return ret;
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}


