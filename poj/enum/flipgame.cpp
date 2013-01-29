
/*
 * poj 1753
 * memory: 904K
 * time: 47MS
 * code length: 504B
 * date: 2012-10-28 21:29:42
 * */

#include <iostream>
#include <queue>
#include  <iomanip>
using namespace std;

bool vis[1<<16];
unsigned short father[1<<16];

unsigned short change[16] = {
    0x0013, 0x0027, 0x004e, 0x008c,  // 0 - 3
    0x0131, 0x0272, 0x04e4, 0x08c8,  // 4 - 7
    0x1310, 0x2720, 0x4e40, 0x8c80,  // 8 - 11
    0x3100, 0x7200, 0xe400, 0xc800,  // 12 -15
};

int main(int argc, const char *argv[])
{
    queue<unsigned short> statequeue;

    unsigned short start = 0;

    char ch;
    for(int i = 0; i < 16; ++i) {
        cin >> ch;

        if(ch == 'b') {
            start |= (1<<i);
        }
    }

    statequeue.push(start);
    vis[start] = true;
    father[start] = -1;

    bool isOk = false;
    unsigned short head;
    while( !statequeue.empty() ){

        head = statequeue.front();
        statequeue.pop();

        if(head == 0 || head == 0xffff ) {
            isOk = true;
            break;
        }

        for(int i =0; i < 16; ++i) {

            unsigned short tmp = head;
            tmp ^= change[i];

            if( !vis[tmp]) {

                statequeue.push(tmp);
                vis[tmp] = true;
                father[tmp] = head;
            }
        }
    }

    if(isOk) {

        int mov = 0;

        while( head != start ) {
            ++mov;
            head = father[head];
        }

        cout << mov << endl;

    }else {
        cout << "Impossible" << endl;
    }

    return 0;
}
