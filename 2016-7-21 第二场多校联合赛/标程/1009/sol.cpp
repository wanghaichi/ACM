#include <bits/stdc++.h>
using namespace std;

void run() {
  int n, m; scanf("%d%d", &n, &m);
  vector<int> a(n, -1);
  for (int i = 0; i < m; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    a[x - 1] = y;
  }
  for (int i = n - 1; i >= 2; --i) if (a[i] == -1) {
    if (i == n - 1) a[i] = 0;
    else a[i] = a[i + 1];
  }
  if (a[0] == -1 && a[1] == -1) a[0] = a[1] = 100;
  else if (a[0] == -1 && a[1] != -1) a[0] = 100;
  else if (a[0] != -1 && a[1] == -1) a[1] = a[0];
  int x = a[0] + a[1], y = accumulate(a.begin(), a.end(), 0);
  int g = __gcd(x, y); x /= g; y /= g;
  printf("%d/%d\n", x, y);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
