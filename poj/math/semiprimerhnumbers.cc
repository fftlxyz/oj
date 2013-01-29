/* poj 3292
 * memroy: 1820K
 * time: 32MS
 * complier: G++
 * codelength: 1335B
 * date: 2012-11-08 07:54:54
 * 1A
 * 筛选法，复习了.....
 */
#include <stdio.h>
#include <math.h>
#include <string.h>

const int MAXN= (1000001-1)/4;

#define hn(i) ( 4*i+1)

//the ith h number is prime or not
bool isprime[MAXN+5];
bool is2prime[MAXN+5];
int cnt[MAXN+5];

void getprime();
void get2prime();

int main(int argc, const char *argv[])
{
    getprime();
    get2prime();

    cnt[0] = 0;
    for(int i = 1; i <= MAXN; ++i) {
        if( is2prime[i] ){
            cnt[i] = cnt[i-1] + 1;
        } else {
            cnt[i] = cnt[i-1];
        }
    }

    int hnum;
    int hi;

    while( scanf("%d", &hnum) != EOF ){

        if(hnum == 0)
            break;
        hi = (hnum - 1)/4;
        printf("%d %d\n", hnum, cnt[hi]);
    }
    return 0;
}


void getprime()
{
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = 0;
    for( int i = 1; i <= MAXN; ++i) {
        if( isprime[i]){
            for(int j = i; 4ll*i*j+i+j <= MAXN; ++j){
                isprime[4*i*j+i+j] = 0;
            }
        }
    }
}

void get2prime()
{
    for(int i = 1; i <= MAXN; ++i){
        is2prime[i] = !isprime[i];
    }

    for(int i = 0; i <= MAXN; ++i) {
        if( is2prime[i]) {
            for(int j = 1; 4ll*i*j+i+j <= MAXN; ++j){
                is2prime[4*i*j+i+j] = 0;
            }
        }
    }

}
