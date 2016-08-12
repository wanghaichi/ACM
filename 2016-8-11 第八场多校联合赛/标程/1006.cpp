#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int A[110000],C,n,m;
int main(){
    //freopen("physics.in","r",stdin);
    //freopen("physics.out","w",stdout);
    int t; scanf("%d",&t);
    for (;t;t--){
        scanf("%d%d",&n,&C);
        for (int i=1;i<=n;i++){
            scanf("%d",&A[i]); int k2,k3; scanf("%d%d",&k2,&k3);
        }
        scanf("%d",&m); sort(A+1,A+n+1);
        for (;m;m--){
            int k1,k2; scanf("%d%d",&k2,&k1);
            double t=1ll*A[k1]*A[k1]/2.0/C;
            double ans=sqrt(2ll*C*(t+k2));
            printf("%.3lf\n",ans);
        }
    }
    return 0;
}
