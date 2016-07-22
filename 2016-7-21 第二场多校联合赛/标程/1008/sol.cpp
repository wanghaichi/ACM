#include <set>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>

const int MAXN = 1000 + 10, SIZE = MAXN * MAXN;
const int inf = 2e9;

typedef std::pair<int, int> ind_t;

int runs[MAXN];
int n, m;

ind_t low[SIZE], upp[SIZE];
int low_cnt, upp_cnt;

void run() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", runs + i);
  }
  low_cnt = 0, upp_cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x = 0, y = 0;
    for (int j = i; j < n; ++j) {
      if (j % 2 == 0) x += runs[j];
      else y += runs[j];
      if (i % 2 == 0 && j % 2 == 0) {
        low[low_cnt++] = ind_t(x, y);
      }
      if (i % 2 == 1 && j % 2 == 1) {
        upp[upp_cnt++] = ind_t(x, y);
      }
    }
  }
  std::sort(low, low + low_cnt); n = 0;
  for (int i = 0, j; i < low_cnt; i = j) {
    for (j = i; j < low_cnt && low[i].first == low[j].first; ++j);
    while (n > 0 && low[n - 1].second >= low[i].second) --n;
    low[n++] = low[i];
  }
  low_cnt = n;
  std::sort(upp, upp + upp_cnt); n = 0;
  for (int i = 0, j; i < upp_cnt; i = j) {
    for (j = i; j < upp_cnt && upp[i].first == upp[j].first; ++j);
    if (!n || upp[n - 1].second < upp[j - 1].second) {
      upp[n++] = upp[j - 1];
    }
  }
  upp_cnt = n;
  static char ret[SIZE];
  for (int i = 0; i < m; ++i) {
    int a, b; scanf("%d%d", &a, &b);
    int x = std::upper_bound(upp, upp + upp_cnt, ind_t(a, +inf)) - upp;
    int y = std::upper_bound(low, low + low_cnt, ind_t(a, -inf)) - low;
    ret[i] = '0' + (y < low_cnt && upp[x - 1].second >= b && low[y].second <= b);
  }
  ret[m] = 0;
  puts(ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
