
#include <iostream>
#include <algorithm>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

const int MAX_N = 50000001;
const int N = 9901; //prime number

bool isprime[MAX_N];
#define random(x) (rand()%x)
void eratosthenes(int n);

int main()
{
    long n = 6555555;

    for(int i = 2; i <=n ; ++i){

        bool isfirst = false;
        while( n % i == 0) {
            n /= i;
            if( !isfirst) {
                isfirst = true;
                cout << i << endl;
            }
        }
    }

    return 0;
}



void eratosthenes(int n)
{
    memset(isprime + 2, 1, sizeof(bool) * n);

    for(int i = 2; i*2 <= n; ++i){
        isprime[ 2 * i] = false;
    }

    int p = 3;

    while(p * p <= n){

        int t = p * p;
        int s = 2*p;

        while( t <= n){
            isprime[t] = 0;
            //p is odd, and all the even has already be deleted
            t += s;
        }

        p += 1;
        while( isprime[p] == 0)
            ++p;
    }
}
