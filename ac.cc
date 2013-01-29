#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int size = 2010;
int road[size][size];
int dist[size],flag[size];
char str[size][10];
#define max 999999
int distance(char str1[],char str2[])
{
    int sum=0,len,index;
    len=strlen(str1);
    for(index=0;index<len;index++)
        if(str1[index]!=str2[index])
            sum++;
    return sum;
}
int main()
{
    int n,i,j,k,sum,t;
    while(scanf("%d",&n)!=EOF&&n)
    {
        for(i=1;i<=n;i++)
            scanf("%s",str[i]);
        memset(dist,0,sizeof(dist));
        memset(road,0,sizeof(road));
        memset(flag,0,sizeof(flag));
        for(i=1;i<n;i++)
        {
            for(j=i+1;j<=n;j++)
            {
                road[i][j]=distance(str[i],str[j]);
                road[j][i]=road[i][j];
            }
        }

        // printf("  ");
        // for(int i = 0; i < n; ++i) {
            // printf("%d ", i);
        // }
        // printf("\n");
        // for(int i = 1; i <= n; ++i) {
            // printf("%d ", i-1);
            // for(int j = 1; j <= n; ++j){
                // printf("%d ", road[i][j]);
            // }
            // printf("\n");
        // }

        sum=0;
        for(k=1;k<=n;k++)
            dist[k]=road[1][k];
        flag[1]=1;
        for(i=1;i<n;i++)
        {
            t=max;
            for(j=1;j<=n;j++)
                if(!flag[j]&&dist[j]<t)
                {
                    t=dist[j];
                    k=j;
                }
            sum+=t;
            flag[k]=1;
            for(j=1;j<=n;j++)
                if(!flag[j]&&road[k][j]<dist[j])
                    dist[j]=road[k][j];
        }
        printf("The highest possible quality is 1/%d.\n",sum);
    }
    return 1;
}
