
/* poj 1125
 * memory: 696K
 * time: 0MS
 * complier: G++
 * code length: 1517B
 * date: 2012-11-03 14:59:51
 **/

/*
 * 就是floyed.....
 * */

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

const int MAX_N = 105;

int d[MAX_N][MAX_N];

int main(int argc, const char *argv[])
{
    int n;
    while( scanf("%d",&n)) {
        if( n == 0 )
            break;

        for (int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                d[i][j] = 1000;
            }
            d[i][i] = 0;
        }

        for(int i = 0; i < n; ++i) {
            int ncontract;
            scanf("%d", &ncontract);
            while(ncontract--){
                int to , cost;
                scanf("%d%d", &to, &cost);
                d[i][to-1] = cost;
            }
        }


        for (int k = 0; k < n; ++k){
            for (int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){

                    if( d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }


        int min = 1000;
        int mini = n;
        for(int i = 0; i < n; ++i){
            int max = -1;
            for(int j = 0; j < n; ++j){
                if( d[i][j] > max )
                    max = d[i][j];
            }

            if( min > max ){
                min = max;
                mini = i;
            }
        }

        if(mini == n )
            printf("disjoint\n");
        else
            printf("%d %d\n", mini+1, min);
    }
    return 0;
}
