#include <stdio.h>

int n=859963392;
int count[3];
int factor[] = {2, 3, 5};

int main(int argc, const char *argv[])
{

    int i;

    for(i = 0; i < 3; ++i) {
        while (n % factor[i] == 0) {
            n /= factor[i];
            count[i]++;
        }
    }

    for(i = 0; i < 3; ++i) {
        printf("%d ", count[i]);
    }


    return 0;
}
