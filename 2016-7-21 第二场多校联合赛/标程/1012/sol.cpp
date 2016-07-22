#include <bitset>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAXN = 100000 + 10, M = 5000;
std::bitset<M> res[3], tmp[3];
std::bitset<M> D[26], L[26], R[26];
char s[MAXN], p[MAXN], ret[MAXN];

void run() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s%s", s, p);
  for (int i = 0; i < 26; ++i) D[i].reset();
  for (int i = 0; i < m; ++i) D[p[i] - 'a'][i] = 1;
  for (int i = 0; i < 26; ++i) {
    L[i] = D[i] << 1;
    R[i] = D[i] >> 1;
  }
  res[0].reset();
  res[1].reset();
  res[2].reset();
  for (int i = 0; i < n; ++i) ret[i] = '0';
  for (int i = 0; i < n; ++i) {
    int o = s[i] - 'a';
    tmp[0] = (res[2] << 1);
    tmp[1] = (res[1] << 1) | (res[0] << 1);
    tmp[1][0] = tmp[0][0] = 1;
    tmp[2] = tmp[1];
    res[0] = tmp[0] & L[o];
    res[1] = tmp[1] & D[o];
    res[2] = tmp[2] & R[o];
    if (res[1][m - 1] || res[0][m - 1]) ret[i - m + 1] = '1';
  }
  ret[n] = 0;
  printf("%s\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}