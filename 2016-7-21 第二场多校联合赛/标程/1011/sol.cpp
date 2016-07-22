#include <bits/stdc++.h>

void run() {
  int n; scanf("%d", &n);
  int s = 0, s2 = 0, odd = 0;
  for (int i = 0; i < n; ++i) {
    int x; scanf("%d", &x);
    s += x; s2 += x / 2;
    odd += x % 2;
  }
  if (odd) printf("%d\n", s2 / odd * 2 + 1);
  else printf("%d\n", s);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
