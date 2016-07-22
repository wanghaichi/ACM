#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int MAXN = 1000 + 10, MOD = 1e9 + 7;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  bool operator < (const Point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  bool operator == (const Point &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  void reduce() {
    int g = std::__gcd(abs(x), abs(y));
    if (g) x /= g, y /= g;
  }
} P[MAXN], Q[MAXN];

int pw[MAXN], n;

void update(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

void run() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &P[i].x, &P[i].y);
  }
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = 2 * pw[i - 1] % MOD;
  }
  std::sort(P, P + n);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int m = 0, cnt = 0;
    for (int j = i + 1; j < n; ++j) {
      if (P[j] == P[i]) ++cnt;
      else Q[m++] = P[j] - P[i];
    }
    for (int j = 0; j < m; ++j) Q[j].reduce();
    std::sort(Q, Q + m);
    update(ret, pw[cnt] - 1);
    for (int x = 0, y; x < m; x = y) {
      for (y = x; y < m && Q[x] == Q[y]; ++y);
      update(ret, 1ll * pw[cnt] * (pw[y - x] - 1) % MOD);
    }
  }
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
