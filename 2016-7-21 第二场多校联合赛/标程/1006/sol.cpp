#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

class Solution {
  static const int MAXN = 200000 + 10, M = 1e9 + 7;
  class Articulation {
  public:
    std::vector<int> keyV, bcc[MAXN];
    int cnt;
    int gao(int n, const std::vector<int> e[]) {
      memset(tag, use = 0, sizeof(tag[0]) * n);
      memset(low, cnt = 0, sizeof(low[0]) * n);
      std::fill_n(bcc, n, keyV = std::vector<int>());
      for (int i = 0; i < n; ++i) if (!tag[i]) dfs(i, 1, e);
      return cnt;
    }
  private:
    int tag[MAXN], low[MAXN], dot[MAXN], use;
    void dfs(int x, int dep, const std::vector<int> e[]) {
      int src = 0, out = 1 < dep; dot[use++] = x;
      tag[x] = low[x] = dep;
      for (auto &y: e[x]) {
        if (!tag[y]) {
          dfs(y, dep + 1, e);
          low[x] = std::min(low[x], low[y]);
          if (low[y] >= tag[x]) {
            if (++out == 2) keyV.push_back(x);
            while (dot[--use] != y) bcc[dot[use]].push_back(cnt);
            bcc[x].push_back(cnt); bcc[y].push_back(cnt++);
          }
        } else if (tag[y] != tag[x] - 1 || src++) {
          low[x] = std::min(low[x], tag[y]);
        }
      }
    }
  } bcc;
  std::vector<int> G[MAXN], now;
  int w[MAXN], vs[MAXN], sub[MAXN];
  int z[MAXN], dp[MAXN], sum[MAXN];
  int n, m;
  int pm(int a, int n) {
    int r = 1;
    for (; n; n >>= 1) {
      if (n & 1) r = 1ll * r * a % M;
      a = 1ll * a * a % M;
    }
    return r;
  }
  int inv(int x) {return pm(x, M - 2);}
  void upd(int &x, int y) {
    x += y; if (x >= M) x -= M;
  }
  void dfs1(int u, int f = -1) {
    dp[u] = w[u]; sum[u] = 0;
    vs[u] = 1; now.push_back(u);
    for (auto &v: G[u]) if (v != f) {
      dfs1(v, u); upd(sum[u], dp[v]);
      dp[u] = 1ll * dp[u] * dp[v] % M;
    }
  }
  void dfs2(int u, int f = -1) {
    if (f == -1) z[u] = sum[u];
    for (auto &v: G[u]) if (v != f) {
      z[v] = sum[v];
      upd(z[v], 1ll * inv(dp[v]) * sub[v] % M);
      dfs2(v, u);
    }
  }

public:
  void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", w + i);
    for (int i = 0; i < n; ++i) G[i].clear();
    for (int i = 0; i < m; ++i) {
      int u, v; scanf("%d%d", &u, &v);
      G[u - 1].push_back(v - 1);
      G[v - 1].push_back(u - 1);
    }
    bcc.gao(n, G);
    for (int i = 0; i < n + bcc.cnt; ++i) {
      if (i >= n) w[i] = 1; G[i].clear();
      vs[i] = z[i] = 0;
    }
    for (int u = 0; u < n; ++u) {
      for (auto &v: bcc.bcc[u]) {
        G[u].push_back(v + n);
        G[v + n].push_back(u);
      }
    }
    int tot = 0;
    for (int i = 0; i < n; ++i) if (!vs[i]) {
      now.clear(); dfs1(i); upd(tot, dp[i]);
      for (auto &v: now) sub[v] = dp[i];
      dfs2(i);
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      upd(z[i], (tot + M - sub[i]) % M);
      upd(ret, 1ll * (i + 1) * z[i] % M);
    }
    printf("%d\n", ret);
  }
} sol;

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) sol.solve();
  return 0;
}
