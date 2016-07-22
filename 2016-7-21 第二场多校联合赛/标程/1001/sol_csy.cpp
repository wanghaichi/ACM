#include<cstdio>
typedef long long ll;
int T,n,i,w;ll s,u;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    for(u=s=0,i=1;i<=n;i++)scanf("%d",&w),s+=w>0?w:-w,u+=w*w;
    u=u*n-s*s;
    if(!u)puts("0/1");else{
      s=gcd(u,n);
      printf("%I64d/%d\n",u/s,n/s);
    }
  }
  return 0;
}