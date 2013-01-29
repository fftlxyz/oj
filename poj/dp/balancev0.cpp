#include <iostream>
#include <cstring>
using namespace std;

const int MAXC = 20;
const int MAXG = 20;
const int MAXV = MAXG * 25 * 15;

int C, G;
int dp[ MAXG+1 ][MAXC + 1][ 2*MAXV + 1];
int d[MAXC + 1];
int w[MAXG + 1];

int main(int argc, const char *argv[])
{
    d[1] = -2;
    d[2] = 3;

    w[1] = 3;
    w[2] = 4;
    w[3] = 5;
    w[4] = 8;

    C = 2;
    G = 4;

    // dp[i][j][v] the fisrt di, and wi, construct value v's num
    // dp[i][j][v] = sum ( dp[i][j-1][v], dp[i-1][j][v],  dp[i-1][j-1][v-wi*dj] )

    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < MAXC; ++i)
        dp[0][i][MAXV] = 1;

    for(int i = 0; i < MAXG; ++i)
        dp[i][0][MAXV] = 1;

    for(int i = 1; i <= C; ++i) {

        for( int j = 1; j <= G; ++j) {

            for(int k = 0; k < 2*MAXV+1 ; ++k) {

                dp[i][j][k] += dp[i-1][j][k];
                dp[i][j][k] += dp[i][j-1][k];

                int v = w[i] * d[j];
                //put the j weight at i postion
                if( ( k - v >= 0 ) && ( k -v <= 2*MAXV ) )
                    dp[i][j][k] +=  dp[i-1][j-1][ k-v ] ;
            }
        }
    }

    for(int i = 1; i <= C; ++i)
        for(int j = 1; j <= G; ++j)
            for(int k = 0; k < 2 * MAXV +1; ++k )
            {
                if( dp[i][j][k] != 0 )
                    cout << i << " " << j <<  " " << k - MAXV  << " " << dp[i][j][k] << endl;
            }


    cout << dp[C][G][MAXV] << endl;

    return 0;
}
