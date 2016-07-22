#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 100 + 5;
int A[N],n,B[N];
int m;

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        memset(A,-1,sizeof(A));
        for (int i = 0; i < m; ++ i) {
            int x,y;
            scanf("%d%d",&x,&y);
            A[x] = y;
        }
        for (int i = n; i >= 1; -- i) {
            if (A[i] != -1) B[i] = A[i];
            else {
                if (i == n) B[i] = 0;
                else B[i] = B[i + 1];
            }
        }
        if (A[1] == -1) B[1] = 100;
        if (A[2] == -1) B[2] = B[1];
        int a = B[1] + B[2];
        int b = std::accumulate(B + 1,B + n + 1,0);
        int g = gcd(a,b);
        printf("%d/%d\n",a / g,b / g);
    }
}
