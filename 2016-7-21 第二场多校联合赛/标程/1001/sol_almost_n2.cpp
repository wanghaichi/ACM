#include <bits/stdc++.h>
const int N = 1010;
int g[N][N];

int gcd(int a, int b) {
  if (!a) return b;
  if (!b) return a;
  if (b < N) return g[b][a % b];
  if (a < N) return g[a][b % a];
  return gcd(b, a % b);
}

void run() {
  int n; scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ret = std::max(ret, gcd(a[i], a[j]));
    }
  }
  printf("%d\n", ret);
}

int main() {
  for (int i = 0; i < N; ++i) g[i][0] = g[0][i] = i;
  for (int i = 1; i < N; ++i) {
    for (int j = 1; j <= i; ++j) g[i][j] = g[j][i] = g[i - j][j];
  }
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
