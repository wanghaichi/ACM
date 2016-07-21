#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define LL long long
using namespace std;

const int mod=1e9+7;
const int N=10000000;

bool check[N+5];
LL s[N+5];
int p,tot,phi[N+5],prime[N+5],n,m;

void getPhi(){
    memset(check,false,sizeof(check));
    phi[1]=1;
    tot=0;
    for(int i=2;i<=N;i++){
        if(!check[i]){phi[i]=i-1;prime[tot++]=i;}
        for(int j=0;j<tot;j++){
            if(i*prime[j]>N)break;
            check[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];break;
            }else{
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
    s[0]=0;
    for(int i=1;i<=N;i++)s[i]=(s[i-1]+phi[i])%mod;
}

LL work(int n,int m){
    if(n==1)return (s[m])%mod;
    if(m==1)return phi[n];
    if(m<1)return 0;
    for(int i=0;i<tot;i++){
        if(n%prime[i]==0){
            return (((LL)(prime[i]-1)*work(n/prime[i],m)%mod+work(n,m/prime[i])%mod)%mod);
        }
    }
    return 0;
}
LL pow(LL a,LL b,int p){
    LL now=1;
    while(b!=0){
        if(b%2==1)now*=a;
        a*=a;b/=2;a%=p;
        now%=p;
    }
    return now;
}

LL gao(LL k,int p){
    if(p==1)return 0;
    LL now=gao(k,phi[p]);
    return(pow(k,now+phi[p],p));
}

int main(){
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getPhi();
while(~scanf("%d %d %d",&n,&m,&p)){
    LL k=work(n,m);
  // printf("%I64d\n",k);
    printf("%I64d\n",gao(k,p));
}
    return 0;
}
