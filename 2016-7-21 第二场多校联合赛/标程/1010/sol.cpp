#include <bits/stdc++.h>
typedef long long LL;
const int MAXN = 50, M = 1e9 + 7;

int dsu[MAXN], val[MAXN], cnt[MAXN];
int x[MAXN], y[MAXN], oe[MAXN][2];
int py[MAXN], rk[MAXN];
int lex[MAXN], cur[MAXN];
int n, m;

int f[MAXN][2], g[MAXN][2];

int get(int x) {
  if (x == dsu[x]) return x;
  int f = dsu[x];
  dsu[x] = get(dsu[x]);
  val[x] ^= val[f];
  return dsu[x];
}

void upd(int &x, int y) {
  x += y; if (x >= M) x -= M;
}

inline bool cmp(int a[], int b[]) {
  for (int i = 0; i < n; ++i) {
    if (a[i] > b[i]) return true;
    if (a[i] < b[i]) return false;
  }
  return false;
}

void run() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n; ++i) dsu[i] = i, val[i] = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", x + i, y + i);
    oe[i][0] = y[i] / 2 - x[i] / 2 + !(x[i] & 1);
    oe[i][1] = (y[i] + 1) / 2 - (x[i] + 1) / 2 + (x[i] & 1);
    assert(oe[i][0] + oe[i][1] == y[i] - x[i] + 1);
  }
  bool flag = true;
  for (int i = 0; i < m; ++i) {
    int l, r, s; scanf("%d%d%d", &l, &r, &s); --l;
    if (!flag) continue;
    int u = get(l), v = get(r);
    if (u == v) flag &= (s == (val[l] ^ val[r]));
    else {
      if (u > v) std::swap(u, v);
      dsu[u] = v;
      val[u] = val[l] ^ val[r] ^ s;
    }
  }
  if (!flag) {
    puts("0\n-1");
    return;
  }
  for (int i = 0; i <= n; ++i) cnt[i] = 0;
  for (int i = 0; i <= n; ++i) ++cnt[get(i)];
  std::vector<int> group;
  for (int i = 0; i <= n; ++i) rk[i] = -1;
  for (int i = 0; i < n; ++i) {
    if (cnt[i] > 1) {
      rk[i] = group.size();
      group.push_back(i);
    }
  }
  assert(group.size() <= 20);
  std::cerr << group.size() << std::endl;
  int total = 1 << group.size();
  long long ret = 0;
  py[n] = 0;
  for (int i = 0; i <= n; ++i) lex[i] = 2e9;
  for (int msk = 0; msk < total; ++msk) {
    for (int i = 0; i < n; ++i) if (cnt[i]) {
      if (cnt[i] == 1) py[i] = -1;
      else py[i] = msk >> rk[i] & 1;
    }
    for (int i = 0; i < n; ++i) {
      if (!cnt[i]) py[i] = val[i] ^ py[dsu[i]];
      f[i][0] = f[i][1] = 0;
      g[i][0] = g[i][1] = -1;
    }
    f[n][0] = 1; f[n][1] = 0;
    g[n][0] = 0; g[n][1] = -1;
    for (int i = n; i >= 0; --i) {
      if (py[i] != -1) g[i][py[i] ^ 1] = -1, f[i][py[i] ^ 1] = 0;
      for (int o = 0; o < 2 && i; ++o) if (g[i][o] != -1) {
        for (int e = x[i]; e <= y[i] && e <= x[i] + 1; ++e) {
          int &r = g[i - 1][(e & 1) ^ o];
          upd(f[i - 1][(e & 1) ^ o], 1ll * f[i][o] * oe[i][e & 1] % M);
          if (r == -1 || r > e) r = e;
        }
      }
    }
    ret += f[0][0] + f[0][1];
    if (g[0][0] == -1 && g[0][1] == -1) continue;
    for (int i = 0; i < n; ++i) {
      if (g[i][0] == g[i][1]) cur[i] = g[i][0];
      else {
        int e = -1;
        for (int o = 0; o < 2; ++o) if (g[i][o] != -1) {
          if (e == -1 || g[i][e] > g[i][o]) e = o;
        }
        for (; i < n; ++i) {
          cur[i] = g[i][e];
          e ^= cur[i] & 1;
        }
      }
    }
    if (cmp(lex, cur)) memcpy(lex, cur, sizeof(cur[0]) * n);
  }
  ret %= M;
  printf("%d\n", ret);
  if (lex[0] == 2e9) puts("-1");
  else {
    for (int i = 0; i < n; ++i) {
      printf("%d%c", lex[i], " \n"[i == n - 1]);
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
