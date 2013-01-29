#include <stdio.h>
#include <string.h>
/* poj 1094
 * memory: 384K
 * time: 0MS
 * complier: G++
 * code length: 3014B
 * date: 2012-11-04 09:50:41
 *
 *
 * 这个题目我纠结了很久。。。。
 * 其实蛮简单的题目，没有正确的选择topo排序的方法。
 * 1.看是否不一致； dfs 环， postorder计算出来。
 * 2.能否确定关系；
 *   即使能拓扑排序也不代表关系可以确定。
 *   如：1.图被分成了多个部分；
 *       2.图有多个度(出度)为0
 *       3. ... 还有多少中情况呢。。。。。
 *   比较简单的判断方法，就是dfs后，postoder后，直接判断是否任意两相邻节点是否有边..
 *   嗯，就是验证一下就行了。。。。
 * * */
const int MAX_N = 28;

int node[MAX_N];
bool visited[MAX_N];
bool finished[MAX_N];

int postnum = 0;

int ordered[MAX_N];

int edge[MAX_N][MAX_N];
int indgree[MAX_N];

bool toposort();
bool dfs(int x);

int n, e;

int main(int argc, const char *argv[])
{
    while ( scanf("%d%d\n", &n, &e) == 2  ){
        if( n == 0 && e == 0)
            break;

        int i;
        char from , to;
        memset(edge, 0, sizeof(edge));
        memset(indgree, 0, sizeof(indgree));
        for(i = 0; i < e; ++i) {
            scanf("%c<%c\n", &from, &to);
            edge[from - 'A'][to - 'A'] = 1;
            ++indgree[to-'A'];

            bool ret = toposort();

            if(ret){
                if(postnum == n) {

                    printf("Sorted sequence determined after %d relations: ", i+1);
                    for(int j = postnum -1; j > -1; --j){
                        printf("%c", ordered[j] + 'A');
                    }
                    printf(".\n");
                    ++i;
                    break;

                } else if(i == e-1) {
                    printf("Sorted sequence cannot be determined.\n");
                }
            } else {
                printf("Inconsistency found after %d relations.\n",i+1);
                ++i;
                break;
            }
        }

        for( ; i< e; ++i) {
            scanf("%c<%c\n", &from, &to);
        }

    }

    return 0;
}


bool toposort()
{
    postnum = 0;
    memset(visited, 0, sizeof(visited));
    memset(finished, 0, sizeof(finished));

    for(int i = 0; i < n; ++i){

       if(!visited[i] && !indgree[i] ){

           postnum = 0;
           bool ret = dfs(i);
           if(!ret)
               return false;
       }
    }

    //拓扑可排不代表关系可以确定
    //1.A->B->D
    //  A->C->D
    //  B->C 关系不确定
    //2.A->B 有两个出度为0的结点
    //  A->C
    //  B和C的关系不确定
    if(postnum == n){
        for(int j =  n-1; j > 0; --j){

            if(!edge[ordered[j]][ordered[j-1]]) {
                postnum = -1;
                break;
            }
        }
    }
    return true;
}


bool dfs(int x)
{
    visited[x] = true;

    for(int i = 0; i < n; ++i){
        if(edge[x][i]){

            if(!visited[i] ) {

                bool ret = dfs(i);
                if(!ret)
                    return false;
            }
            else if(visited[i] && !finished[i]){
                return false;
            }
        }
    }

    ordered[postnum++] = x;
    finished[x] = true;
    return true;
}

