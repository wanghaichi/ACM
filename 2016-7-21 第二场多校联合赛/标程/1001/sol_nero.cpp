#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

int A[2000],n;

const int N = 1000000 + 5;
std::vector<int> prime;
int mindiv[N];

void get_prime(int n) {
    std::vector<bool> doge(n + 1);
    for (int i = 2; i <= n; ++ i) {
        if (!doge[i]) {
            mindiv[i] = i;
            prime.push_back(i);
        }
        for (int x : prime) {
            if (i * x > n) break;
            doge[i * x] = true;
            mindiv[i * x] = x;
            if (i % x == 0) break;
        }
    }
}

int result;
int cnt[N];
std::vector<std::pair<int,int>> ps;

void search(int at,int val,int dt) {
    if (at == ps.size()) {
        cnt[val] += dt;
        if (cnt[val] >= 2 && result < val) result = val;
        return ;
    }
    for (int i = 0; i <= ps[at].second; ++ i) {
        search(at + 1,val,dt);
        val *= ps[at].first;
    }
}

void r(int n,int dt) {
    ps.clear();
    while (n > 1) {
        int x = mindiv[n];
        int c = 0;
        while (n % x == 0) n /= x,c ++;
        ps.emplace_back(x,c);
    }
    search(0,1,dt);
}

int main() {
    get_prime(1000000);
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        result = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d",&A[i]);
            r(A[i],1);
        }
        for (int i = 0; i < n; ++ i) {
            r(A[i],-1);
        }
        printf("%d\n",result);
    }
}
