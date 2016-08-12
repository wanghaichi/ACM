#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int mo=998244353,g=3;
int G[30],nG[30],two[30],n,m,S[30][30],I[11000],nI[11000],rem[11000];
int A[40000],num[22][40000],B[40000];
int quick(int k1,int k2){
    int k3=1;
    while (k2){
        if (k2&1) k3=1ll*k3*k1%mo; k1=1ll*k1*k1%mo; k2>>=1;
    }
    return k3;
}
void fft(int *x,int n,int fl=1){
    for (int i=(n>>1),j=1;j<n;j++){
        if (i<j) swap(x[i],x[j]); int k=(n>>1);
        for (;i&k;i^=k,k>>=1); i^=k;
    }
    int now=0;
    for (int m=2;m<=n;m<<=1){
        int w; now++; if (fl==1) w=G[now]; else w=nG[now];
        for (int i=0;i<n;i+=m){
            int cur=1;
            for (int j=i;j<i+(m>>1);j++){
                int u=x[j],v=1ll*cur*x[j+(m>>1)]%mo;
                x[j]=(u+v)%mo; x[j+(m>>1)]=(u-v+mo)%mo;
                cur=1ll*cur*w%mo;
            }
        }
    }
}
int C(int k1,int k2){
    if (k1<k2) return 0;
    return 1ll*I[k1]*nI[k2]%mo*nI[k1-k2]%mo;
}
int main(){
//    freopen("graph.in","r",stdin);
//    freopen("graph.out","w",stdout);
    int now=(mo-1)/2,ng=quick(g,mo-2),len=0;
    while (now%2==0){
        G[++len]=quick(g,now); nG[len]=quick(ng,now); two[len]=quick(1<<len,mo-2); now>>=1;
    }
    n=10000; m=20; I[0]=1;
    for (int i=1;i<=n;i++) I[i]=1ll*I[i-1]*i%mo;
    for (int i=0;i<=n;i++) nI[i]=quick(I[i],mo-2);
    len=0; while ((1<<len)<(n<<1)) len++;
    for (int i=2;i<=n;i++) A[i]=quick(i,i-2); A[1]=1;
    memcpy(num[1],A,sizeof num[1]);
    for (int i=1;i<=n;i++) A[i]=1ll*A[i]*nI[i-1]%mo;
    fft(A,1<<len); 
    for (int i=2;i<=m;i++){
        memcpy(B,num[i-1],sizeof num[i-1]);
        for (int j=0;j<=n;j++) B[j]=1ll*B[j]*nI[j]%mo;
        fft(B,1<<len);
        for (int j=0;j<(1<<len);j++) B[j]=1ll*B[j]*A[j]%mo;
        fft(B,1<<len,-1);
        for (int j=1;j<=n;j++) num[i][j]=1ll*B[j]*two[len]%mo*I[j-1]%mo;
    }
    for (int i=0;i<=n;i++) rem[i]=quick(2,i*(i-1)/2);
    S[0][0]=1;
    for (int i=1;i<=m;i++)
        for (int j=1;j<=i;j++) S[i][j]=(S[i-1][j-1]+1ll*j*S[i-1][j])%mo;
//    for (int i=1;i<=4;i++){
//        for (int j=1;j<=4;j++) cout<<num[i][j]<<" "; cout<<endl;
//    }
    int t; scanf("%d",&t);
    for (;t;t--){
        scanf("%d%d",&n,&m); int ans=0;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++){
                ans=(ans+1ll*S[m][j]*I[j]%mo*num[j][i]%mo*C(n,i)%mo*rem[n-i])%mo;
            }
        printf("%d\n",ans);
    }
    return 0;
}
