#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define NN 11000
#define int long long

int tp,prime[NN],pre[NN],x,y,d;

const int mod=9901;

void getprime(){
     int i,j;
     memset(pre,0,sizeof(pre));
     for(i=2;i<=10000;i++)if (!pre[i]){
        prime[++tp]=i;
        for(j=i*i;j<=10000;j+=i){
            pre[j]=1;
        }
     }
}

int mod_exp(int p,int cnt){
    if (cnt==1) return p%mod;
    int ans=mod_exp(p,cnt>>1);
    ans=ans*ans%mod;
    if (cnt&1) ans=ans*p%mod;
    return ans;
}

/*int gettmp(int p,int cnt){//二分求等比数列和p^0+...+p^cnt %mod
if (cnt==0) return 1;
int ans=1;
ans=(1+mod_exp(p,(cnt+1)/2))%mod;
ans=ans*gettmp(p,(cnt-1)/2)%mod;
if (cnt%2==0) {ans=(ans+mod_exp(p,cnt))%mod;}
return ans;
}*/

long long ex_gcd(long long a,long long b){
     if (b==0){
        x=1,y=0,d=a;
        return a;
     }
     else {
        long long gcd=ex_gcd(b,a%b);
        long long t=x;
        x=y;
        y=t-a/b*y;
        return gcd;
     }
}

int gettmp(int p,int cnt){//逆元法求等比数列和
    ex_gcd(9901,p-1);
    int rev=y;
    while (rev<0) rev=rev+9901*9901;
    int ans=(mod_exp(p,cnt+1)+mod-1)%mod;
    ans=ans*rev%mod;
    return ans;
}

int A,B,tmp,totfac,fac[NN],faccnt[NN],i,ans;

main(){
    tp=0;
    getprime();
    while(scanf("%lld%lld",&A,&B)!=EOF){
        if (A==0&&B!=0) {printf("0\n");continue;}
        tmp=A;
        totfac=0;//fac,faccnt
        for(i=1;i<=tp;i++){
            if (prime[i]>tmp) break;
            if (tmp%prime[i]==0){
                fac[++totfac]=prime[i];
                faccnt[totfac]=0;
                while(tmp%prime[i]==0){
                    tmp=tmp/prime[i];
                    faccnt[totfac]++;
                }
            }
        }
        if (tmp!=1) {fac[++totfac]=tmp;faccnt[totfac]=1;}
        for(i=1;i<=totfac;i++){faccnt[i]*=B;}
        ans=1;
        for(i=1;i<=totfac;i++){
            int p=fac[i]%mod;
            //用逆元法时要记得将fac[i]%mod,否则gcd(fac[i],9901)可能等于9901，则求不出逆元
            if (p==0) tmp=1;
            else if (p==1) tmp=(faccnt[i]+1)%mod;
            else tmp=gettmp(p,faccnt[i]);
            ans=ans*tmp%mod;
        }
        printf("%lld\n",ans);

    }
    return 0;
}

