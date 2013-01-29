#include <iostream>
#include <cstring>
using namespace std;

const int NMAX = 10;
const int CASHMAX = 100000;

int main(int argc, const char *argv[])
{
    int cash = 735;
    int cashKinds = 0;
    int cashNum[NMAX] = {4,6,3};
    int cashValue[NMAX] = {125,5,350};


    int dp[CASHMAX+1][NMAX] = {0};
    int isCash[CASHMAX+1] = {0};

    //dp[i][j] 表示面值为i的，需要的第j中cash的数目
    //

    while( cin >> cash >> cashKinds ) {

        int index= 0;

        while( index < cashKinds   ) {

            cin >> cashNum[index ] >> cashValue[index ];
            ++index;
        }

        // cout << cash << " " << cashKinds << " ";

        // for(int i = 0; i < cashKinds; ++i )
            // cout << cashNum[i] << " " << cashValue[i] << " ";
        // cout << endl;

        memset(dp,0, sizeof(dp) );
        memset( isCash,0, sizeof( isCash) );
        isCash[0] = true;


        //dp[i][j]表示，cash为i时，第j种钱币的，使用量
        //dp[i][j] = dp[ i - cashValue[j] ] + 1;
        //isCash[i]表示，cash i 是否可行
        for( int i = 1; i <= cash; ++i ) {

            for(int j = 0; j < cashKinds; ++j) {

                int rcash = i - cashValue[j];

                if( ( rcash >= 0 ) && isCash[rcash] &&  dp[rcash][j] < cashNum[j] ) {

                    for(int  k = 0; k < cashKinds; ++k)
                        dp[i][k] = dp[rcash][k];

                    //这是唯一的变化
                    dp[i][j] += 1;
                    isCash[i] = true;

                    break;
                }

            }

        }


        int okCash = cash;
        while( okCash >= 0)
        {
            if( isCash[okCash] )
            {
                // cout << cash << " " << okCash << endl;
                cout << okCash << endl;
                break;
            }

            --okCash;
        }

        // for(int i = 0; i <= cash; ++i) {
        // if( isCash[i] ) {
        // cout << i << endl;

        // int sum =0;
        // for(int j =0 ; j < cashKinds; ++j ) {

        // if( dp[i][j] > cashNum[j] ) {
        // cout << i << " " << j << ": error" << endl;
        // break;
        // }

        // sum += dp[i][j] * cashValue[j];
        // }

        // if(i != sum )
        // cout << i << ": error" << endl;

        // }
        // }
    }

    return 0;
}
