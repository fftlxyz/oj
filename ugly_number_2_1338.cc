
/* poj:1338
 * Accepted
 * 392K
 * 0MS
 * G++
 * 765B
 * 2013-02-21 08:33:55
 * 递推。。。递推。。。。 还是要多联系哈
 */

#include <stdio.h>

int ugly_numbers[1550] = {1,};

int at[3] = {0};
int factor[3] = {2, 3, 5};

int main(int argc, const char *argv[])
{
    int i = 1;
    int j = 0;
    int fi;

    for(i=1; i < 1550; ++i){

        fi = 0;
        for(j= 1; j < 3; ++j){

            if(factor[j] * ugly_numbers[at[j]] < factor[fi] * ugly_numbers[at[fi]]) {
                fi = j;
            }
        }

        ugly_numbers[i] = factor[fi] * ugly_numbers[at[fi]];

        for(j=0; j < 3; ++j) {

            if(ugly_numbers[i] == factor[j] * ugly_numbers[at[j]]) {

                ++at[j];
            }
        }

    }

    while( scanf("%d", &i) && i != 0 ) {
        printf("%d\n", ugly_numbers[i-1]);
    }

    return 0;
}
