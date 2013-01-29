#include <stdio.h>
#include <iostream>
using namespace std;

int extendedgcd(int a, int b, int &x, int &y);

int main(int argc, const char *argv[])
{
    int a = 108;
    int b = 9901;
    int x, y;

    extendedgcd( a, b, x, y);

    x = x % b;
    if( x < 0)
        x += b;

    printf("%d\n", x);
    printf("%d\n", a*x % b);

    return 0;
}

int extendedgcd(int a, int b, int &x, int &y)
{
    if ( b == 0){
        x = 1;
        y = 0;
        return a;
    } else {
        int d = extendedgcd( b, a % b, x, y);
        int t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}
