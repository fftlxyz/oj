/* poj 2586
 * memroy: 248K
 * time: 32MS
 * complier: C++
 * code length: 563B
 * date: 2012-11-01 19:07:04
 * 确实是很巧妙的贪心策略
 */
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{

    double s,d;
    while( cin >> s >> d) {
        double max;

        if(s < d/4)
            max = 10*s - 2*d;
        else if( s < 2*d/3)
            max = 8*s - 4*d;
        else if( s < 3*d/2 )
            max = 6*s - 6*d;
        else if( s < 4*d)
            max = 3*s - 9*d;
        else
            max = -1;

        if( max > 0)
            cout << max << endl;
        else
            cout << "Deficit" << endl;
    }

    return 0;
}
