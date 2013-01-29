
/*
 * poj 2965
 * memory:940K
 * time:329MS
 * code length:1896B
 * date: 2012-10-28 22:10:00
 * */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

bool vis[1<<16];
unsigned short father[1<<16];

unsigned short change[16] = {
    0x111f,0x222f,0x444f,0x888f,
    0x11f1,0x22f2,0x44f4,0x88f8,
    0x1f11,0x2f22,0x4f44,0x8f88,
    0xf111,0xf222,0xf444,0xf888
};

int main(int argc, const char *argv[])
{
    queue<unsigned short> statequeue;

    unsigned short start = 0;

    char ch;
    for(int i = 0; i < 16; ++i) {
        cin >> ch;

        if(ch == '+' ) {
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

        if(head == 0 ) {
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

        stack<unsigned short> path;

        while( head != start ) {
            ++mov;

            path.push(head);
            head = father[head];
        }

        cout << mov << endl;

        unsigned short pre = head;
        while(!path.empty()) {

            unsigned short top = path.top();
            path.pop();

            int changei = top ^ pre;
            pre = top;


            for( int i = 0; i < 16; ++i) {

                if( change[i] == changei )
                   cout << (i/4) +1  << " " << (i%4) + 1 << endl;
            }
        }

    }else {
        cout << "Impossible" << endl;
    }

    return 0;
}
