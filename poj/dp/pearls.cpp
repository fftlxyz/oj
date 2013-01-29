#include <iostream>
using namespace std;

/*
 *fly2best
 *poj 1260
 *memory: 716K
 *time: 0MS
 *code length: 1317B
 *date: 2012-10-25 10:03:08
 */

const int MAXC = 1000;

int main(int argc, const char *argv[])
{
    int a[MAXC] = {0};
    int p[MAXC] = {0};


    int sum[MAXC] = {0};
    int dp[MAXC] = {0};

    int N;

    cin >> N;

    while(N--) {

        int c ;
        cin >> c;

        for(int i =0; i < c; ++i)
            cin >> a[i] >> p[i];

        // c = 2;
        // a[0] = 100; a[1] = 100;
        // p[0] = 1; p[1] = 2;
        //
        // c = 3;
        // a[0] = a[1] = 1; a[2] = 100;
        // p[0] = 10; p[1] = 11; p[2] = 12;

        // dp[i] = min{ dp[j] + ( sum( a[j..i] ) + 10 ) * p[i] ) { 0 <= j < i}

        sum[0] = a[0];
        for(int i = 0; i < c; ++i) {
            sum[i] = sum[i-1] + a[i];
        }

        dp[0] = (a[0] + 10) * p[0];

        for(int i = 1; i < c; ++i) {

            int min =  (sum[i] + 10) * p[i];

            for(int j = 0; j < i ; ++j) {

                int tmp = dp[j] + ( sum[i] - sum[j] + 10) * p[i];
                if( min > tmp)
                    min = tmp;
            }

            dp[i] = min;
        }

        cout << dp[c-1] << endl;

        // for(int i =0; i < c; ++i) {
        // cout << dp[i] << " ";
        // }
        // cout << endl;
    }

    return 0;
}
