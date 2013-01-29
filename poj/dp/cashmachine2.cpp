#include <iostream>
#include <cstring>
using namespace std;

const int CASHMAX = 100000;
const int NMAX = 10;

int dp[CASHMAX +1] = {0};

int cash = 735;
int N = 3;
int cashNum[NMAX] = {4,6,3};;
int cashValue[NMAX] = {125,5,350};

int main(int argc, const char *argv[])
{

    // dp[v] 表示容量为v时的最大value
    //
    //
    while( cin >> cash >> N) {

        int i =0;
        while( i < N ) {
            cin >> cashNum[i] >> cashValue[i];
            i++;
        }

        memset(dp, 0, sizeof(dp));

        for(int i = 0; i < N; ++i) {

            //convert to complete knapsack
            if(cashNum[i] * cashValue[i] >= cash) {

                for(int v = cashValue[i]; v <= cash; ++v) {

                    int tmp = dp[v - cashValue[i] ] + cashValue[i];

                    if( tmp > dp[v] )
                        dp[v] = tmp;
                }
                // for(int v = cash; v >= cashValue[i]; --v)
            }
            else {

                //convert to one-zero knapsack
                int k = 1;
                while( k < cashNum[i] ) {

                    for(int v = cash; v >= k * cashValue[i]; --v) {

                        int tmp = dp[v - k * cashValue[i] ] + k * cashValue[i];

                        if( tmp > dp[v] )
                            dp[v] = tmp ;

                    }

                    cashNum[i] -= k;
                    k *= 2;
                }

                if( cashNum[i] > 0 ) {

                    k = cashNum[i];

                    for(int v = cash; v >= k * cashValue[i]; --v) {

                        int tmp = dp[v - k * cashValue[i] ] + k * cashValue[i];

                        if( tmp > dp[v] )
                            dp[v] = tmp ;

                    }
                }

            }

        }

        int max = dp[cash];

        for(int i = 0; i < cash; ++i)
            if( max < dp[i] )
                max = dp[i];

        cout << max << endl;
    }
    return 0;
}

