#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 100000 + 5;
int n,A[N];

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        int count = 0,pair = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
            if (A[i] & 1) count ++;
            pair += A[i] >> 1;
        }
        if (count == 0) {
            printf("%d\n",pair << 1);
            continue;
        } else {
            printf("%d\n",1 + 2 * (pair / count));
        }
    }
}
