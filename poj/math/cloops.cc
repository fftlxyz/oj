
/* poj 2115
 * memory: 388K
 * time: 0MS
 * complier: G++
 * code length: 1187B
 * date: 2012-11-05 09:30:48
 */

/*
 * c loop after analise, it' a egcd problem
 * */

#include <cstdio>
#include <iostream>
using namespace std;

struct EGcd
{
    long long int x;
    long long int y;
    long long int d;
};

EGcd extendedgcd(long long int a,long long int b);

long long n;

int main(int argc, const char *argv[])
{
    unsigned int a, b, c, k;

    while( scanf("%u%u%u%u", &a, &b, &c, &k) == 4) {

        if( a== 0 && b == 0 && c == 0 && k == 0)
            break;

        unsigned int r = b - a;
        n = 1LL << k;

        EGcd egcd = extendedgcd(c, n);

        long long d = egcd.d;
        long long x = egcd.x;

        if( r % d == 0){
            long long e = (r/ d * x ) % n + n;
            // cout << n << " " << r << " " << d << " " << x << endl;
            // cout << r/d * x << endl;
            // cout << r/d *x % n << endl;
            // cout << (r/d *x +n ) % n << endl;
            // cout << r/d *x % n + n << endl;
            printf("%lld\n", e);
            long long min = e % ( n / d);
            printf("%lld\n", min);

        } else {
            printf("FOREVER\n");
        }
    }

    return 0;
}

EGcd extendedgcd(long long int a,long long int b)
{
    EGcd ret;

    if ( b == 0) {
        ret.x = 1;
        ret.y = 0;
        ret.d = a;
    }
    else {
        EGcd egcd = extendedgcd(b, a % b);
        ret.x = egcd.y;
        ret.y = (egcd.x - a / b * egcd.y);
        ret.d = egcd.d;
    }
    return ret;
}
