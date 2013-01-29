#include <stdio.h>
#include <string.h>
#define eps 1e-8
using namespace std;
int m, n, x, el;double value;
struct E{
    int u, v;
    double r, c;
}e[1001];
bool bellman(){
    int i, j, f, p[102], u, v;double r, c, d[102];
    memset(d, 0, sizeof(d));
    d[x] = value;
    while(d[x] <= value + eps){
        f = 0;
        for(j = 0; j <= el; j++){
            if(d[e[j].v] + eps < (d[e[j].u] - e[j].c) * e[j].r ){
                d[e[j].v] = (d[e[j].u] - e[j].c) * e[j].r;
                p[e[j].v] = e[j].u;
                f = 1;
            }
        }
        if(!f)
            return d[x] > value + eps;
    }
    return 1;
}
int main(){
    // freopen("1860.in","r",stdin);
    // freopen("1860.out","w",stdout);
    int i, j, u, v, f;double ruv, cuv, rvu, cvu;
    while(scanf("%d%d%d%lf", &m, &n, &x, &value) != -1){
        el = 0;
        for(i = 0; i < n; i++){
            scanf("%d%d%lf%lf%lf%lf", &u, &v, &ruv, &cuv, &rvu, &cvu);
            e[el].u = u;
            e[el].v = v;
            e[el].r = ruv;
            e[el++].c = cuv;
            e[el].u = v;
            e[el].v = u;
            e[el].r = rvu;
            e[el++].c = cvu;
        }
        if(bellman())puts("YES");
        else puts("NO");
    }
    return 0;
}
