#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int INF = 0x3f3f3f3f;
template<int N> struct CostFlow {
    int s,t,vis[N],d[N],head[N],cur[N],etot;
    struct Edge {int v,cap,cost,next;} g[2055555];
    void add_edge(int u,int v,int cap,int cost) {
        g[etot].v = v; g[etot].cap = cap; g[etot].cost = cost; g[etot].next = head[u]; head[u] = etot ++;
        g[etot].v = u; g[etot].cap = 0; g[etot].cost = -cost; g[etot].next = head[v]; head[v] = etot ++;
    }
    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }
    int aug(int u,int a) {
        if (u==t) return a;
        vis[u] = 1;
        int flow = 0,f;
        for (int &i = cur[u]; i != -1; i = g[i].next) {
            Edge &e = g[i];
            if (e.cap && !vis[e.v] && d[u]==d[e.v]+e.cost)
                if (f = aug(e.v,std::min(a,e.cap))) {
                    flow += f;
                    e.cap -= f;
                    g[i^1].cap += f;
                    a -= f;
                    if (a==0) break;
                }
        }
        return flow;
    }
    bool modlabel() {
        int tmp = INF;
        for (int u = 0; u < N; u ++) if (vis[u]) {
            for (int i = head[u]; i != -1; i = g[i].next) {
                Edge &e = g[i];
                if (e.cap && !vis[e.v])
                    tmp = std::min(tmp,d[e.v]+e.cost-d[u]);
            }
        }
        if (tmp==INF) return true;
        for (int u = 0; u < N; u ++) if (vis[u]) {
            vis[u] = 0;
            d[u] += tmp;
        }
        return false;
    }
    void mcmf(int _s,int _t,int &cost,int &flow) {
        s = _s; t = _t; cost = flow = 0; int f;
        memset(d,0,sizeof(d));
        while (true) {
            memcpy(cur,head,sizeof(head));
            while (f=aug(s,INF)) {
                flow += f;
                cost += f*d[s];
                memset(vis,0,sizeof(vis));
            }
            if (modlabel()) break;
        }
    }
};

const int N = 500 + 5;
int n,m;
std::vector<int> edges[N];
char str[N];
bool mark[N];

CostFlow<500 + 2> F;

int graph[N][N];

std::vector<int> get_path(int source,int target) {
    std::queue<int> que;
    std::vector<int> pre(n,-1);
    que.push(source);
    pre[source] = -2;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        if (u == target) break;
        for (int v : edges[u]) {
            if (pre[v] == -1) {
                pre[v] = u;
                que.push(v);
            }
        }
    }
    std::vector<int> vec;
    for (int u = target; ; u = pre[u]) {
        vec.push_back(u);
        if (u == source) break;
    }
    assert(vec.size() % 2 == 0);
    return vec;
}

bool zz(int q,int c,std::vector<std::pair<int,int>> &op) {
    int qf = 0,qe = 0;
    std::vector<int> tag(n,-1),que(n);
    que[qe++] = q;
    tag[q] = 0;
    while (qf != qe) {
        int u = que[qf++];
        mark[u] = true;
        for (int v : edges[u]) {
            if (tag[v] == -1) {
                tag[v] = tag[u] ^ 1;
                que[qe++] = v;
            } else if (tag[v] != tag[u] ^ 1) {
                return false;
            }
        }
    }
    F.init();
    int _s = n,_t = _s + 1;
    int a = 0,b = 0;
    for (int I = 0; I < qe; ++ I) {
        int u = que[I];
        if (tag[u] == 0) {
            if (str[u] != c + '0') {
                F.add_edge(_s,u,1,0);
                a ++;
                for (int J = 0; J < qe; ++ J) {
                    int v = que[J];
                    if (tag[v] == 1 && str[v] == c + '0') {
                        F.add_edge(u,v,1,graph[u][v]);
                    }
                }
            }
        } else {
            if (str[u] == c + '0') {
                F.add_edge(u,_t,1,0);
                b ++;
            }
        }
    }
    if (a != b) return false;
    int cost,flow;
    F.mcmf(_s,_t,cost,flow);
    assert(flow == a);
    std::vector<std::vector<int>> paths;
    std::vector<bool> is_key(n);
    for (int I = 0; I < qe; ++ I) {
        int u = que[I];
        if (tag[u] == 0 && str[u] != c + '0' || tag[u] == 1 && str[u] == c + '0') is_key[u] = true;
        if (tag[u] != 0 || str[u] == c + '0') continue;
        for (int i = F.head[u]; i != -1; i = F.g[i].next) {
            int v = F.g[i].v;
            if ((~i & 1) && F.g[i ^ 1].cap > 0 && v != _t) {
                paths.push_back(get_path(u,v));
            }
        }
    }
    for (auto &vec : paths) {
        for (int i = 0; i < vec.size(); ) {
            int j = i;
            while (j + 2 < vec.size() && is_key[vec[j + 2]]) j += 2;
            for (int k = j; ; k -= 2) {
                if (k + 2 == vec.size()) {
                    op.emplace_back(vec[k],vec[k + 1]);
                } else if (is_key[vec[k + 1]]) {
                    op.emplace_back(vec[k + 1],vec[k]);
                    op.emplace_back(vec[k + 1],vec[k + 2]);
                } else {
                    op.emplace_back(vec[k + 1],vec[k + 2]);
                    op.emplace_back(vec[k + 1],vec[k]);
                }
                if (k == i) break;
            }
            is_key[vec[i]] = false;
            is_key[vec[std::min(j + 2,(int)vec.size() - 1)]] = true;
            i = j + 2;
        }
        is_key[vec[0]] = is_key[vec.back()] = false;
    }
    return true;
}

int work() {
    std::vector<std::pair<int,int>> result;
    memset(mark,false,sizeof(mark));
    for (int i = 0; i < n; ++ i) {
        if (mark[i]) continue;
        std::vector<std::pair<int,int>> va,vb;
        bool fa = zz(i,0,va);
        bool fb = zz(i,1,vb);
        if (!fa && !fb) return -1;
        if (fa == false || fb == true && vb.size() < va.size()) va.swap(vb);
        result.insert(result.end(),ALL(va));
    }
    printf("%d\n",result.size());
    for (auto t : result) {
        printf("%d %d\n",t.first + 1,t.second + 1);
    }
    return 0;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        scanf("%s",str);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                graph[i][j] = i == j ? 0 : INF;
            }
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
            graph[a][b] = graph[b][a] = 1;
        }
        for (int k = 0; k < n; ++ k) 
            for (int i = 0; i < n; ++ i) 
                for (int j = 0; j < n; ++ j)
                    graph[i][j] = std::min(graph[i][j],graph[i][k] + graph[k][j]);
        int answer = work();
        if (answer == -1) {
            printf("-1\n");
        }
    }
}
