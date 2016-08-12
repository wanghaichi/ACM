#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100000,g=3;
int G[30],nG[30],two[30];
int n,x[N+10],I[N+10],nI[N+10],tw[N+10],A[N<<2],B[N<<2],ans[N];
const int mo=998244353;
void fft(int *x,int n,int fl=1){
    for (int i=(n>>1),j=1;j<n;j++){
        if (i<j) swap(x[i],x[j]);
        int k;
        for (k=(n>>1);i&k;i^=k,k>>=1); i^=k;
    }
    int now=0;
    for (int m=2;m<=n;m<<=1){
        int w; now++; if (fl==1) w=G[now]; else w=nG[now];
        for (int i=0;i<n;i+=m){
            int cur=1;
            for (int j=i;j<i+(m>>1);j++){
                int u=x[j],v=1ll*x[j+(m>>1)]*cur%mo;
                x[j]=(u+v)%mo; x[j+(m>>1)]=(u-v+mo)%mo;
                cur=1ll*cur*w%mo;
            }
        }
    }
}
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
    int now=(mo-1)/2,ng=quick(g,mo-2),len=0;
    while (now%2==0){
        len++; G[len]=quick(g,now); nG[len]=quick(ng,now); two[len]=quick(1<<len,mo-2); now>>=1;
    }
	int t; scanf("%d",&t); I[0]=1; tw[0]=1;
	for (int i=1;i<=N;i++) I[i]=1ll*I[i-1]*i%mo;
	for (int i=0;i<=N;i++) nI[i]=quick(I[i],mo-2);
	for (int i=1;i<=N;i++) tw[i]=2*tw[i-1]%mo;
	for (;t;t--){
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&x[i]);
		sort(x+1,x+n+1);
		len=0; while ((1<<len)<(n+1<<1)) len++;
		for (int i=0;i<(1<<len);i++) A[i]=0,B[i]=0;
		for (int i=1;i<=n;i++) A[i]=1ll*I[n-i]*tw[i-1]%mo*x[i]%mo;
		for (int i=0;i<=n;i++) B[i]=nI[i];
		fft(A,1<<len); fft(B,1<<len);
		for (int i=0;i<(1<<len);i++) A[i]=1ll*A[i]*B[i]%mo;
		fft(A,1<<len,-1);
		for (int i=1;i<=n;i++) ans[i]=(1ll*nI[i-1]*A[n-i+1]%mo*two[len]%mo+mo)%mo;
		for (int i=1;i<=n;i++) ans[i]=(ans[i-1]+ans[i])%mo;
		for (int i=1;i<=n;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
