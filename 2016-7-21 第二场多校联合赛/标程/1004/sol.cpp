#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

struct FastIO {
  static const int S = 1310720;
  int wpos; char wbuf[S];
  FastIO() : wpos(0) {}
  inline int xchar() {
    static char buf[S];
    static int len = 0, pos = 0;
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, stdin);
    if (pos == len) return -1;
    return buf[pos ++];
  }
  inline int xuint() {
    int c = xchar(), x = 0;
    while (c <= 32) c = xchar();
    for (;'0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
    return x;
  }
  inline int xint() {
    int s = 1, c = xchar(), x = 0;
    while (c <= 32) c = xchar();
    if (c == '-') s = -1, c = xchar();
    for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void xstring(char *s) {
    int c = xchar();
    while (c <= 32) c = xchar();
    for(; c > 32; c = xchar()) *s++ = c;
    *s = 0;
  }
  inline void wchar(int x) {
    if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
    wbuf[wpos ++] = x;
  }
  inline void wint(int x) {
    if (x < 0) wchar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n) s[n ++] = '0' + x % 10, x /= 10;
    while (n--) wchar(s[n]);
  }
  inline void wstring(const char *s) {
    while (*s) wchar(*s++);
  }
  ~FastIO() {
    if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
  }
} io;

const int MAXN = 100000 + 10;
const int MOD = 1e9 + 7;

namespace Storage {
  int data[MAXN << 6], *p;
  void init() {
    p = data;
  }
  int* alloc(int len) {
    p += len;
    return p - len;
  }
}

struct seg_t {
  int *index_left, *index_right;
  int sum, tag;
  void set_tag(int val) {
    tag = val;
    sum = val + 1;
  }
  int go_left(int val) {
    if (~val) return index_left[val];
    else return val;
  }
  int go_right(int val) {
    if (~val) return val = index_right[val];
    else return val;
  }
} tree[MAXN << 2];

int a[MAXN], b[MAXN], c[MAXN], xs[MAXN];
int n, m;

#define lson (rt<<1)
#define rson (rt<<1|1)

inline void update(int rt) {
  tree[rt].sum = tree[lson].sum + tree[rson].sum;
}

inline void push_down(int rt) {
  if (tree[rt].tag != -2) {
    tree[lson].set_tag(tree[rt].go_left(tree[rt].tag));
    tree[rson].set_tag(tree[rt].go_right(tree[rt].tag));
  }
  tree[rt].tag = -2;
}

void build(int rt, int l, int r) {
  tree[rt].tag = -2;
  tree[rt].index_left = Storage::alloc(r - l);
  tree[rt].index_right = Storage::alloc(r - l);
  if (l + 1 == r) {
    tree[rt].sum = a[l] >= b[l];
    return;
  }
  int m = (l + r) >> 1;
  build(lson, l, m);
  build(rson, m, r);
  update(rt);
  int sl = m - l, sr = r - m;
  int *vl = b + l, *vr = b + m;
  int i = 0, j = 0, n = 0;
  while (i < sl && j < sr) {
    if (vl[i] < vr[j]) {
      tree[rt].index_left[n] = i;
      tree[rt].index_right[n] = j - 1;
      c[n++] = vl[i++];
    } else {
      tree[rt].index_left[n] = i - 1;
      tree[rt].index_right[n] = j;
      c[n++] = vr[j++];
    }
  }
  while (i < sl) {
    tree[rt].index_left[n] = i;
    tree[rt].index_right[n] = j - 1;
    c[n++] = vl[i++];
  }
  while (j < sr) {
    tree[rt].index_left[n] = i - 1;
    tree[rt].index_right[n] = j;
    c[n++] = vr[j++];
  }
  memcpy(b + l, c, sizeof(c[0]) * (r - l));
}

void ins(int rt, int l, int r, int L, int R, int val) {
  if (L <= l && R >= r) {
    tree[rt].set_tag(val);
    return;
  }
  push_down(rt);
  int m = (l + r) >> 1;
  if (L < m) ins(lson, l, m, L, R, tree[rt].go_left(val));
  if (R > m) ins(rson, m, r, L, R, tree[rt].go_right(val));
  update(rt);
}

int ask(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) return tree[rt].sum;
  push_down(rt);
  int ret = 0, m = (l + r) >> 1;
  if (L < m) ret += ask(lson, l, m, L, R);
  if (R > m) ret += ask(rson, m, r, L, R);
  return ret;
}

void discretization() {
  for (int i = 0; i < n; ++i) c[i] = i;
  std::sort(c, c + n, [&](int x, int y) {
      return b[x] < b[y];
      });
  for (int i = 0; i < n; ++i) {
    xs[i] = b[c[i]];
    b[c[i]] = i;
  }
  for (int i = 0; i < n; ++i) {
    a[i] = std::upper_bound(xs, xs + n, a[i]) - xs - 1;
  }
}

const int C = ~(1<<31), M = (1<<16)-1;
int rnd(int last, int &a, int &b) {
  a = (36969 + (last >> 3)) * (a & M) + (a >> 16);
  b = (18000 + (last >> 3)) * (b & M) + (b >> 16);
  return (C & ((a << 16) + b)) % 1000000000;
}

void run() {
  n = io.xuint();
  m = io.xuint();
  int A = io.xuint();
  int B = io.xuint();
  for (int i = 0; i < n; ++i) a[i] = io.xuint();
  for (int i = 0; i < n; ++i) b[i] = io.xuint();
  discretization();
  Storage::init();
  build(1, 0, n);
  int last = 0, ret = 0;
  for (int i = 0; i < m; ++i) {
    int l = rnd(last, A, B) % n + 1;
    int r = rnd(last, A, B) % n + 1;
    int x = rnd(last, A, B) + 1;
    if (l > r) std::swap(l, r);
    if ((l + r + x) & 1) {
      x = std::upper_bound(xs, xs + n, x) - xs;
      ins(1, 0, n, l - 1, r, x - 1);
    } else {
      last = ask(1, 0, n, l - 1, r);
      ret += (long long)(i + 1) * last % MOD;
      if (ret >= MOD) ret -= MOD;
    }
  }
  printf("%d\n", ret);
}

int main() {
  int T = io.xuint();
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
