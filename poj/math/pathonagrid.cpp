/*
 * memory: 696K
 * time: 32MS
 * code length: 533B
 * date: 2012-10-26 08:58:56
 * */

#include <iostream>
using namespace std;

/*
 * 这个题目就是组合
 * 本来是没什么好做的，但是有一个有意思的地方
 */

int main(int argc, const char *argv[])
{
    long long m,n, s;

    while (cin >> m >> n ) {

        if(m == 0 && n ==0 )
            break;

        if( m > n) {
            long long tmp = n;
            n = m;
            m = tmp;
        }

        // C(m+n,m)
        // trick is s is alway an interger, will never be frction
        // because s is C(n+i,i) which is alway a integer
        // we know at last s is able to store in an unsiged int
        // but how to ensure int the process s can be store in long long
        // easy~
        // 2^32 * 2^32 = 2^64
        s = 1;
        for(int i = 1; i <= m; ++i) {
            s = s*(i+n)/i;
        }

        cout  << s << endl;
    }


    return 0;
}

