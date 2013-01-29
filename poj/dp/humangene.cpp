/* poj 1080
 * memory: 760K 这个内存大小似乎是c++造成的
 * time: 0MS
 * code length: 1990B
 * date: 2012-10-25 11:25:43
 * */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 100;

int dp[MAXN+1][MAXN+1] ;

int score[][5] = {
    /*A  C  G  T  -*/
    /*A*/  {5,-1,-2,-1,-3},
    /*C*/  {-1,5,-3,-2,-4},
    /*G*/  {-2,-3,5,-2,-2},
    /*T*/  {-1,-2,-2,5,-1},
    /*-*/  {-3,-4,-2,-1,0}
};

int main(int argc, const char *argv[]){

    int subindex[255] = {0};

    subindex['A'] = 0;
    subindex['C'] = 1;
    subindex['G'] = 2;
    subindex['T'] = 3;
    subindex['-'] = 4;

    int N;

    cin >> N;

    while(N--) {

        // string a = "AGTGATG";
        // string b = "GTTAG";

        // a = "AGCTATT";
        // b = "AGCTTTAAA";

        // int alen = a.length();
        // int blen = b.length();

        string a,b;
        int alen,blen;

        cin >> alen >> a;
        cin >> blen >> b;

        // dp[i][j] = max{ dp[i-1][j-1] +  score( a[i], b[j]) , dp[i][j-1] + score( , dp[i-1][j] };

        dp[0][0] = 0;
        for(int i = 1 ; i <= alen ; ++i) {
            dp[i][0] = dp[i-1][0] + score[ subindex[ a[i-1] ] ][ subindex['-'] ];
        }

        // for(int i = 1 ; i <= alen ; ++i) {
        // cout << dp[i][0] << " ";
        // }
        // cout << endl;

        for(int j =1; j <= blen; ++j) {
            dp[0][j] = dp[0][j-1] + score[ subindex['-'] ][ subindex[ b[j-1] ]];
        }


        for(int i = 1; i <= alen; ++i) {
            for(int j = 1; j <= blen; ++j) {

                int max = dp[i-1][j-1] + score[ subindex[ a[i-1] ] ][ subindex[ b[j-1] ] ];
                int tmp1 = dp[i][j-1] + score[ subindex['-'] ][ subindex[ b[j-1] ]];
                int tmp2 = dp[i-1][j] + score[ subindex[ a[i-1] ] ][ subindex['-'] ];

                if( max < tmp1 ) max = tmp1;

                if( max < tmp2 ) max = tmp2;

                dp[i][j] = max;
            }
        }

        cout << dp[alen][blen] << endl;
    }
    return 0;
}
