
/* poj 1860
 * memory: 400K
 * time: 16MS
 * code length: 1929B
 * date: 2012-11-01 08:19:25
 */
/*
 * 水题啊。。。。。。
 * 但是我贡献了3次WA
 * 前3次，用的int, 保存的rate 和 commistion， 估计溢出了
 * bellmanford 正环
 * */

#include <stdio.h>
#include <string.h>


struct Edge
{
    int x;
    int y;
    double rate;
    double commission;
} edges[201];

int numofedges;

double check[101];


int main(int argc, const char *argv[])
{
    int n, m, s;
    double v;

    scanf("%d%d%d%lf", &n, &m, &s ,&v);
    numofedges = 2 * m;

    int a, b;
    double drab, dcab, drba, dcba;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lf%lf%lf%lf", &a, &b, &drab, &dcab, &drba, &dcba);

        edges[2*i].x = a;
        edges[2*i].y = b;
        edges[2*i].rate = drab;
        edges[2*i].commission = dcab;

        edges[2*i + 1].x = b;
        edges[2*i + 1].y = a;
        edges[2*i + 1].rate = drba;
        edges[2*i + 1].commission = dcba;
    }

    memset(check, 0, sizeof(check));

    check[s] = v;

    bool isbreak = false;
    for (int i = 0; i < n - 1; ++i) {

        bool updated = false;

        for (int j = 0 ; j < numofedges; ++j) {

            int x = edges[j].x;
            int y = edges[j].y;
            double rxy = edges[j].rate;
            double cxy = edges[j].commission;

            double update = ((check[x] - cxy)) * rxy;

            if (check[y] < update) {
                check[y] = update;

                updated = true;
            }
        }

        if(!updated){
            isbreak = true;
            break;
        }
    }

    bool circle = false;

    if(!isbreak){
        for (int j = 0 ; j < numofedges; ++j) {

            int x = edges[j].x;
            int y = edges[j].y;
            double rxy = edges[j].rate;
            double cxy = edges[j].commission;

            double update = (check[x] - cxy) * rxy;
            if (check[y] < update) {
                circle = true;
                break;
            }
        }
    }

    circle ? printf("YES\n") : printf("NO\n");

    return 0;
}
