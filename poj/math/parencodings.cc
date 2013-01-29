/* poj 1068
 * memory: 144K
 * time: 0MS
 * code length: 838B
 * date: 2012-11-02 08:19:41
 */

#include <stdio.h>
#include <stack>
using namespace std;

int main(int argc, const char *argv[])
{
    int ncase;
    scanf("%d", &ncase);

    while( ncase-- ){
        int np;
        scanf("%d", &np);

        stack<int> lpp; //未匹配左括号位置栈

        int numparen = 0;
        int lastp = 0;
        while(np--) {
            int p;
            scanf("%d", &p);

            int leftincnum = p - lastp;
            int ppos = numparen + leftincnum + 1;
            numparen = ppos;
            lastp = p;

            // printf("%d ", ppos);
            for(int i= ppos - leftincnum; i < ppos; ++i)
                lpp.push(i);

            int leftpos = lpp.top();
            lpp.pop();

            printf("%d ", (ppos - leftpos + 1)/2 );
        }
        printf("\n");

    }

    return 0;
}
