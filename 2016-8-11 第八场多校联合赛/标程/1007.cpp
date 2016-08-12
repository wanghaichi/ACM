#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,A[20],B[20],len,phi,C[20];
const int N=1100000;
int mo;
struct atom{
	int a,b;
}I[N],x[N];
atom operator * (atom k1,atom k2){
	return (atom){k1.a+k2.a,1ll*k1.b*k2.b%mo};
}
int quick(int k1,int k2,int Mo=-1){
	if (Mo==-1) Mo=mo;
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%Mo; k2>>=1;
		k1=1ll*k1*k1%Mo;
	}
	return k3;
}
atom operator / (atom k1,atom k2){
	return (atom){k1.a-k2.a,1ll*k1.b*quick(k2.b,phi-1)%mo};
}
int get(int p,int q,int Mo){
	mo=Mo; phi=Mo/p*(p-1);
	I[0]=(atom){0,1}; 
	for (int i=1;i<=n;i++){
		int k1=i,k2=0;
		while (k1%p==0) k1/=p,k2++;
		x[i]=(atom){k2,k1};
	}
	for (int i=1;i<=n+1;i++) I[i]=I[i-1]*x[i];
	atom u=I[n]/(I[n/2]*I[n-n/2]);
	int C=0;
	if (u.a>=q) C=0; else C=1ll*quick(p,u.a)*u.b%mo;
	u=u/x[n/2+1];
	int k1=0; 
	if (u.a>=q) k1=0; else k1=1ll*quick(p,u.a)*u.b%mo;
	int ans=(k1+4ll*(C-k1))%mo;
	int rem=(2ll*C-k1)%mo;
	ans=(ans-3ll*rem)%mo;
	return ((ans+3ll*quick(2,n))%mo+mo)%mo;
}
int solve(){
	len=0;
	if (m==1||(n&1)) return 0;
	for (int i=2;i*i<=m;i++)
		if (m%i==0){
			len++; A[len]=1; int num=0;
			while (m%i==0){
				A[len]*=i; num++; m/=i;
			}
			B[len]=get(i,num,A[len]);
			C[len]=A[len]/i*(i-1);
		}
	if (m>1){
		len++; A[len]=m; B[len]=get(m,1,A[len]); C[len]=m-1;
	}
	for (int i=1;i<len;i++){
		int k1=quick(A[i],C[i+1]-1,A[i+1]),k2=quick(A[i+1],C[i]-1,A[i]);
		mo=A[i]*A[i+1];
		B[i+1]=(1ll*B[i]*k2%mo*A[i+1]+1ll*B[i+1]*k1%mo*A[i])%mo;
		A[i+1]=mo; C[i+1]=C[i]*C[i+1];
	}
	return B[len];
}
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	int t; scanf("%d",&t);
	for (;t;t--){
		scanf("%d%d",&n,&m);
		printf("%d\n",solve());
	}
}
