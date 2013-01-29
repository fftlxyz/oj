/* poj 3176
 * memory: 1672K
 * time: 375MS
 * codelength: 872B
 * date: 2012-10-25 10:27:42
 */

#include <iostream>
using namespace std;

const int MAXN = 350;

int cow[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(int argc, const char *argv[])
{
    int n;

    cin >> n;

    for(int i =0; i < n; ++i) {
        for(int j =0 ; j <= i; ++j) {
            cin >> cow[i][j];
        }
    }

    // for(int i =0; i < n; ++i) {
        // for(int j =0 ; j <= i; ++j) {
            // cout << cow[i][j] << " ";
        // }
        // cout << endl;
    // }


    for(int i=0; i < n; ++i) {
        dp[n-1][i] = cow[n-1][i];
    }

    for(int i = n-2; i >=0; --i) {

        for(int j = 0; j <= i; ++j) {

            int max = dp[i+1][j];

            if( dp[i+1][j+1] > max)
                max = dp[i+1][j+1];

            dp[i][j] = max + cow[i][j];
        }

    }

    cout << dp[0][0] << endl;


    return 0;
}
