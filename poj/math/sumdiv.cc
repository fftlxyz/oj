/*
 * poj 1845
 * memory: 356K
 * time: 0MS
 * complier: G++
 * code length: 2556B
 * date: 2012-11-07 12:03:58
 * 2次memory limit exceed, 2 次 wrong answer, finally accepted~~
 **/

#include <stdio.h>
#include <string.h>

const int N = 9901; //prime number
const int PRIME_N = 100;

struct
{
    int p;
    int exp;
} primeexp[PRIME_N];

int primenum = 0;

int modexp(int x, int y);
void factor(int n);
int extendedgcd(int a, int b, long long int &x, long long int &y);

int main(int argc, const char *argv[])
{
    int a, b;

    while( scanf("%d%d", &a, &b) == 2){

    // scanf("%d%d", &a, &b);
    if( a == 0 && b!= 0){
        printf("0\n");
        continue;
        // return 0;
    }

    if( a == 0 && b ==0 ) {
        printf("1\n");
        continue;
        // return 0;
    }
    if( a == 1 || b == 0) {
        printf("1\n");
        continue;
        // return 0;
    }

    factor(a);

    int sum = 1;
    for( int i = 0; i < primenum; ++i){

        int p = primeexp[i].p % N;  // 这是先前没有考虑到的
        int exp = primeexp[i].exp;

        int tmp;
        if( p == 0){
            tmp = 1;
        } else if(p == 1) {  //等比为1, 不能用求和公式
            tmp = exp * (b % N) + 1;
        } else {
            // printf("%d^%d\n", i, primeexp[i]);
            int px = modexp(p,exp );
            int pxb = modexp( px, b);
            int pxb1 = (pxb * p - 1) % N;

            long long int x, y;

            extendedgcd(p-1, N, x, y);
            x = x % N;
            if( x < 0 )
                x += N;
            pxb1 = pxb1 * x % N;
            tmp = pxb1;
        }
        sum = ( tmp * sum) % N;
    }

    printf("%d\n", sum);
    }

    return 0;
}

void factor(int n)
{
    primenum = 0;
    for(int i = 2; i *i <= n; ++i){

        if( n % i == 0 ){
            primeexp[primenum].p = i;
            primeexp[primenum].exp = 0;
            while( n % i == 0){
                n /= i;
                ++primeexp[primenum].exp;
            }
            ++primenum;
        }
    }

    if( n!= 1) {
        primeexp[primenum].p = n;
        primeexp[primenum].exp = 1;
        ++primenum;
    }
}

int extendedgcd(int a, int b, long long int &x, long long int &y)
{
    if ( b == 0){
        x = 1;
        y = 0;
        return a;
    } else {
        int d = extendedgcd( b, a % b, x, y);
        long long  int t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}


int modexp(int x, int y)
{
    if( y == 0)
        return 1;
    else {
        int z = modexp(x, y / 2);
        z = (z * z) % N;
        if(y % 2 != 0) {
            z = (z * (x % N)) % N;
        }
        return z;
    }
}
