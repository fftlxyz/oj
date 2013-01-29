/* poj 1936
 * memory: 500K
 * time: 16MS
 * complier: G++
 * code length: 483B
 * date: 2012-11-19 20:57:42
 *
 * 就判断一个串是否是另一个串的字串
 * o(n)
 * 嗯，不要把strlen 写到循环里。。。
 * 我看这道提蛮水的，但是ac率好像不高，就看了discuss...
 * 没准，我也写到循环上了。。。。
 */


#include <stdio.h>
#include <string.h>
const int N = 100010;
char stra[N];
char strb[N];

int main(int argc, const char *argv[])
{
    while( scanf("%s%s", stra, strb) == 2) {
        int alen = strlen(stra);
        int blen = strlen(strb);

        int i = 0;
        for ( int j = 0 ; j < blen && i < alen; ++j) {
            if (strb[j] == stra[i])
                i++;
        }

        i == alen ? printf("Yes\n") : printf("No\n");
    }
    return 0;
}
