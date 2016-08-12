#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N=510000;
long long A[N],B[N],C[N],x[N];
int n,m,s[N],head;
set<int>S;
void add(long long *A,int k1,long long k2){
	for (;k1<=n;k1+=k1&(-k1)) A[k1]+=k2;
}
long long find(long long *A,int k1){
	long long ans=0; for (;k1;k1-=k1&(-k1)) ans+=A[k1]; return ans;
}
void addall(int k1,long long k2){
//	cout<<"addall "<<k1<<" "<<k2<<endl;
	add(B,k1,k2); 
	add(C,k1,1ll*k2*(n-k1+1));
}
void addin(int k1,int k2){
	if (k1>n) return;
	long long pre=A[k1];
	A[k1]+=k2; addall(k1,k2);
	if (A[k1]&&pre==0) S.insert(k1); else if (A[k1]==0&&pre) S.erase(k1);
}
long long getans(int k1){
//	cout<<"fa "<<k1<<" "<<find(C,k1)<<" "<<find(B,k1)<<endl;
	return find(C,k1)-find(B,k1)*(n-k1);
}
long long getw(long long k1){
	return trunc(sqrt(k1)+1e-8);
}
void update(int k1){
	addin(k1,x[k1]-x[k1-1]-A[k1]);
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	int t; scanf("%d",&t);
	for (;t;t--){
		scanf("%d%d",&n,&m); S.clear();
		memset(B,0x00,sizeof B);
		memset(C,0x00,sizeof C);
		for (int i=1;i<=n;i++){
			scanf("%lld",&A[i]);
			if (A[i]!=A[i-1]){
				S.insert(i); addall(i,A[i]-A[i-1]);
			}
		}
		for (int i=n;i;i--) A[i]-=A[i-1];
		for (;m;m--){
			int k1; scanf("%d",&k1);
			if (k1==1){
				int k2,k3,k4; scanf("%d%d%d",&k2,&k3,&k4);
				addin(k2,k4); addin(k3+1,-k4);
			} else if (k1==2){
				int k2,k3; scanf("%d%d",&k2,&k3); head=1;
				set<int>::iterator k4=S.upper_bound(k2);
				x[k2-1]=find(B,k2-1); x[k2]=getw(find(B,k2)); s[1]=k2;
				while (k4!=S.end()&&(*k4)<=k3){
					int where=(*k4); x[where-1]=getw(find(B,where-1));
					x[where]=getw(find(B,where));
					s[++head]=where; k4++;
				}
				if (k3!=n){
					x[k3]=getw(find(B,k3)); x[k3+1]=find(B,k3+1);
					s[++head]=k3+1;
				}
			//	for (int i=1;i<=n;i++) cout<<x[i]<<" "; cout<<endl;
				for (int i=1;i<=head;i++) update(s[i]);
			} else if (k1==3){
				int k2,k3; scanf("%d%d",&k2,&k3);
				printf("%lld\n",getans(k3)-getans(k2-1));
			}
		}
	}
	return 0;
}
