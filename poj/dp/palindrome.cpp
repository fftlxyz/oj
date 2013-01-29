
/*
 * author:fly2best
 * poj:1159
 * memory:768K
 * time:782MS
 * date: 2012-10-25 16:19:23
 * */

#include <iostream>
#include <string>
using namespace std;

const int MAXN = 5000;

string str = "Ab3bd";
int n;
int dp[MAXN+1][2] = {0};

int main(int argc, const char *argv[])
{
    // n = str.length();

    cin >> n;
    cin >> str;

    // dp[i][j] stands for [i,j)上的需要插入的字符
    // for(int i =0; i < n; ++i)
        // dp[i][i+1] = 0;

    // for(int i =0; i <=n; ++i)
        // dp[i][i] = 0;

    for(int s = 2; s <= n; ++s) {
        for(int i =0; i + s < n+1; ++i) {

            int j = (i+s);
            int j1 = j%2-1; //

            if(j1<0)
                j1+=2;

            int min = MAXN;

            // i+1 < n && j-1 > 0 &&
            if( str[i] == str[j-1])
                min = dp[i+1][j1];
            else  {

                if( min > dp[i+1][j%2] + 1)
                    min = dp[i+1][j%2] + 1;

                if( min > dp[i][j1] + 1)
                    min = dp[i][j1] + 1;
            }

            dp[i][j%2] = min;
        }
    }

    cout << dp[0][n%2] << endl;

    // for(int s = 2; s <= n; ++s) {
        // cout << s << ":" << endl;
        // for(int i =0; i + s < n+1; ++i) {
            // cout << i << " " << i +s  << " " << dp[i][i+s] << " " << endl;
        // }
    // }


    return 0;
}
