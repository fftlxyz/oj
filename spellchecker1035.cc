/* poj1035
 * memory:640K
 * time:110MS
 * complier:G++
 * code length: 2675B
 * date: 2012-11-19 22:50:03
 * 确实是挺水的, 1 A
 * 直接暴力
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dict[10005][20];
int lendct[10005];
char word[20];

int match[10005];

int main(int argc, const char *argv[])
{
    int  n = 0;

    while(scanf("%s", dict[n]) && dict[n][0] != '#')
        ++n;


    for (int i = 0; i < n; ++i)
        lendct[i] = strlen(dict[i]);

    while (scanf("%s",word) && word[0] != '#') {
        int lenwd = strlen(word);
        int mi = 0;

        bool ismatch = false;
        for (int i = 0; i < n; ++i) {

            ismatch = false;
            if (abs(lendct[i] - lenwd) > 1)
                continue;

            int diff = 0;
            if(lenwd == lendct[i]) {
                for ( int j = 0; j < lenwd; ++j) {
                    diff += !(word[j] == dict[i][j]);
                    if(diff > 1)
                        break;
                }

                if(diff == 0) {
                    ismatch = true;
                    break;
                }

                if ( diff == 1) {
                    match[mi++] = i;
                }
            }

            if (lenwd > lendct[i]) {

                int j = 0;
                int k = 0;
                while (j < lenwd && k < lendct[i]) {
                    if (word[j] == dict[i][k])
                        ++k, ++j;
                    else {
                        break;
                    }
                }

                if (k == lendct[i])
                    match[mi++] = i;
                else
                {
                    int cmp = strcmp(word + j + 1, dict[i] + k);
                    if (cmp == 0)
                        match[mi++] = i;
                }
            }

            if (lenwd < lendct[i]) {

                int j = 0;
                int k = 0;
                while (j < lendct[i]) {
                    if (word[k] == dict[i][j])
                        ++k, ++j;
                    else {
                        break;
                    }
                }

                if ( k == lenwd )
                    match[mi++] = i;
                else
                {
                    int cmp = strcmp(word + k, dict[i] + j+1);
                    if (cmp == 0)
                        match[mi++] = i;
                }
            }

        }

        if (ismatch)
            printf("%s is correct\n", word);
        else {
            printf("%s: ", word);
            for (int i = 0; i < mi; ++i ) {
                printf("%s ",dict[match[i]]);
            }
            printf("\n");
        }
    }

    return 0;
}
