#include<cstdio>
#define N 65540
typedef unsigned int U;
U T,n,i,x,w[N],g[N],nxt[N],f[256][256],h[N][256],v[256],ans;
char op[9];
inline void read(U&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline U opt(U a,U b){
  if(op[0]=='A')return a&b;
  if(op[0]=='O')return a|b;
  return a^b;
}
inline void up(U&a,U b){if(a<b)a=b;}
void dfs(U x){
  U dp=0,A=w[x]>>8,B=w[x]&255,i;
  for(i=0;i<256;i++)if(v[i])up(dp,f[i][B]+(opt(A,i)<<8));
  ans=(1LL*x*(dp+w[x])+ans)%1000000007;
  for(v[A]++,i=0;i<256;i++)h[x][i]=f[A][i],up(f[A][i],opt(B,i)+dp);
  for(i=g[x];i;i=nxt[i])dfs(i);
  for(v[A]--,i=0;i<256;i++)f[A][i]=h[x][i];
}
int main(){
  read(T);
  while(T--){
    read(n);scanf("%s",op);
    for(i=1;i<=n;i++)read(w[i]),g[i]=0;
    for(i=2;i<=n;i++)read(x),nxt[i]=g[x],g[x]=i;
    ans=0,
    dfs(1);
    printf("%u\n",ans);
  }
  return 0;
}
