#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<string>
#include<vector>
#include<set>
#include<queue>
#include<time.h>
#include<assert.h>
#include<iostream>
using namespace std;
typedef long long LL;
typedef pair<int,int>pi;
const int M=1e9+7;
const int Maxn=55;
int dp[Maxn][2],cnt[Maxn][2],fst[Maxn][2];
int val[Maxn],f[Maxn],sz[Maxn];
int ned[Maxn];
vector<int>G[Maxn];
bool ok;
int n,m;
pi find(int x){
	int y=x,ty=0;
	while(f[y]!=y)ty^=val[y],y=f[y];
	int tmp=0;
	while(x!=y){
		int t1=f[x],t2=val[x];
		val[x]=ty^tmp,tmp^=t2;
		f[x]=y,x=f[x];
	}
	return pi(y,ty);
}
void merge(int x,int y,int ty){
	pi xx=find(x),yy=find(y);
	if(xx.first>yy.first)swap(xx,yy);
	if(xx.first==yy.first){
		if((xx.second!=yy.second)!=ty){ok=0;return;}
	}
	else{
		sz[yy.first]+=sz[xx.first];
		f[xx.first]=yy.first;
		val[xx.first]=xx.second^yy.second^ty;
	}
}
int eu[2000],ev[2000],ne;
int main(){
	int _;scanf("%d",&_);
	while(_--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			int l,r;scanf("%d%d",&l,&r);
			cnt[i][0]=cnt[i][1]=(r-l+1)/2;
			if(l%2==r%2)cnt[i][l%2]++;
			fst[i][0]=cnt[i][0]?(l&1?(l+1):l):M;
			fst[i][1]=cnt[i][1]?(l&1?l:(l+1)):M;
		}
		cnt[0][0]=1;cnt[0][1]=0;
		for(int i=0;i<=n+1;i++)f[i]=i,val[i]=0,sz[i]=1;
		ne=0;
		ok=1;
		for(int i=0;i<m;i++){
			int l,r,ty;scanf("%d%d%d",&l,&r,&ty);
			merge(l,r+1,ty);
		}
		int ans=0;
		if(!ok){
			puts("0\n-1");
			continue;
		}
		vector<int>V;
		for(int i=1;i<=n+1;i++){
			if(f[i]==i&&sz[i]>1){
				//printf("i=%d\n",i);
				V.push_back(i);
			}
		}
		//for(int i=1;i<=n+1;i++)printf("u=%d val=%d\n",find(i).first,find(i).second);
		vector<int> res;
		res.assign(n,M);
		for(int mask=0;mask<1<<V.size();mask++){
			memset(ned,-1,sizeof(ned));
			for(int j=0;j<V.size();j++){
				if(mask>>j&1)ned[V[j]]=1;else ned[V[j]]=0;
			}
			if(ned[find(n+1).first]==1)continue;
			ned[n+1]=0;
			//for(int i=1;i<=n+1;i++)printf("%d ",find(i).second);puts("");
			dp[n+1][0]=1;dp[n+1][1]=0;
			for(int i=n;i>=1;i--){
				dp[i][0]=dp[i][1]=0;
				int nedcol=ned[find(i).first]<0?-1:(ned[find(i).first]^find(i).second);
				if(nedcol==-1){		
					dp[i][0]=(1LL*dp[i+1][1]*cnt[i][1]+1LL*dp[i+1][0]*cnt[i][0])%M;
					dp[i][1]=(1LL*dp[i+1][0]*cnt[i][1]+1LL*dp[i+1][1]*cnt[i][0])%M;
				}
				else if(nedcol==0)dp[i][0]=(1LL*dp[i+1][1]*cnt[i][1]+1LL*dp[i+1][0]*cnt[i][0])%M;
				else if(nedcol==1)dp[i][1]=(1LL*dp[i+1][0]*cnt[i][1]+1LL*dp[i+1][1]*cnt[i][0])%M;
			}
			//puts("ok");
			//for(int i=1;i<=n+1;i++)printf("dp=%d %d\n",dp[i][0],dp[i][1]);
			ans+=(dp[1][1]+dp[1][0])%M;
			if(ans>=M)ans-=M;
			for(int st=0;st<2;st++){
				if(!dp[1][st])continue;
				vector<int>ts(n,M);
				int pre=st;
				for(int i=1;i<=n;i++){
					//0
					if((dp[i+1][pre^1]&&dp[i+1][pre]&&fst[i][0]<fst[i][1])||(!dp[i+1][pre^1]))
						ts[i-1]=fst[i][0];
					else{
						ts[i-1]=fst[i][1];
						pre^=1;
					}
				}
				if(ts<res)res=ts;
			}
			//printf("mask=%d res=%d\n",mask,res[1]);
		}
		if(!ans)puts("0\n-1");
		else{
			printf("%d\n",ans);
			for(int i=0;i<res.size();i++)printf("%d%c",res[i],i==res.size()-1?'\n':' ');
		}
	}
	return 0;
}
