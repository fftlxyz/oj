#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <algorithm>
using std::queue;
using std::sort;

//双向bfs

// 这个给我的启示是, 如果超时的话，可能判Wrong Answer
// 双向bfs
// 我直接bfs的话, 应该是超时了，可不知为什么判了个Wrong Anaswer, 害我检查了半天...
// 双向bfs果然不是盖的.
// 搜索的状态数, 从n, 变成了sqrt(n), nx...
// 11544624	fly2best	1198	Accepted	4724K	47MS	G++	4641B	2013-05-01 10:24:08
// 11541258	fly2best	1198	Wrong Answer			G++	4574B	2013-04-30 11:44:57
// 11541183	fly2best	1198	Wrong Answer			G++	4049B	2013-04-30 11:19:54


//64个格子的棋盘
//4个棋子
//最多64^4个状态
//就是2^24个状态,这个数据量很小
//不知哪里分析有误, 这个数据量是不大, 不知为什么超时, 过单个例子应该是没问题的, 可能过多个例子有问题.
//
//判重问题, 每个棋子用6位表示, 每个格局用24位表示
//2M内存,可以hold住
// 对状态进行编码, 转化为一个数字, 使用bitmap.
unsigned char bitmap[2][1 << 21];

struct Point;
struct State;

static inline void setbit(int di, int i);
static inline bool testbit(int di, int i);
static inline bool isinboard(int x, int y);

void printf_state(State& state);
int bfs();

struct Point
{
    char x;
    char y;
    bool operator < (const Point &obj) const {

        if (x < obj.x || (x == obj.x && y < obj.y))
            return true;

        return false;
    }
};

struct State
{
    Point points[4];

    void normalize() {
        sort(points, points+4);
        index = -1;
        step = 0;
    }

    //shold have be normalized
    int getIndex() {
        if (index == -1) {
            index = 0;
            for (int i = 0; i < 4; ++i) {
                index |= (points[i].x << 6 * i);
                index |= (points[i].y << (6 * i + 3));
            }
        }
        return index;
    }


    bool isContain(int x, int y)
    {
        for (int i = 0; i < 4; ++i) {
            if (points[i].x == x && points[i].y == y) {
                return true;
            }
        }
        return false;
    }

    int index;

    int step;

    bool operator == (State & obj) {
        return getIndex() == obj.getIndex();
    }


};

State start, end;

int main(int argc, const char *argv[])
{

    while (1) {
        memset(bitmap, 0, sizeof(bitmap));

        int x, y;
        for (int i = 0; i < 4; ++i) {
            int n = scanf("%d%d", &x, &y);

            if (n != 2)
                return 0;

            start.points[i].x = x - 1;
            start.points[i].y = y - 1;
        }

        for (int i = 0; i < 4; ++i) {
            scanf("%d%d", &x, &y);
            end.points[i].x = x - 1;
            end.points[i].y = y - 1;
        }

        start.normalize();
        end.normalize();

        if (bfs())
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}


int bfs()
{
    queue<State> que[2];

    que[0].push(start);
    setbit(0, start.getIndex());

    que[1].push(end);
    setbit(1, end.getIndex());

    int di = 0;
    while (!que[0].empty() || !que[1].empty()) {

        di ^= 1;

        if (que[di].empty())
            continue;

        State state = que[di].front();
        que[di].pop();

        static int dx[] = {1, -1, 0, 0};
        static int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {

            for (int j = 0; j < sizeof(dx) / sizeof(int); ++j) {

                State next = state;

                int nextx = next.points[i].x + dx[j];
                int nexty = next.points[i].y + dy[j];
                bool containnext = next.isContain(nextx, nexty);

                int nnextx = nextx + dx[j];
                int nnexty = nexty + dy[j];

                if (isinboard(nextx, nexty) && !containnext) {
                    next.points[i].x = nextx;
                    next.points[i].y = nexty;
                    next.normalize();
                } else if (containnext && isinboard(nnextx, nnexty) && !next.isContain(nnextx, nnexty)) {
                    next.points[i].x = nnextx;
                    next.points[i].y = nnexty;
                    next.normalize();
                }

                //如果从另一个方向访问过, 就返回真
                if (testbit(di ^ 1, next.getIndex())) {
                    return 1;
                }

                if ( !testbit(di, next.getIndex())) {
                    // printf_state(next);
                    setbit(di, next.getIndex());
                    next.step = state.step + 1;

                    //各走4步
                    if (next.step < 4)
                        que[di].push(next);
                }
            }
        }

    }
    return 0;
}


static inline void setbit(int di, int i)
{
    bitmap[di][i / 8] |= (1 << i % 8);
}

static inline bool testbit(int di, int i)
{
    return bitmap[di][i / 8] & (1 << i % 8);
}

static inline bool isinboard(int x, int y)
{
    return (x > -1 && x < 8) && (y > -1 && y < 8);
}

void printf_state(State& state)
{
    for (int i = 0; i < 4; ++i)
        printf("%d %d\n", state.points[i].x, state.points[i].y);
    printf("%p\n", state.getIndex());
}
