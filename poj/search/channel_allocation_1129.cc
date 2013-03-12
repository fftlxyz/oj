// poj 1129
// Accepted
// 388K
// 16MS
// G++
// 1619B
// 2013-02-28 20:38:08
// 你要知道枚举的是什么？
// 枚举已有的颜色, 然后再加一种颜色，我得再想想这个题
// 加这一种颜色是不是必需的？
#include <stdio.h>
#include <string.h>


int color[26];
int colorcnt = 0;
bool map[26][26];
int n;
int min = 26;

void dfs(int x);

int main(int argc, const char *argv[])
{
    char buf[32] = {0};
    int i, j;

    while((scanf("%d", &n) != EOF) && n != 0) {

        memset(map, 0, sizeof(map));
        memset(color, -1, sizeof(color));
        colorcnt = 0;
        min = n;

        i = 0;
        while (i < n) {
            scanf("%s", buf);
            j = 2;
            // printf("%c:", 'A' + i);
            while (buf[j] != '\0') {
                map[i][buf[j] - 'A'] = true;
                // printf("%c", buf[j]);
                ++j;
            }
            ++i;
            // printf("\n");
        }


        dfs(0);

        if (min > 1)
            printf("%d channels needed.\n", min);
        else
            printf("%d channel needed.\n", min);
    }


    return 0;
}

void dfs(int x)
{
    int i, j;
    bool isfound = true;
    bool newcolor = true;

    //剪枝
    if (colorcnt >= min) {
        return;
    }

    if (x == n) {
        min = colorcnt;
        return ;
    }

    for (i = 0; i < colorcnt; ++i) {
        isfound = true;

        for (j =0; j < n; ++j) {
            if (map[x][j] && color[j] == i) {
                isfound =false;
            }
        }

        if (isfound) {
            newcolor = false;

            color[x] = i;
            dfs(x+1);
        }
    }

    if (newcolor) {
        color[x] = colorcnt++;
        dfs(x+1);
        colorcnt--;
    }

}
