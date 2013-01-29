/*
 * poj 1328
 * memory: 776K
 * time: 110MS
 * code length: 2168B
 * date: 2012-10-26 22:22:56
 * */
//转化为区间选点问题
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct Segment
{
    double start;
    double end;
    bool covered;
};

bool mycompare(const Segment & left, const Segment & right);

int main(int argc, const char *argv[])
{
    int casenum = 0;
    int n = 1;
    int d = 2;
    // int x[] = {0,-3,2};
    // int y[] = {2,1,1};

    while( cin >> n >> d)
    {
        if(n == 0 && d==0)
            break;

        vector<Segment> segVector;
        Segment segment;
        int x, y;

        bool isOk = true;

        for(int i = 0; i < n; ++i) {
            cin >> x >> y;

            if( y > d)
                isOk = false;

            if( y == d) {
                segment.start = x;
                segment.end = x;
            }else {
                double b = sqrt( d*d - y*y);
                segment.start =  x - b;
                segment.end = x + b;
            }
            segment.covered = false;
            segVector.push_back(segment);
        }

        if(!isOk) {
            cout << "Case " << ++casenum << ": " << -1 << endl;
            continue;
        }

        sort(segVector.begin(), segVector.end(), mycompare);

        int count = 0;

        for(int i =0 ; i < n; ++i) {
            if( !segVector[i].covered ) {
                count++;
                for( int j = i; j < n; ++j) {
                    if(  segVector[j].start < segVector[i].end ) {
                        segVector[j].covered = true;
                    }
                    else if( fabs( segVector[j].start - segVector[i].end ) < 0.0000001 )
                    {
                        segVector[j].covered = true;
                    }
                }
            }
        }

        cout << "Case " << ++casenum << ": " << count << endl;
    }

    return 0;
}

bool mycompare(const Segment & left, const Segment & right)
{
    if( left.end < right.end )
        return true;
    else if(left.end == right.end )
    {
        return left.start < right.start;
    }

    return false;
}
