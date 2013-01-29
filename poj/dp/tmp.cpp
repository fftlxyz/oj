
#include <iostream>
#include<cstdio>
#include <cstring>
#include<cmath>
#include<algorithm>
using namespace std;


struct node
{
    int num;
    int value;

}a[15];




bool dp[100001];
int cash,N;

int main ()
{
    int i,j,k;
    while(scanf("%d%d",&cash,&N)!=EOF)
    {

        memset(dp,0,sizeof(dp));
        for(i=1;i<=N;i++)
            scanf("%d%d",&a[i].num,&a[i].value);
        if (cash==0||N==0)
        {
            printf("0\n");
            continue;
        }

        int max=0;
        dp[0]=true;
        for(i=1;i<=N;i++)
        {
            if(a[i].value>cash)
                continue;
            for(j=max;j>=0;j--)
            {
                if(dp[j]==true)
                for(k=1;k<=a[i].num;k++)
                {

                    {
                        int temp=j+k*a[i].value;
                        if(temp>cash)
                            break;
                        if(temp>max)
                        {
                            max=temp;
                        }
                        dp[temp]=true;
                    }
                }
            }
        }
        printf("%d\n",max);

    }
    return 0;
}
