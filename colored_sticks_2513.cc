
/* fly2best
 * 2513
 * Accepted
 * 73584K
 * 1422MS
 * G++
 * 2870B
 * 2013-02-21 16:07:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int NSTICKS = 250010;

int graph_node[NSTICKS*2];
int father[NSTICKS*2];

struct tire_node_t
{
    tire_node_t *  children[26];
    int index;
};

tire_node_t root;

int count = 0;

tire_node_t * find_node(char *str);
int get_node_index(tire_node_t *node);
void add_graph_edge(int u, int v);
int find(int u);

void traverse(tire_node_t *node);

int main(int argc, const char *argv[])
{
    tire_node_t * node1;
    tire_node_t * node2;
    root.index = -1;
    char buf1[12] = {0};
    char buf2[12] = {0};
    memset(father, -1, sizeof(father));

    while( scanf("%s %s", buf1, buf2) == 2) {

       node1 = find_node(buf1);
       node2 = find_node(buf2);

       add_graph_edge(get_node_index(node1), get_node_index(node2));
    }

    int odd_node_cnt = 0;

    for(int i = 0; i < count; ++i) {
        if (graph_node[i] % 2 != 0 ) {
            ++odd_node_cnt;
        }
    }

    // traverse(&root);

    if( odd_node_cnt == 0  || odd_node_cnt == 2) {

        int set_cnt = 0;
        for( int i = 0; i < count; ++i) {
            if (father[i] == -1) {
                ++set_cnt;
            }
        }

        //万能的discuss...
        if (set_cnt == 1 || set_cnt == 0)
            printf("Possible\n");
        else {
            //not connected
            // printf("setcount:%d\n", set_cnt);
            printf("Impossible\n");
        }
    } else {
        printf("Impossible\n");
    }


    return 0;
}


tire_node_t * find_node(char *str)
{
    tire_node_t *p = &root;
    int i;

    while(*str != '\0') {
        i = *str++ - 'a';

        if ( p->children[i] == NULL ) {

            p->children[i] = (tire_node_t *)malloc(sizeof(tire_node_t));
            memset(p->children[i], 0, sizeof(tire_node_t));
            p->children[i]->index = -1;
        }
        p = p->children[i];
    }

    return p;
}

int get_node_index(tire_node_t *node)
{
    if (node->index == -1) {
        node->index = count++;
    }
    return node->index;
}

void add_graph_edge(int u, int v)
{
    graph_node[u]++;
    graph_node[v]++;

    int f1 = find(u);
    int f2 = find(v);

    if (f1 != f2) {
        father[f1] = f2;
    }
}

int find(int u)
{
    if (father[u] == -1)
        return u;

    int f = find(father[u]);
    father[u] = f;
    return f;
}

static char buf[12] = {0};
static int level = -1;

void traverse(tire_node_t *node)
{
    level++;

    if( node->index != -1) {
        buf[level] = '\0';
        printf("%s degree:%d\n", buf, graph_node[node->index]);
    }

    for(int i = 0; i < 26; ++i) {
        if (node->children[i] != 0) {
            buf[level] = 'a' + i;
            traverse(node->children[i]);
        }
    }
    level--;

}
