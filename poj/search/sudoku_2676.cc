/* poj
 * fly2best
 * 2676
 * Accepted
 * 388K
 * 1875MS
 * G++
 * 2318B
 * 2013-02-23 18:32:34
 *
 * 这个题目的可以优化的地方:
 * 把状态保存起来，check的时候，每次都去搜索, 我本不愿去优化，
 * 但是，这样可以让我更好的体会回溯法,所以...
 *
 * 无法理解，为什么会超时
 * 我自认位优化后的代码，怎么会超时呢?
 * 数组越界了....汗啊...有个优化写错了..
 * fly2best	2676	Accepted	384K	922MS	G++	2314B	2013-02-23 22:04:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(int *p, int i, int k);
bool dfs(int *p);

bool checku(int *p, int i, int k);
bool dfsu(int *p, int zeroi);

bool row[10][10];
bool column[10][10];
bool subsquare[10][10];

int zerolist[81];
int zerocnt;

int main(int argc, const char *argv[])
{
    char buf[16] = {0};
    int sudoku[81];
    int casenum, i, j, k;


    scanf("%d", &casenum);

    while (casenum--) {

        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));
        memset(subsquare, 0, sizeof(subsquare));
        memset(zerolist, 0, sizeof(zerolist));
        zerocnt = 0;

        for (i = 0; i < 9; ++i) {
            scanf("%s", buf);
            for (j = 0; j < 9; ++j) {
                k = buf[j] - '0';
                sudoku[i * 9 + j] = k;

                //优化
                row[i][k] = true;
                column[j][k] = true;
                subsquare[i/3*3 + j/3][k] = true;
                if (!k)
                    zerolist[zerocnt++] = i * 9 + j;
            }
        }

        dfsu(sudoku, 0);
    }

    return 0;
}

bool dfsu(int *p, int zeroi)
{
    int x, y, squarei;
    int pi;

    if (zeroi == zerocnt) {
        // output
        for (pi = 0; pi < 81; ++pi) {
            printf("%d", p[pi]);

            if ((pi + 1) % 9 == 0) {
                printf("\n");
            }
        }
        return true;
    }

    int i = zerolist[zeroi];

    x = i % 9;
    y = i / 9;
    squarei = y/3*3 + x/3;

    if (zeroi < zerocnt) {

        for (int k = 1; k < 10; ++k) {

            // if (checku(p, i, k) != check(p, i, k)) {
                // printf("%d %d\n", i, k);
            // }

            if (checku(p, i, k)) {
                p[i] = k;

                row[y][k] = column[x][k] = subsquare[squarei][k] = true;

                // printf("%d %d\n", i, k);

                if (dfsu(p, zeroi+1)){
                    return true;
                }

                row[y][k] = column[x][k] = subsquare[squarei][k] = false; //回溯
            }
        }

    }
    p[i] = 0;  // 回溯
    return false;
}

bool checku(int *p, int i, int k)
{
    int x = i % 9;
    int y = i / 9;

    return !(row[y][k] || column[x][k] || subsquare[y/3*3 + x/3][k]);
}

bool dfs(int *p)
{
    int i= 0;
    int x, y, squarei;
    bool isok = false;
    for( i = 0; i < 81; ++i) {
        if (p[i] == 0) {
            isok = true;
            break;
        }
    }

    x = i % 9;
    y = i / 9;
    squarei = y/3*3 + x/3;

    if (isok) {

        for (int k = 1; k < 10; ++k) {

            // if (checku(p, i, k) != check(p, i, k)) {
                // printf("%d %d\n", i, k);
            // }

            if (checku(p, i, k)) {
                p[i] = k;

                row[y][k] = column[x][k] = subsquare[squarei][k] = true;

                // printf("%d %d\n", i, k);

                if (dfs(p)){
                    return true;
                }

                row[y][k] = column[x][k] = subsquare[squarei][k] = false; //回溯
            }
        }

    } else {

        // output
        int pi;
        for (pi = 0; pi < 81; ++pi) {
            printf("%d", p[pi]);

            if ((pi + 1) % 9 == 0) {
                printf("\n");
            }
        }
    }

    p[i] = 0;  // 回溯

    return !isok;
}


bool check(int *p, int i, int k)
{
    int x = i % 9;
    int y = i / 9;

    int r, c, m, n;

    //行
    for ( c = 0; c < 9; ++c) {
        if (p[y * 9 + c] == k)
            return false;
    }

    //列
    for ( r = 0; r < 9; ++r) {
        if (p[r * 9 + x] == k)
            return false;
    }

    r = y / 3 * 3;
    c = x / 3 * 3;

    for (m = r; m < r + 3; ++m) {
        for ( n = c; n < c + 3; ++n) {

            if (p[m*9 + n] == k)
                return false;
        }
    }

    return true;
}
