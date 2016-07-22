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
int n,m;
int a[222];
int main(){
	int _;scanf("%d",&_);
	while(_--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)a[i]=101;
		for(int i=0;i<m;i++){
			int x,y;scanf("%d%d",&x,&y);
			a[x]=y;
		}
		if(a[1]==101)a[1]=100;
		if(a[2]==101)a[2]=min(a[1],100);
		int ans=a[1]+a[2];
		int maxx=0;
		for(int i=n;i>=3;i--){
			if(a[i]!=101)maxx=max(maxx,a[i]);
			a[i]=maxx;
			ans+=maxx;
		}
		int t=a[1]+a[2];
		int gc=__gcd(t,ans);
		printf("%d/%d\n",t/gc,ans/gc);
	}
	return 0;
}
