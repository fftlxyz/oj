#include <stdio.h>
#include <string.h>

inline int max(int a, int b)
{
   return a > b ? a : b;
}

inline int min(int a, int b)
{
   return a < b ? a : b;
}
const int MAX_N = 5;

int n;
int weight[MAX_N][MAX_N];
int lx[MAX_N];
int ly[MAX_N];
int left[MAX_N];

bool s[MAX_N];
bool t[MAX_N];


//just cross path的过程
bool match(int i)
{
    s[i] = true;
    for (int j = 1; j <= n; ++j)
        if( lx[i] + ly[j] == weight[i][j] && !t[j] ) {
            t[j] = true;
            if ( left[j] == 0 || match(left[j]) ) {
                left[j] = i;
                return true;
            }
        }
    return false;
}

void update()
{
    int delta = 1 << 30;

    for(int i = 1; i <= n; ++i) if(s[i])
        for(int j = 1;   j <=n ; ++j) if(!t[j]) {
            delta = min(delta, lx[i] + ly[j] - weight[i][j]);
        }

    for(int i =1; i <= n; ++i) {
        if(s[i]) lx[i] -= delta;  // so we can add an edage in
        if(t[i]) ly[i] += delta;  // so we can keep the matched edge unchaged
    }

}


int km()
{
    //init label
    for (int i = 1; i <= n; ++i) {
        lx[i] = ly[i] = 0;
        for ( int j = 1; j <=n; ++j) {
            lx[i] = max( lx[i], weight[i][j]);
        }
    }

    memset(left,0, sizeof(left));

    for( int i = 1; i <= n; ++i) {

        //必须把节点i给我match了....
        for(;;) {
            //需初始化，表示从i开始的匈牙利树
            memset(s, 0, sizeof(s));
            memset(t, 0, sizeof(t));
            if (match(i))
                break;
            else
                update();
        }
    }


    int w = 0;
    for(int i = 1; i <= n; ++i) {
        w += weight[left[i]][i];
    }
    return w;
}

int main(int argc, const char *argv[])
{

    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &weight[i][j]);
        }
    printf("%d\n",km());

    return 0;
}
