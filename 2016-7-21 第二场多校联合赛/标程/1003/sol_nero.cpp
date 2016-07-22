#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

void read() {}

template<typename T,typename... Args>
void read(T &x,Args&... args) {
    char c; bool sign = false;
    for (c = getchar();c < '0' || c > '9'; c = getchar()) if (c == '-') sign = true;
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    sign && (x = -x);
    read(args...);
}

const int N = 10000 + 5;
const int D = 10;
const int INF = 0x3f3f3f3f;
int n,m;
std::vector<int> edges[N];
std::vector<std::pair<int,int>> ext;
int par[D][N],dis[D][N];
int ban[N];

int dsu[N];

int find(int x) {
    return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

void bfs(int source,int *par,int *dis) {
    std::fill(par,par + n,-1);
    std::fill(dis,dis + n,INF);
    std::queue<int> que;
    que.push(source);
    dis[source] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int v : edges[u]) {
            if (ban[v] == 0 && dis[v] == INF) {
                dis[v] = dis[u] + 1;
                par[v] = u;
                que.push(v);
            }
        }
    }
}

int dfs(int u,int fa) {
    int ret = 0;
    for (int v : edges[u]) {
        if (ban[v] || v == fa) continue;
        ret = std::max(ret,dfs(v,u) + 1);
    }
    return ret;
}

int calc(int s,int t) {
    static int par[N],dis[N];
    int tmp = ban[t]; ban[t] = 0;
    bfs(s,par,dis);
    ban[t] = tmp;
    if (dis[t] == INF) {
        return dfs(s,-1) + dfs(t,-1);
    }
    std::vector<int> vec;
    for (int u = t; ; u = par[u]) {
        vec.emplace_back(u);
        if (u == s) break;
    }
    std::reverse(ALL(vec));
    std::vector<int> prefix(vec.size() + 1),suffix(vec.size() + 1);
    for (int x : vec) ban[x] ++;
    for (int i = 0; i < vec.size(); ++ i) {
        int u = vec[i];
        int val = dfs(u,-1);
        prefix[i] = std::max(prefix[i],val + dis[u]);
        prefix[i + 1] = prefix[i];
        suffix[i] = val + dis[t] - dis[u];
    }
    for (int i = (int)vec.size() - 1; i >= 0; -- i) {
        suffix[i] = std::max(suffix[i],suffix[i + 1]);
    }
    int ret = 0;
    for (int d = 1; d < vec.size(); ++ d) {
        ret = std::max(ret,prefix[d - 1] + suffix[d]);
    }
    for (int x : vec) ban[x] --;
    return ret;
}

int search(int u,int source) {
    int ret = calc(u,source);
    for (int i = 0; i < (int)ext.size(); ++ i) {
        for (int c = 0; c < 2; ++ c) {
            int fst = ext[i].first,snd = ext[i].second;
            if (c) std::swap(fst,snd);
            if (ban[snd]) continue;
            auto f = [](int a,int b,int snd,int *par,int *ban) {
                if (a == b) return true;
                for (int x = par[a]; ; x = par[x]) {
                    if (ban[x] || x == snd) return false;
                    if (x == b) break;
                }
                return true;
            };
            if (f(u,fst,snd,par[i << 1 | c],ban) == false) continue;
            for (int x = u; x != fst; x = par[i << 1 | c][x]) {
                ban[x] ++;
            }
            ban[fst] ++;
            ban[snd] ++;
            ret = std::max(ret,search(snd,source) + dis[i << 1 | c][u] + 1);
            for (int x = u; x != fst; x = par[i << 1 | c][x]) {
                ban[x] --;
            }
            ban[fst] --;
            ban[snd] --;
        }
    }
    return ret;
}

int b_search(int u,int d) {
    int ret = d;
    for (int v : edges[u]) {
        if (ban[v]) continue;
        ban[v] ++;
        ret = std::max(ret,b_search(v,d + 1));
        ban[v] --;
    }
    for (int i = 0; i < ext.size(); ++ i) {
        for (int c = 0; c < 2; ++ c) {
            int fst = ext[i].first,snd = ext[i].second;
            if (c) std::swap(fst,snd);
            if (fst != u || ban[snd]) continue;
            ban[snd] ++;
            ret = std::max(ret,b_search(snd,d + 1));
            ban[snd] --;
        }
    }
    return ret;
}

int brute() {
    int ret = 0;
    std::fill(ban,ban + n,0);
    for (int source = 0; source < n; ++ source) {
        ban[source] ++;
        ret = std::max(ret,b_search(source,0));
        ban[source] --;
    }
    return ret;
}

int work() {
    bfs(0,par[0],dis[0]);
    bfs(std::max_element(dis[0],dis[0] + n) - dis[0],par[0],dis[0]);
    int result = *std::max_element(dis[0],dis[0] + n);
    for (int i = 0; i < (int)ext.size(); ++ i) {
        bfs(ext[i].first,par[i << 1],dis[i << 1]);
        bfs(ext[i].second,par[i << 1 | 1],dis[i << 1 | 1]);
    }
    std::fill(ban,ban + n,0);
    for (int i = 0; i < (int)ext.size(); ++ i) {
        for (int c = 0; c < 2; ++ c) {
            int fst = ext[i].first,snd = ext[i].second;
            if (c) std::swap(fst,snd);
            ban[fst] ++;
            ban[snd] ++;
            result = std::max(result,search(snd,fst) + 1);
            ban[fst] --;
            ban[snd] --;
        }
    }
    return result;
}

int main() {
    //freopen("data.in","r",stdin);
    int cas;
    read(cas);
    while (cas--) {
        read(n,m);
        for (int i = 0; i < n; ++ i) edges[i].clear();
        std::iota(dsu,dsu + n,0);
        ext.clear();
        for (int i = 0; i < m; ++ i) {
            int a,b;
            read(a,b); a --; b --;
            if (find(a) != find(b)) {
                edges[a].push_back(b);
                edges[b].push_back(a);
                dsu[find(a)] = find(b);
            } else {
                ext.emplace_back(a,b);
            }
        }
        printf("%d\n",work());
    }
}
