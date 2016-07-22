#include <cstdio>
#include <cassert>
#include <algorithm>
const int MAXN = 2000 + 10;

struct pos_t {
  int r, c;
  pos_t() {}
  pos_t(int _r, int _c): r(_r), c(_c) {}
  bool operator < (const pos_t &rhs) const {
    return r < rhs.r || (r == rhs.r && c < rhs.c);
  }
};

struct list_t {
  int val, prev, next;
  list_t() {}
  list_t(int _val, int _prev, int _next): val(_val), prev(_prev), next(_next) {}
} pts[MAXN];

int perm[4], sum[MAXN][MAXN];
int index[MAXN], pos[MAXN];
pos_t one[MAXN];

bool cmpByCol(int a, int b) {
  return one[a].c < one[b].c || (one[a].c == one[b].c && one[a].r < one[b].r);
}
bool cmpByRow(int a, int b) {
  return one[a].r < one[b].r || (one[a].r == one[b].r && one[a].c < one[b].c);
}

inline void remove(int x) {
  int y = pts[x].prev, z = pts[x].next;
  pts[z].prev = y;
  if (y != -1) pts[y].next = z;
}

inline int subms(int x1, int x2, int y1, int y2) {
  return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}

void run() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < 4; ++i) {
    scanf("%d", perm + i);
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      sum[i][j] = 0;
    }
  }
  for (int i = 0; i < k; ++i) {
    scanf("%d%d", &one[i].r, &one[i].c);
    sum[one[i].r][one[i].c] = 1;
    index[i] = i;
  }
  std::sort(one, one + k);
  std::sort(index, index + k, cmpByCol);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  }
  int up = 0, down = 0;
  for (int i = 0; i < 4; ++i) {
    up += perm[i] > std::max(perm[0], perm[3]);
    down += perm[i] < std::min(perm[0], perm[3]);
  }
  int ret = 0;
  for (int i = 0; i < k; ++i) {
    int sz = 0;
    for (int j = 0; j < k; ++j) {
      if (one[index[j]].r >= one[i].r) {
        pts[sz] = list_t(index[j], sz - 1, sz + 1);
        pos[index[j]] = sz++;
      }
    }
    for (int j = k - 1; one[j].r > one[i].r; --j) {
      if ((perm[0] - perm[3]) * (one[i].c - one[j].c) <= 0) {
        remove(pos[j]);
        continue;
      }
      static int box[4], cur, z;
      box[0] = i, box[1] = j, cur = 2;
      if (perm[0] > perm[3]) z = pos[i];
      else z = pos[j];
      int x1 = one[i].r, x2 = one[j].r;
      int y1 = std::min(one[i].c, one[j].c);
      int y2 = std::max(one[i].c, one[j].c);
      for (int h = 0; h < up && pts[z].next < sz; ++h) {
        z = pts[z].next;
        box[cur++] = pts[z].val;
        y2 = one[pts[z].val].c;
      }
      if (perm[0] < perm[3]) z = pos[i];
      else z = pos[j];
      for (int h = 0; h < down && pts[z].prev >= 0; ++h) {
        z = pts[z].prev;
        box[cur++] = pts[z].val;
        y1 = one[pts[z].val].c;
      }
      if (subms(x1, x2, y1, y2) != 4 || cur != down + up + 2) {
        remove(pos[j]);
        continue;
      }
      int rest = 2 - up - down;
      if (perm[0] > perm[3]) z = pos[i];
      else z = pos[j];
      for (int h = 0; h < rest && pts[z].prev >= 0; ++h) {
        z = pts[z].prev;
        box[cur++] = pts[z].val;
      }
      if (cur == 4) {
        std::sort(box, box + 4, cmpByRow);
        bool flag = true;
        for (int i = 0; i < 3; ++i) flag &= one[box[i]].r < one[box[i + 1]].r;
        for (int x = 0; x < 4 && flag; ++x) {
          for (int y = x + 1; y < 4; ++y) {
            flag &= (perm[x] - perm[y]) * (one[box[x]].c - one[box[y]].c) > 0;
          }
        }
        ret += flag;
        //if (flag) fprintf(stderr, "%d %d %d %d\n", x1, x2, y1, y2);
      }
      remove(pos[j]);
    }
  }
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
