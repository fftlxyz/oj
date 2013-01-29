/*
 * poj 2253
 * memory: 760K
 * time:0MS
 * code length:2056B
 * date: 2012-10-30 20:35:43
 * */

/* 这题目的数据量太弱了.....
 * 水题啊。。。
 * 老子调了两个小时*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

struct Vertex
{
    int x;
    int y;
    bool inS;
    double d;
};

const int MAXN = 200;


int main(int argc, const char *argv[])
{
    Vertex verts[MAXN];

    int ncase = 1;

    while ( 1 ) {

        int numOfStone;

        cin >> numOfStone;

        if(numOfStone == 0)
            break;

        for(int i = 0; i < numOfStone; ++i){
            cin >> verts[i].x >> verts[i].y;
            verts[i].d = 2000;
            verts[i].inS = false;
        }
        verts[0].d = 0;

        double min = 0;
        int mini = 0;

        for(int i = 0; i < numOfStone; ++i) {

            min = 2000;
            mini = -1;
            for(int j =0; j < numOfStone; ++j) {

                if( !verts[j].inS && min > verts[j].d ) {
                    min = verts[j].d;
                    mini = j;
                }
            }

            // cout <<  "i " << i << " " << mini << " " <<  min << endl;
            verts[mini].inS = true;

            for(int j = 0; j < numOfStone; ++j) {

                if(!verts[j].inS) {

                    //relax
                    int x1 = verts[mini].x;
                    int y1 = verts[mini].y;

                    int x2 = verts[j].x;
                    int y2 = verts[j].y;

                    double d = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)*1.0 );

                    // cout << "j " << j << " " << d << endl;

                    if( d < min)
                        d = min;

                    if( d < verts[j].d   ) {
                        // cout << "update " << j << " " << verts[j].d << endl;
                        verts[j].d = d;
                    }
                }
            }
        }
        cout << "Scenario #" << ncase++ << endl;
        cout.setf(ios::fixed);
        cout.precision(3);
        cout << "Frog Distance = " << verts[1].d << endl << endl;
    }
    return 0;
}
