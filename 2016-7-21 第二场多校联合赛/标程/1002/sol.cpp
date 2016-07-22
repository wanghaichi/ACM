#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef unsigned int uint;

const int MAXN = 1 << 16, S = 1 << 8;
const int MOD = 1e9 + 7;

std::vector<int> edges[MAXN];
uint weight[MAXN], pool[MAXN + S][S], f[MAXN];
int n, op, sz;

uint* new_array(uint* src = NULL) {
  if (src == NULL) {
    memset(pool[sz], -1, sizeof(uint) * S);
  } else {
    memcpy(pool[sz], src, sizeof(uint) * S);
  }
  return pool[sz++];
}

uint opt(uint x, uint y) {
  if (op == 0) return x & y;
  if (op == 1) return x | y;
  return x ^ y;
}

void ins(uint x, uint v, uint* f[S]) {
  uint a = x >> 8, b = x & 255;
  for (int i = 0; i < S; ++i) {
    uint w = v + opt(i, b);
    if (f[a][i] == -1 || w > f[a][i]) f[a][i] = w;
  }
}

uint ask(uint x, uint* f[S], uint ret = 0) {
  uint a = x >> 8, b = x & 255;
  for (int i = 0; i < S; ++i) if (f[i][b] != -1) {
    uint w = f[i][b] + (opt(a, i) << 8);
    if (w > ret) ret = w;
  }
  return ret;
}

void dfs(int u, uint* dp[S]) {
  uint* backup = dp[weight[u] >> 8];
  dp[weight[u] >> 8] = new_array(backup);
  ins(weight[u], f[u], dp);
  for (auto &v: edges[u]) {
    f[v] = ask(weight[v], dp);
    dfs(v, dp);
  }
  dp[weight[u] >> 8] = backup;
}

void run() {
  char str[10];
  scanf("%d%s", &n, str);
  op = str[0] == 'X' ? 2 : (str[0] == 'O');
  for (int i = 0; i < n; ++i) {
    edges[i].clear();
    scanf("%u", weight + i);
  }
  for (int i = 1, parent; i < n; ++i) {
    scanf("%d", &parent);
    edges[parent - 1].push_back(i);
  }
  f[0] = sz = 0;
  uint* dp[S];
  for (int i = 0; i < S; ++i) {
    dp[i] = new_array();
  }
  dfs(0, dp);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    f[i] += weight[i];
    ret += 1ll * (i + 1) * f[i] % MOD;
    if (ret >= MOD) ret -= MOD;
  }
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
}
