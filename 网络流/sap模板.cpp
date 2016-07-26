#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxv = 100047, maxe = 400047;


struct E
{
    int to, from, next, cap;
}edge[maxe];

int head[maxv], cnt, n, m, src, des;
int dep[maxv], gap[maxv];

void addedge(int _u, int _v, int _w)
{
    edge[cnt].from = _u;
    edge[cnt].to = _v;
    edge[cnt].cap = _w;
    edge[cnt].next = head[_u];
    head[_u] = cnt++;
    edge[cnt].from = _v;
    edge[cnt].to = _u;
    edge[cnt].cap = 0;
    edge[cnt].next = head[_v];
    head[_v] = cnt++;
}

int que[maxv];

void bfs()
{
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[des] = 0;
    que[rear++] = des;
    int u, v;
    while (front != rear)
    {
        u = que[front++];
        front = front % maxv;
        for (int i=head[u]; i!=-1; i=edge[i].next)
        {
            v = edge[i].to;
            if (edge[i].cap != 0 || dep[v] != -1)
                continue;
            que[rear++] = v;
            rear = rear % maxv;
            ++gap[dep[v] = dep[u] + 1];
        }
    }
}
int cur[maxv],stack[maxv];
int Sap()       //sap模板
{
    int res = 0;
    bfs();
    int top = 0;
    memcpy(cur, head, sizeof(head));
    int u = src, i;
    while (dep[src] < n)
    {
        if (u == des)
        {
            int temp = inf, inser = n;
            for (i=0; i!=top; ++i)
                if (temp > edge[stack[i]].cap)
                {
                    temp = edge[stack[i]].cap;
                    inser = i;
                }
            for (i=0; i!=top; ++i)
            {
                edge[stack[i]].cap -= temp;
                edge[stack[i]^1].cap += temp;
            }
            res += temp;
            top = inser;
            u = edge[stack[top]].from;
        }

        if (u != des && gap[dep[u] -1] == 0)
            break;
        for (i = cur[u]; i != -1; i = edge[i].next)
            if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1)
                break;

        if (i != -1)
        {
            cur[u] = i;
            stack[top++] = i;
            u = edge[i].to;
        }
        else
        {
            int min = n;
            for (i = head[u]; i != -1; i = edge[i].next)
            {
                if (edge[i].cap == 0)
                    continue;
                if (min > dep[edge[i].to])
                {
                    min = dep[edge[i].to];
                    cur[u] = i;
                }
            }
            --gap[dep[u]];
            ++gap[dep[u] = min + 1];
            if (u != src)
                u = edge[stack[--top]].from;
        }
    }
    return res;
}

int main()
{
    int T, i;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        int x, y;
        int Min = inf, Max = -inf;
        for (i=1; i<=n; ++i) {      //找出起点src 终点des
            scanf("%d%d", &x, &y);
            if (x <= Min){
                src = i;
                Min = x;
            }
            if (x >= Max){
                des = i;
                Max = x;
            }
        }
        cnt = 0;
        memset(head, -1, sizeof(head));
        int u, v, c;
        for (i=0; i!=m; ++i)
        {
            scanf("%d%d%d", &u, &v, &c);
            addedge(u,v,c);
            addedge(v,u,c);
        }
        int ans = Sap();
        printf("%d\n", ans);
    }
    return 0;
}
