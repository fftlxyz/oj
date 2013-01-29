#include <iostream>
using namespace std;

//我认为这个题意思不清晰
//使剩下的队列满足a1 < a2 < a3 ... < a(i ) <=> a(i+1) > a(i+2) > .. a(n-1) > a(n)
// poj 1836
// memory:  736K
// Time: 266MS
// code length: 1824B
// date: 2012-10-24 15:07:28

// int n = 8;
// double a[1000] = {1.86,1.86,1.30621,2,1.4,1,1.97,2.2};

int n = 8;
double a[1000] = {3,4,5,1,2, 5, 4, 3};

void lis(int *dp);
void lds(int *dp);

int main(int argc, const char *argv[])
{
    cin >> n;

    int i = 0;

    while(i < n)
        cin >> a[i++];

    int dplis[1000] = {0};
    int dplds[1000] = {0};

    lis(dplis);
    lds(dplds);

    int maxlis[1000] = {0};
    int maxlds[1000] = {0};

    maxlis[0] = 1;

    for(int i = 1; i < n; ++i) {

        maxlis[i] = dplis[i];

        if(maxlis[i] < maxlis[i-1])
            maxlis[i] = maxlis[i-1];
    }


    maxlds[n-1] = 1;
    for(int i = n -2; i > -1; --i) {

        maxlds[i] = dplds[i];

        if(maxlds[i] < maxlds[i+1])
            maxlds[i] = maxlds[i+1];
    }

    int max = 2;

    for(int i = -1; i < n; ++i) {

        int ret1 =0;
        int ret2 =0;

        if(i > -1)
            ret1 = maxlis[i];

        if(i + 1 < n)
            ret2 = maxlds[i+1];

        if(max < ret1 + ret2)
            max = ret1 + ret2;
    }

    cout << n - max << endl;

    return 0;
}

//a[0,nlen-1] 上的最长上升子序列
void lis(int *dp)
{
    int nlen = n;

    for(int i = 0; i < nlen; ++i) {
        dp[i] = 1;

        for(int j = 0; j < i; ++j) {
            if( a[i] > a[j] && dp[i] < dp[j] + 1 )
                dp[i] = dp[j] +1;
        }
    }
}

//a[0,n-1]
void lds(int *dp)
{
    int s = 0;

    for(int i = n-1; i > s-1; --i)
    {
        dp[i] = 1;

        for(int j = i+1; j < n; ++j) {

            if( a[i] > a[j] && dp[i] < dp[j] +1 )
                dp[i] = dp[j] +1;
        }
    }
}

