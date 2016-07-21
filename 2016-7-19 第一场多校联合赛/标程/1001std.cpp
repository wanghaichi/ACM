#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
#define N 100010
struct node {
    int u, v, w;
    node() {}
    node(int _u, int _v, int _w):u(_u), v(_v), w(_w) {}
};
struct Node{
   int v,len;
   Node(){}
   Node(int _v, int _len):v(_v), len(_len){}
};
vector<Node>vet[N];
vector<node> edge;
int n, m, f[N];
double dp[N];
int sum[N];
bool cmp(const node &x, const node &y) {
    return x.w < y.w;
}
int find_set(int x) {
    if (f[x] == x) return x;
    return f[x] = find_set(f[x]);
}
long long Kruskal() {
    sort(edge.begin(), edge.end(), cmp);
    for (int i = 1; i <= n; i++) f[i] = i;
    long long ans = 0;
    for (int i = 0, u, v, w; i < (int)edge.size(); i++)
    {
        u = edge[i].u, v = edge[i].v, w = edge[i].w;
        u = find_set(u), v = find_set(v);
        if (u == v) continue;
        f[u] = v;
        ans += (long long)w;
        vet[edge[i].u].push_back(Node(edge[i].v,w));
        vet[edge[i].v].push_back(Node(edge[i].u,w));
    }
    return ans;
}
void dfs(int root,int father)
{
   sum[root] = 1;
   for(int i = 0;i < (int)vet[root].size();i++)
    {
      int son = vet[root][i].v;
      int len = vet[root][i].len;
      if(son == father)continue;
      dfs(son,root);
      sum[root] += sum[son];
      dp[root] += dp[son] + ((double)sum[son] * (n - sum[son])) * len;
   }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        edge.clear();
        for (int i = 0, a, b, c; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            edge.push_back(node(a, b, c));
        }
        for(int i = 1;i <= n;i++)vet[i].clear();
        memset(sum,0,sizeof(sum));
        memset(dp,0,sizeof(dp));
        long long ans = Kruskal();
        dfs(1,0);
        long long s = (long long)n * (n - 1) / 2;
        printf("%I64d %.2f\n",ans,dp[1] / (double)s);
    }
    return 0;
}
