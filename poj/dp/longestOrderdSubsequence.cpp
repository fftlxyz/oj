
/*
 * poj 2533 longest ordered sequence
 * memory: 724K
 * time: 0MS
 * code length: 633B
 * date: 2012-10-24 10:09:42
 * 话说这题目，还有o(n) 的时间复杂度。。。。
 */

#include <iostream>
using namespace std;

const int MAXN = 1000;

int a[MAXN] = {1,7,3,5,9,4,8};
int dp[MAXN] = {0};

int main(int argc, const char *argv[])
{

    int n = 7;

    cin >> n;

    int i = 0;

    while(i < n)
        cin >> a[i++];

    for(int i = 0; i < n; ++i )
    {
        dp[i] = 1;

        for(int j = 0; j < i; ++j) {

            if( a[i] > a[j] && dp[i] < dp[j] + 1 )
                dp[i] = dp[j] +1;
        }
    }

    int max = dp[0];

    //第一次没考虑到,汗...
    for(int i = 1; i < n; ++i)
        if( dp[i] > max)
            max = dp[i];
    cout << max << endl;

    return 0;
}
