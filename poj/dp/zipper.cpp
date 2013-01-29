
/**
 * poj 2192
 * memory: 732k
 * speed: 188Ms
 * 这个内存和速度。。。。
 * Tue Oct 23 18:58:18 CST 2012
 */

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    string a = "cat";
    string b = "tree";

    string c = "tcraete";

    int N ;
    int n =1;

    cin >> N;

    while( n <= N ) {

        cin >> a >> b >> c;

        // cout << a  << " " << b << " "<< c <<endl;

        // dp[i][j] 表示 a的前i字符和b的前j个字符，是否能构成 c的前i+j个字符

        // dp[i][j] = or( ((c[i+j-1] == a[i-1]) &&  dp[i-1][j] )  ||  ((c[i+j-1]) == b[j-1]) && dp[i][j-1]   )

        bool dp[201][201] = {0};

        dp[0][0] = true;

        int alen = a.length();
        int blen = b.length();

        for(int i = 0; i < alen +1 ; ++i )
            for(int j = 0; j < blen +1 ; ++j)
            {
                if(i > 0)
                    dp[i][j] = dp[i][j] || ( ( c[ i+j -1  ] == a[i-1] ) && dp[i-1][j] );

                if(j > 0)
                    dp[i][j] =  dp[i][j] || ( ( c[ i+j -1 ] == b[j-1] )&& dp[i][j-1] );
            }

        cout << "Data set " << n++ << ": ";
        if( dp[alen][blen] )
            cout << "yes" << endl;
        else
            cout << "no" << endl;

        // for(int i = 0; i < alen + 1  ; ++i )
            // for(int j = 0; j < blen + 1 ; ++j) {
                // if(dp[i][j])
                    // cout << i << " " << j << endl;
            // }

    }

    return 0;
}
