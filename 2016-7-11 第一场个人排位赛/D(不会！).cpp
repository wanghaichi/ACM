#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define N 200003

vector<int>V[N];
int dp[N][21];
int ans, n;

void dfs(int u) {
    int i, v, k, j;
    for (i = 0;i < V[u].size();i++) {
        v = V[u][i];
        dfs(v);
    }
    for (i = 1;i < 21;i++) {
        dp[u][i] = i;
        for (j = 0;j < V[u].size();j++) {
            v = V[u][j];
            int mi = 20*n;
            for (k = 1;k < 21;k++) {
                if (k == i) continue;
                mi = min(mi, dp[v][k]);
            }
            dp[u][i] += mi;
        }
    }
}

int main() {
    int T, ca = 1, i, j;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (i = 1;i <= n;i++) V[i].clear();
        memset(dp, 0, sizeof(dp));
        for (i = 1;i <= n;i++) {
            scanf("%d", &j);
            V[j].push_back(i);
        }
        ans = 20*n;
        dfs(1);
        for (i = 1;i < 21;i++) {
            ans = min(ans, dp[1][i]);
        }
        printf("Case #%d: %d\n", ca++, ans);
    }
}
