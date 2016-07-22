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
const int Maxn=1000020;
int cnt[Maxn],tl[Maxn];
int cas=0;
int ask(int x){
	if(tl[x]==cas)return cnt[x];
	return 0;
}
void add(int x){
	if(tl[x]<cas)tl[x]=cas,cnt[x]=0;
	cnt[x]++;
}
int main(){
	int _;scanf("%d",&_);
	int n;
	while(_--){
		cas++;
		scanf("%d",&n);
		vector<int>V;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			for(int j=1;j*j<=x;j++){
				if(x%j==0){
					V.push_back(j);
					add(j);
					if(j*j!=x){
						add(x/j);
						V.push_back(x/j);
					}
				}
			}
		}
		int ans=1;
		for(int i=0;i<V.size();i++){
			int x=V[i];
			int t=ask(x);
			if(t>=2)ans=max(ans,V[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
