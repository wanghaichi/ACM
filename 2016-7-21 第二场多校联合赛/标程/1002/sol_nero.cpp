#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int MOD = (int)1e9 + 7;
const int N = (1 << 16) + 5;
char op[4];
int n;
int weight[N];
std::vector<int> edges[N];

unsigned opt(unsigned a,unsigned b) {
    if (op[0] == 'A') return a & b;
    if (op[0] == 'O') return a | b;
    return a ^ b;
}

unsigned dp[1 << 8][1 << 8];
unsigned backup[N][1 << 8];
unsigned result[N];

template<typename T>
T _max(T &a,T b) {
    if (a == -1 || a < b) a = b;
}

void dfs(int u) {
    unsigned val = 0;
    int a = weight[u] >> 8,b = weight[u] & 255;
    for (int i = 0; i < 256; ++ i) {
        if (dp[i][b] != -1)
            _max(val,dp[i][b] + opt(a,i) * 256);
    }
    result[u] = val + weight[u];
    std::copy(dp[a],dp[a] + 256,backup[u]);
    for (int i = 0; i < 256; ++ i) {
        _max(dp[a][i],val + opt(i,b));
    }
    for (int v : edges[u]) {
        dfs(v);
    }
    std::copy(backup[u],backup[u] + 256,dp[a]);
}

unsigned work() {
    memset(dp,-1,sizeof(dp));
    dfs(0);
    unsigned ret = 0;
    for (int i = 0; i < n; ++ i) {
        ret = (ret + (i + 1) * 1ll * result[i]) % MOD;
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%s",&n,op);
        for (int i = 0; i < n; ++ i) {
            scanf("%d",weight + i);
            edges[i].clear();
        }
        for (int i = 1; i < n; ++ i) {
            int x;
            scanf("%d",&x); -- x;
            edges[x].push_back(i);
        }
        printf("%u\n",work());
    }
}
