#include <bits/stdc++.h>
const int MAXN = 1000000 + 10;
int cnt[MAXN];

void run() {
  int n; scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int mx = *std::max_element(a.begin(), a.end());
  for (int i = 1; i <= mx; ++i) cnt[i] = 0;
  for (int i = 0; i < n; ++i) cnt[a[i]]++;
  for (int ret = mx; ret >= 1; --ret) {
    int sum = 0;
    for (int i = ret; i <= mx; i += ret) sum += cnt[i];
    if (sum > 1) {
      printf("%d\n", ret);
      return;
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
