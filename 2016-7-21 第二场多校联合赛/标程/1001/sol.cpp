#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef long long LL;

LL gcd(LL a, LL b) {
  return !b ? a : gcd(b, a % b);
}

void run() {
  int n;
  LL sw = 0, s2w = 0;
  scanf("%d", &n);
  for (int i = 0, w; i < n; ++i) {
    scanf("%d", &w);
    sw += abs(w);
    s2w += w * w;
  }
  LL a = s2w * n - sw * sw, b = n;
  LL g = gcd(a, b);
  printf("%lld/%lld\n", a / g, b / g);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
