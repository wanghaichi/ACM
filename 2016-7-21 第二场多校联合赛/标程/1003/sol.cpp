#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int MAXN = 10000 + 10;

typedef std::pair<int, int> PII;

struct path_t: public std::vector<int> {
  int front_len, back_len, best;
  int opposite(int u) const {return *begin() + back() - u;}
  bool is_ring() const {return back() == *begin();}
  int cost(int u) const {
    if (is_ring()) return std::max(front_len, back_len);
    if (u == *begin()) return front_len;
    else return back_len;
  }
};

inline void upd(int &x, int y) {
  if (y > x) x = y;
}

std::vector<int> edges[MAXN], graph[MAXN], key_nodes;
std::vector<path_t> paths;
std::set<int> visited;
bool is_branch[MAXN];
int mapping[MAXN], deg[MAXN], parent[MAXN];
int height[MAXN][2], dp[1 << 14][10];
int paths_to_nodes[1 << 14], extra[1 << 14];
int n, m;

void dfs(int src, int x, path_t &path) {
  path.push_back(x);
  if (path.size() > 1 && (deg[x] > 2 || src == x)) {
    paths.push_back(path);
  } else {
    for (auto &y: edges[x]) if (!visited.count(x * n + y)) {
      visited.insert(x * n + y);
      visited.insert(y * n + x);
      if (!is_branch[y]) dfs(src, y, path);
    }
  }
  path.pop_back();
}

int calc_chain(path_t &path) {
  int n = path.size(), ret = 0;
  int u = path[0], v = path.back();
  path.front_len = path.back_len = 0;
  if (path.is_ring()) path.best = height[u][0];
  else path.best = height[u][0] + height[v][0];
  std::vector<int> val(n, 0);
  std::priority_queue<int> pq;
  for (int i = 1; i + 1 < n; ++i) {
    val[i] = height[path[i]][0] + i;
    if (!pq.empty()) upd(ret, pq.top() + val[i]);
    upd(path.front_len, val[i]);
    upd(path.back_len, n - i - 1 + height[path[i]][0]);
    upd(val[i], val[i - 1]);
    pq.push(height[path[i]][0] - i);
  }
  for (int i = n - 2, cur = 0; i >= 1; --i) {
    upd(cur, n - 1 - i + height[path[i]][0]);
    upd(path.best, cur + val[i - 1]);
  }
  upd(path.best, height[u][0] + path.back_len);
  upd(path.best, height[v][0] + path.front_len);
  return ret;
}

void reduce() {
  for (int i = 0; i < n; ++i) {
    deg[i] = edges[i].size();
    is_branch[i] = false;
    parent[i] = -1;
    height[i][0] = height[i][1] = 0;
  }
  std::queue<int> Q;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 1) Q.push(i);
  }
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    is_branch[u] = true;
    for (auto &v: edges[u]) if (!is_branch[v]) {
      parent[u] = v;
      if (height[v][0] < height[u][0] + 1) {
        height[v][1] = height[v][0];
        height[v][0] = height[u][0] + 1;
      } else if (height[v][0] == height[u][0] + 1) {
        height[v][1] = height[v][0];
      }
      if (--deg[v] == 1) Q.push(v);
    }
  }
  key_nodes.clear(); paths.clear(); visited.clear();
  path_t tmp_path;
  for (int i = 0; i < n; ++i) if (deg[i] > 2) {
    key_nodes.push_back(i);
    mapping[i] = key_nodes.size() - 1;
    dfs(i, i, tmp_path);
  }
  if (key_nodes.empty()) {
    int root = 0;
    while (is_branch[root]) ++root;
    key_nodes.push_back(root);
    mapping[root] = key_nodes.size() - 1;
    dfs(root, root, tmp_path);
  }
}

void build_graph() {
  for (int i = 0; i < n; ++i) graph[i].clear();
  for (size_t i = 0; i < paths.size(); ++i) {
    int u = mapping[paths[i][0]];
    int v = mapping[paths[i].back()];
    graph[u].push_back(i);
    if (u != v) graph[v].push_back(i);
  }
}

int calc(int src) {
  int s = 1 << m, ret = 0;
  for (int msk = 0; msk < s; ++msk) {
    extra[msk] = height[key_nodes[src]][0];
    for (auto &x: graph[src]) if (!(msk >> x & 1)) {
      upd(extra[msk], paths[x].cost(key_nodes[src]));
    }
    for (int i = 0; i < n; ++i) dp[msk][i] = -1;
  }
  dp[0][src] = 0;
  paths_to_nodes[0] = 1 << src;
  for (int msk = 0; msk < s; ++msk) {
    int node_msk = paths_to_nodes[msk];
    for (int i = 0; i < n; ++i) if (dp[msk][i] != -1) {
      int cost = dp[msk][i], idx = key_nodes[i];
      if (i != src) {
        upd(ret, cost + height[idx][0] + extra[msk]);
      }
      for (auto &y: graph[i]) if (!(msk >> y & 1)) {
        int j = mapping[paths[y].opposite(idx)], new_msk = msk | (1 << y);
        if (j == src) upd(ret, cost + paths[y].best);
        upd(ret, cost + extra[new_msk] + paths[y].cost(idx));
        if (node_msk >> j & 1) continue;
        if (paths[y].is_ring()) upd(dp[new_msk][j], paths[y].cost(idx));
        else upd(dp[new_msk][j], cost + paths[y].size() - 1);
      }
    }
  }
  return ret;
}

void run() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) edges[i].clear();
  for (int i = 0; i < m; ++i) {
    int u, v; scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  reduce();
  int ret = 0;
  for (int i = 0; i < n; ++i) upd(ret, height[i][0] + height[i][1]);
  for (auto &path: paths) upd(ret, calc_chain(path));
  n = key_nodes.size(), m = paths.size();
  for (int msk = 0; msk < (1 << m); ++msk) {
    paths_to_nodes[msk] = 0;
    for (int i = 0; i < m; ++i) if (msk >> i & 1) {
      paths_to_nodes[msk] |= 1 << mapping[paths[i][0]];
      paths_to_nodes[msk] |= 1 << mapping[paths[i].back()];
    }
  }
  build_graph();
  for (int i = 0; i < n; ++i) {
    upd(ret, calc(i));
  }
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
