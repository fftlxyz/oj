#include <iostream>
#include <cstring>
using namespace std;

const int MAXC = 20;
const int MAXG = 20;
const int MAXV = MAXG * 25 * 15;

int C, G;
int dp[ MAXG+1 ][ 2*MAXV + 1];
int d[MAXC + 1];
int w[MAXG + 1];

int main(int argc, const char *argv[])
{
    d[1] = -2; d[2] = 3;

    w[1] = 3; w[2] = 4; w[3] = 5; w[4] = 8;

    C = 2; G = 4;

    cin >> C >> G;

    int i =1;
    while(i <= C)
        cin >> d[i++];

    i = 1;
    while(i <= G)
        cin >> w[i++];

    memset(dp, 0, sizeof(dp));

    dp[0][MAXV] = 1;

    for( int i = 1; i <= G; ++i) {

        for(int j = 0; j < 2*MAXV+1 ; ++j) {

            for(int k = 1; k <= C; ++k ) {

                int v = w[i] * d[k];
                if( j -v >=0 && j-v <= 2*MAXV +1)
                    dp[i][j] += dp[i-1][j-v];

            }
        }
    }

    cout << dp[G][MAXV] << endl;

    // for(int i = 0; i<= G; ++i)
        // for(int j =0; j < 2 * MAXV +1; ++j) {

            // if(dp[i][j] != 0 )
                // cout << i << " " << j << " " << j - MAXV << " " << dp[i][j] << endl;
        // }

    return 0;
}
