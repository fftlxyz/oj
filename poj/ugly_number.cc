
#include <stdio.h>
#include <limits.h>

int urly_numbers[1550] = {1,};

int at[3] = {0};
int factor[3] = {2, 3, 5};

int main(int argc, const char *argv[])
{
    int i = 1;
    int j = 0;
    int k = 0;
    int next = INT_MAX;

    for(i=1; i < 1550; ++i){

        next = INT_MAX;

        for(j= 0; j < 3; ++j){

            for( k = at[j]; k < i; ++k) {

                if(urly_numbers[k]* factor[j] > urly_numbers[i-1]) {

                    at[j] = k;

                    if(urly_numbers[k]* factor[j] < next)
                        next = urly_numbers[k]* factor[j];

                    break;
                }
            }
        }

        urly_numbers[i] = next;
    }

    for(i=0; i < 1550; ++i){
        printf("%d ", urly_numbers[i]);
    }

    return 0;
}
