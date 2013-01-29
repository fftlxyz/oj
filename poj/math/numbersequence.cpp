/* poj 1019
 * memory: 1096K
 * time: 0MSG
 * code length: 1831B
 * date: 2012-10-29 19:54:52
 * */
#include <iostream>
using namespace std;

const int N = 31500; //这个数是我通过程序测出来的....

int f[N];
long long sum[N];
int orderbits[6] = {0,9,180,2700,36000,450000};
int orderstart[6] = {0,1,10,100,1000,10000};

int main(int argc, const char *argv[])
{

    for( int i = 1; i < N; ++i) {

        if( i / 10 == 0)
            f[i] = f[i-1] + 1;
        else if(i / 100 == 0)
            f[i] = f[i-1] + 2;
        else if(i/1000 == 0)
            f[i] = f[i-1] + 3;
        else if( i/ 10000 == 0)
            f[i] = f[i-1] + 4;
        else if( i/ 100000 == 0)
            f[i] = f[i-1] + 5;
    }

    for(int i = 1 ; i < N; ++i) {
        sum[i] = f[i] + sum[i-1];
    }

    int index = 82;

    int numbercase ;

    cin >> numbercase;


    while(numbercase--){
        cin >> index;
        int n1left ;

        // find 在某个阶乘的第几位
        for( int i = 1; i < N; ++i) {
            if( sum[i] >= index ) {
                n1left = index - sum[i-1];
                // cout << i << " " << sum[i-1] << " " << n1left << endl;
                break;
            }
        }

        int sumorderbits = 0;
        int norder = 1;
        int n2left ;

        //找出是哪个数量级的
        //ie, 找出这个index在的那个数是几位的
        for(int i = 1; i < 6; ++i) {
            sumorderbits  += orderbits[i];

            if( sumorderbits >= n1left){
                norder = i;
                n2left =  n1left - sumorderbits  + orderbits[i];
                break;
            }
        }

        // cout << norder << " " << n2left << endl;

        //算出这个数，并且是第几位
        int number = (n2left - 1) /norder + orderstart[norder];
        int ibit = ((n2left -1) % norder) +1;
        // cout << number << "  " << ibit << endl;

        int ibitreverse = norder - ibit;

        while( ibitreverse-- ) {
            number /= 10;
        }

        //输出...
        cout <<  number % 10 << endl;

    }

    return 0;
}
