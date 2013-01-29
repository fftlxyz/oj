/*
 * 前缀表达式... 水题目，不过复习了一个...
 * poj 3295
 * memory: 352K
 * time: 0MS
 * code lenth: 2994B:
 * date: 2012-11-02 10:01:17
 */

#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main(int argc, const char *argv[])
{
    char str[1005] = {0};
    char eval[1005] = {0};
    int argu[1005] = {0};

    int etop = 0;
    int atop = 0;
    bool var[5];

    while( scanf("%s", str) == 1){

        if(str[0] == '0')
            break;

        int explen = strlen(str);

        bool isfalse = false;

        for(int i = 0; i < 32; ++i){

            etop = 0;
            atop = 0;

            var[0] = i & 0x0001;
            var[1] = i & 0x0002;
            var[2] = i & 0x0004;
            var[3] = i & 0x0008;
            var[4] = i & 0x0010;

            int j = 0;
            while(j < explen ){

                char ch = str[j++];

                eval[etop++] = ch;
                if( ch == 'K' || ch == 'A'
                       || ch == 'C' || ch == 'E' ){
                    argu[atop++] = 2;
                }
                else if( ch == 'N') {
                    argu[atop++] = 1;
                }
                else {
                    eval[etop - 1] =  var[ch -'p'] + '0';
                    //must be variable
                    --argu[atop - 1];

                    while( argu[atop - 1] == 0) {
                        atop--;
                        char x = eval[etop - 1];
                        char w = eval[etop - 2];
                        char k = eval[etop - 3];

                        char val;
                        if( w == 'N') {
                            val = !(x-'0') + '0';
                            etop -= 2;
                        } else {

                            switch(k) {
                                case 'K':
                                    val = (x - '0') && (w - '0');
                                    break;
                                case 'A':
                                    val = (x - '0') || (w - '0');
                                    break;
                                case 'C':
                                    val = 1;
                                    if( (w - '0') && !(x - '0'))
                                        val = 0;
                                    break;
                                case 'E':
                                    val =  (x == w);
                                    break;
                            }
                            val += '0';
                            etop -=3;
                        }

                        eval[etop++] = val;

                        if( atop == 0)
                            break;

                        --argu[atop - 1];
                    }
                }
            }

            if( eval[etop -1] == '0' ){
                isfalse = true;
                break;
            }
        }

        isfalse ? printf("not\n"): printf("tautology\n");

    }

    return 0;
}
