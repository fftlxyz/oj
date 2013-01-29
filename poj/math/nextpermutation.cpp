
/* poj 1833
 * memory: 168K
 * time: 469MS  ( cin cout TLE->  scanf printf TLE -> scanf printf C++ 470ms 编译器啊.....)
 * complier: C++
 * code length: 1297B
 * date: 2012-10-31 16:45:07
 *
 * 我觉得这个代码已经写的够简单的了。。。。
 * 咋会超时呢。。。。。
 */
#include <stdio.h>

bool next_permutation(int *p, int n);

int main(int argc, const char *argv[])
{

    int perm[1024];
    int n;
    int k;

    int ncase;
    // cin >> ncase;
    scanf("%d", &ncase);

    while(ncase--){

        // cin >> n >> k;
        scanf("%d", &n);
        scanf("%d", &k);
        for(int i = 0; i < n; ++i){
            // cin >> perm[i];
            scanf("%d", &perm[i]);
        }

        while(k--)
            next_permutation(perm,n);

        for(int i = 0; i < n-1; ++i){
            // cout << perm[i] << " ";
            printf("%d ", perm[i]);
        }
        // cout << perm[n-1] << endl;
        printf("%d\n", perm[n-1]);
    }
    return 0;
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

bool next_permutation(int *p, int n)
{
    bool isexist = false;
    int i = n-1;
    while(i) {
        if(p[i-1] < p[i])
            break;
        i--;
    }

    int j = n-1;
    if(i){
        isexist = true;
        while(p[j] < p[i-1]){
            j--;
        }
        swap(p[j], p[i-1]);
    }

    //cout << j << " " << i << endl;
    j = n -1;
    while(j > i)
    {
        swap(p[i], p[j]);
        --j;
        ++i;
    }

    return isexist;
}
