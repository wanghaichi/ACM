#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 40 + 5;
const int MOD = (int)1e9 + 7;
int n,m;
std::vector<int> edges[N];
LL rel[N][2];
int X[N],Y[N];
int cnt[N][2];
int dp[N][2];

void show(LL mask) {
    for (int i = 0; i <= n; ++ i) {
        printf("%d",mask >> i & 1);
    }
    putchar(' ');
            
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int search(int at,LL odd,LL visited) {
    if (at != 0) {
        dp[at][0] = dp[at][1] = 0;
        for (int i = 0; i < 2; ++ i) {
            if ((visited >> at - 1 & 1) && (odd >> at - 1 & 1) != i) continue;
            for (int j = 0; j < 2; ++ j) {
                add(dp[at][i ^ j],dp[at - 1][i] * 1ll * cnt[at][j] % MOD);
            }
        }
    }

    int ret = 0;

    if (at == n + 1) {
        for (int i = 0; i < 2; ++ i) {
            if ((visited >> at - 1 & 1) && (odd >> at - 1 & 1) != i) continue;
            add(ret,dp[at - 1][i]);
        }
        return ret;
    }
    if (edges[at].empty() || (visited >> at & 1)) {
        return search(at + 1,odd,visited);
    }

    add(ret,search(at + 1,odd | rel[at][1],visited | rel[at][0] | rel[at][1]));
    add(ret,search(at + 1,odd | rel[at][0],visited | rel[at][0] | rel[at][1]));
    return ret;
}

void work() {
    memset(rel,0,sizeof(rel));
    for (int source = 0; source <= n; ++ source) {
        std::vector<int> vis(n + 1,-1);
        vis[source] = 0;
        std::queue<int> que;
        que.push(source);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            rel[source][vis[u]] |= 1ll << u;
            for (int t : edges[u]) {
                int v = t >> 1;
                int s = t & 1;
                if (vis[v] != -1) {
                    if (vis[v] != vis[u] ^ s) {
                        printf("0\n-1\n");
                        return ;
                    }
                } else {
                    vis[v] = vis[u] ^ s;
                    que.push(v);
                }
            }
        }
    }
    for (int i = 0; i <= n; ++ i) {
        cnt[i][X[i] & 1] = (Y[i] - X[i]) / 2 + 1;
        cnt[i][X[i] & 1 ^ 1] = Y[i] - X[i] + 1 - cnt[i][X[i] & 1];
    }
    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    int ways = search(0,0,0);
    if (ways == 0) {
        printf("0\n-1\n");
        return ;
    }
    printf("%d\n",ways);
    std::vector<int> result;
    LL odd = 0,visited = 0;
    int prefix = 0;
    for (int i = 0; i <= n; ++ i) {
        //show(odd),show(visited),printf("%d\n",prefix);
        if (visited >> i & 1) {
            int x = X[i];
            while ((x ^ (odd >> i) ^ prefix) & 1) ++ x;
            result.push_back(x);
            prefix ^= x & 1;
            continue;
        }
        int x = X[i];
        if (search(0,odd | rel[i][(x ^ prefix) & 1 ^ 1],visited | rel[i][0] | rel[i][1]) == 0) ++ x;
        result.push_back(x);
        odd |= rel[i][(x ^ prefix) & 1 ^ 1];
        prefix ^= x & 1;
        visited |= rel[i][0] | rel[i][1];
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%d%c",result[i]," \n"[i == n]);
    }
}

int main() {
    srand(time(NULL));
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d",X + i,Y + i);
        }
        for (int i = 0; i <= n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int l,r,s;
            scanf("%d%d%d",&l,&r,&s); l --;
            edges[l].push_back(r << 1 | s);
            edges[r].push_back(l << 1 | s);
        }
        work();
    }
}
