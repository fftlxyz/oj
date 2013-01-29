/*
 * memory: 6549k
 * time: 235ms
 * code legth: 3136b
 * date:2012-10-26 16:05:33
 */

#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

const int MAXSTATE = 362880;

struct Node
{
    char dir;
    bool visted;
    char state[9];
    int p;
} node[MAXSTATE];

char startState[] = {'2','3','4','1','5','9','7','6','8'};
char endState[] = {'1','2','3','4','5','6','7','8','9'};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char dir[] = {'u','d','l','r'};

int hash_code(char *p);

int main(int argc, const char *argv[])
{

    for( int i = 0; i < 9; ++i) {
        char ch;
        cin >> ch;
        if(ch == 'x')
            ch = '9';
        startState[i] = ch;
    }

    int start = hash_code(startState);
    int end = hash_code(endState);


    node[start].visted = true;
    node[start].p = -1;
    memcpy( node[start].state, startState, sizeof(endState) );

    queue<int> nodeQueue;

    nodeQueue.push(start);

    bool isOk = false;

    while( !nodeQueue.empty() ) {

        int head =  nodeQueue.front();
        nodeQueue.pop();

        if(head == end) {
            isOk = true;
            break;
        }

        int z;
        for(int i =0; i < 9; ++i) {
            if( node[head].state[i] == '9' ) {
                z= i;
            }
        }

        int x = z / 3;
        int y = z % 3;

        for(int i =0; i < 4; ++i ) {

            int newx = x + dx[i];
            int newy = y + dy[i];
            int newz = newx * 3 + newy;

            //没有越界
            if( newx > -1 && newx < 3 && newy > -1 && newy < 3) {

                char t = node[head].state[newz];
                node[head].state[newz] = node[head].state[z];
                node[head].state[z] = t;

                int newhc = hash_code(node[head].state);

                if(!node[newhc].visted) {

                    memcpy(node[newhc].state, node[head].state, sizeof(node[head].state));
                    node[newhc].p = head;
                    node[newhc].visted = true;
                    node[newhc].dir = dir[i];

                    nodeQueue.push(newhc);
                }

                t = node[head].state[newz];
                node[head].state[newz] = node[head].state[z];
                node[head].state[z] = t;
            }
        }
    }

    if(isOk)
    {
        stack<char> mov;

        int i = end;
        while( i != start ) {
            mov.push( node[i].dir);
            i = node[i].p;
        }

        while(!mov.empty()) {
            cout << mov.top();
            mov.pop();
        }
        cout << endl;
    }else {
        cout << "unsolvable" << endl;
    }

    return 0;
}


//1-9上全排列的hash
//最大之为9!-1 最小为0
//这是一个完美hash函数
int hash_code(char *p)
{
    static int perm[] = {1,1,2,6,24,120,720,5040,40320};
    int h = 0;

    //找全排列的hash方法
    for(int i =0; i < 9; ++i)
    {
        int count =0;
        for(int j =0 ;j < i; ++j) {
            if( p[i] < p[j])
                ++count;
        }
        h += perm[i] * count;
    }

    return h;
}
