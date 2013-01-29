#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
const int MAXN=601,INF=0x7FFFFFFF;
using namespace std;
struct point
{
	int key[2];
}P[MAXN],Q[MAXN];
int N,Ans,A[MAXN],G[MAXN],C[25],order[MAXN];
void countingsort(int y)
{
	int i;
	memset(C,0,sizeof(C));
	for (i=1;i<=N;i++)
		C[P[i].key[y]]++;
	for (i=1;i<=24;i++)
		C[i]+=C[i-1];
	for (i=N;i>=1;i--)
	{
		order[C[P[i].key[y]]]=i;
		C[P[i].key[y]]--;
	}
	for (i=1;i<=N;i++)
		Q[i]=P[order[i]];
	for (i=1;i<=N;i++)
		P[i]=Q[i];
}
void radixsort()
{
	countingsort(1);
	countingsort(0);
}
inline int binsearch(int v)
{
	int a=0,b=N,m;
	while (a+1<b)
	{
		m=(a+b)>>1;
		if (G[m]<v)
			a=m;
		else
			b=m-1;
	}
	if (G[b]<v)
		a=b;
	return a;
}
void dynamic()
{
	int i,k;
	radixsort();
	A[0]=G[0]=0;
	for (i=1;i<=N;i++)
	{
		A[N-i+1]=P[i].key[1];
		G[i]=INF;
	}
	for (i=1;i<=N;i++)
	{
		k=binsearch(A[i]); //查找小于A[i]的最大G[k]，返回k
		if (A[i] < G[k+1])
			G[k+1]=A[i];
	}
	for (i=N;i>=0;i--)
		if (G[i]!=INF)
		{
			Ans=i;
			break;
		}
}
int main()
{
	int x,y;
	while (scanf("%d%d",&x,&y),x!=-1 || y!=-1)
	{
		N=Ans=0;
		while (x!=0 || y!=0)
		{
			P[++N].key[0]=x;P[N].key[1]=y;
			scanf("%d%d",&x,&y);
		}
		dynamic();
		printf("%d\n",Ans);
	}
	return 0;
}
