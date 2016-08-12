#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
struct bian{
	int next,point;
}b[6100];
int d[3100][3100],n,m,len,p[3100],tot[3100][3100],two[3100],ans[3100];
const int mo=998244353;
void ade(int k1,int k2){
	b[++len]=(bian){p[k1],k2}; p[k1]=len;
}
void add(int k1,int k2){
	ade(k1,k2); ade(k2,k1);
}
void dfs1(int k1,int k2){
	for (int i=1;i<=n/2;i++) d[k1][i]=0; d[k1][0]=1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2){
			dfs1(j,k1);
			for (int k=1;k<=n/2;k++) d[k1][k]+=d[j][k-1];
		}
	}
}
void dfs2(int k1,int k2){
	for (int i=0;i<=n/2;i++) tot[k1][i]=d[k1][i];
	for (int i=1;i<=n/2;i++){
		int num=tot[k2][i-1];
		if (i>1&&k2!=0) num-=d[k1][i-2];
		tot[k1][i]+=num;
	}
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2)
			dfs2(j,k1);
	}
}
void calc(int k1,int k2){
	int pre=1; ans[0]++;
	for (int now=1;now<=n/2;now++){
		if (tot[k1][now]<2) break;
		ans[now<<1]=(ans[now<<1]+1ll*two[pre]*(two[tot[k1][now]]-1-tot[k1][now]))%mo;
		for (int i=p[k1];i;i=b[i].next){
			int j=b[i].point; 
			if (j!=k2&&d[j][now-1]>1)
				ans[now<<1]=(ans[now<<1]-1ll*two[pre]*(two[d[j][now-1]]-1-d[j][now-1]))%mo;
		}
		if (tot[k1][now]-d[k1][now]>1){
			int k3=tot[k1][now]-d[k1][now];
			if (k3>1){
				ans[now<<1]=(ans[now<<1]-1ll*two[pre]*(two[k3]-1-k3))%mo;
			}
		}
		pre+=tot[k1][now];
	}
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2){
			calc(j,k1); int pre=0;
			for (int now=0;now<=n/2;now++){
				int x=tot[k1][now],y=d[j][now];
				if (now!=0) x-=d[j][now-1];
				if (x==0||y==0) break;
				ans[(now<<1)+1]=(ans[(now<<1)+1]+1ll*two[pre]*(two[x+y]-two[x]-two[y]+1))%mo;
				pre+=x+y;
			}
		}
	}
}
void solve(){
	scanf("%d",&n); memset(p,0x00,sizeof p); len=0;
	for (int i=1;i<n;i++){
		int k1,k2; scanf("%d%d",&k1,&k2); add(k1,k2);
	}
	memset(ans,0x00,sizeof ans);
	dfs1(1,0); two[0]=1; for (int i=1;i<=n;i++) two[i]=two[i-1]*2%mo;
	dfs2(1,0); calc(1,0);
	for (int i=0;i<n;i++) printf("%d ",(ans[i]+mo)%mo); printf("\n");
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	int t; scanf("%d",&t);
	for (;t;t--) solve();
	return 0;
}

