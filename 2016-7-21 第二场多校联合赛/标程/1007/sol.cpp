#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

const int MAXN = 500 + 10, SIZE = MAXN * MAXN;
const int inf = 1e9;

struct KM {
  typedef int VAL;
  VAL lx[MAXN],ly[MAXN],sl[MAXN];
  int px[MAXN],py[MAXN],sy[MAXN],fa[MAXN],n;
  void aug(int v) {
    sy[v]=py[v]; if (px[sy[v]]!=-2) aug(px[sy[v]]);
  }
  bool find(int v, const VAL w[][MAXN]) {
    for (int i=0;i<n;++i) if (!~py[i]) {
      if (sl[i]>lx[v]+ly[i]-w[v][i]) {
        sl[i]=lx[v]+ly[i]-w[v][i]; fa[i] = v;
      }
      if (lx[v]+ly[i]==w[v][i]) {
        py[i]=v; if (!~sy[i]) {aug(i); return 1;}
        if (~px[sy[i]]) continue;
        px[sy[i]]=i; if (find(sy[i],w)) return 1;
      }
    }
    return 0;
  }
  VAL gao(int _n, const VAL w[][MAXN], VAL m=inf) {
    n=_n; std::fill(sy,sy+n,-1); std::fill(ly,ly+n,0);
    for (int i=0;i<n;++i) lx[i]=*std::max_element(w[i],w[i]+n);
    for (int i(0),flag;i<n;++i) {
      for (int j=0;j<n;++j)px[j]=py[j]=-1,sl[j]=inf;
      px[i]=-2; if (find(i,w)) continue;
      for (flag=0,m=inf; !flag; m=inf) {
        for (int j=0;j<n;++j) if (!~py[j]) m=std::min(m,sl[j]);
        for (int j=0;j<n;++j) {
          if (~px[j]) lx[j]-=m;
          if (~py[j]) ly[j]+=m;
          else sl[j]-=m;
        }
        for (int j=0;j<n;++j) if (!~py[j]&&!sl[j]) {
          py[j]=fa[j]; if (!~sy[j]) {aug(j);flag=1;break;}
          px[sy[j]]=j; if (find(sy[j],w)) {flag=1;break;}
        }
      }
    }
    VAL ret(0);
    for (int i=0;i<n;++i) ret+=w[sy[i]][i];
    return ret;
  }
} km;

char col[MAXN];
std::vector<int> G[MAXN];
std::vector<int> path[MAXN][MAXN];
int dis[MAXN][MAXN];
int mark[MAXN];
int n, m;

void bfs(int s) {
  for (int i = 1; i <= n; ++i) {
    dis[s][i] = -1;
    path[s][i].clear();
  }
  std::queue<int> Q;
  Q.push(s);
  dis[s][s] = 0;
  path[s][s].push_back(s);
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (auto &v: G[u]) if (dis[s][v] == -1) {
      path[s][v] = path[s][u];
      path[s][v].push_back(v);
      dis[s][v] = dis[s][u] + 1;
      Q.push(v);
    }
  }
}

int min_steps;
std::pair<int, int> moves[SIZE];
std::vector<int> X, Y;

bool bicolor(int u, int c) {
  if (mark[u] != -1) return mark[u] == c;
  mark[u] = c;
  if (!c) X.push_back(u);
  else Y.push_back(u);
  for (auto &v: G[u]) {
    if (!bicolor(v, c ^ 1)) return false;
  }
  return true;
}

int weight[MAXN][MAXN];
int mate1[MAXN], mate2[MAXN];

int get_cost(std::vector<int> &X, std::vector<int> &Y, int *mate) {
  std::vector<int> left, right;
  for (auto &v: X) {
    if (col[v] == '1') left.push_back(v);
  }
  for (auto &v: Y) {
    if (col[v] == '0') right.push_back(v);
  }
  assert(left.size() == right.size());
  int n = left.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      weight[i][j] = -dis[right[i]][left[j]];
    }
  }
  int cost = -km.gao(n, weight);
  int tmp = 0;
  for (int i = 0; i < n; ++i) {
    int u = left[i], v = right[km.sy[i]];
    mate[u] = v; mate[v] = u;
    tmp += dis[u][v];
  }
  assert(tmp == cost);
  return cost;
}

void build_moves(int u, int v) {
  if (col[u] == '1') std::swap(u, v);
  std::vector<int> &p = path[u][v];
  for (size_t i = 0, j; i < p.size(); i = j) {
    for (j = i; j < p.size() && col[p[j]] == '0'; ++j);
    if (j == p.size()) break;
    for (int k = j; k > i; --k) {
      moves[min_steps++] = std::make_pair(p[k], p[k - 1]);
      std::swap(col[p[k]], col[p[k - 1]]);
    }
  }
}

bool solve(int s) {
  X.clear(); Y.clear();
  if (!bicolor(s, 0)) return false;
  int one = 0, zero = 0;
  for (auto &v: X) {
    if (col[v] == '1') one++;
    else zero++;
  }
  for (auto &v: Y) {
    if (col[v] == '1') one++;
    else zero++;
  }
  int cost1 = inf, cost2 = inf;
  int *mate;
  if (X.size() == zero) {
    cost1 = get_cost(X, Y, mate1);
  }
  if (Y.size() == zero) {
    cost2 = get_cost(Y, X, mate2);
  }
  if (cost1 == inf && cost2 == inf) return false;
  if (cost1 < cost2) mate = mate1;
  else mate = mate2;
  for (auto &u: X) if (mate[u] != -1) {
    build_moves(u, mate[u]);
  }
  return true;
}

void run() {
  scanf("%d%d", &n, &m);
  scanf("%s", col + 1);
  for (int i = 1; i <= n; ++i) G[i].clear();
  for (int i = 0; i < m; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) bfs(i);
  bool flag = true;
  min_steps = 0;
  for (int i = 1; i <= n; ++i) {
    mate1[i] = mate2[i] = mark[i] = -1;
  }
  for (int i = 1; i <= n && flag; ++i) {
    if (mark[i] == -1) flag &= solve(i);
  }
  if (!flag) puts("-1");
  else {
    printf("%d\n", min_steps);
    for (int i = 0; i < min_steps; ++i) {
      printf("%d %d\n", moves[i].first, moves[i].second);
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
