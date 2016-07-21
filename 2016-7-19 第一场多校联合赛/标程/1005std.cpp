#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 10;

int n, m, f[N][N], x, y, ans, in_girl[N], in_boy[N], boy[N], girl[N];

void dfs_girl(int k, int s)
{
    int v = 0, flag;
    for(int i = 1; i <= n; i++)
        if(!in_girl[i])
    {
        flag = 1;
        for(int j = k; j <= n; j++)
            if(!(f[i][boy[j]] || f[i][boy[j % n + 1]]))
        {
            flag = 0; break;
        }
        if(flag) v++;
    }
    if(s + v >= ans) return;
    if(k > n){
        ans = s; return;
    }
    for(int i = 2; i <= n; i++)
        if(!in_girl[i])
    {
        int p = (f[i][boy[k]] || f[i][boy[k % n + 1]]) ? 1 : 0;
        in_girl[i] = 1;
        dfs_girl(k + 1, s + p);
        in_girl[i] = 0;
    }
}

void dfs_boy(int k)
{
    if(k > n){
        for(int i = 2; i <= n; i++) in_girl[i] = 0;
        if(f[1][boy[1]] || f[1][boy[2]])
            dfs_girl(2, 1);
        else
            dfs_girl(2, 0);
        return;
    }
    for(int i = 1; i <= n; i++)
        if(!in_boy[i])
    {
        boy[k] = i;
        in_boy[i] = 1;
        dfs_boy(k + 1);
        in_boy[i] = 0;
    }
}

int main()
{
   // freopen("data.txt", "r",stdin);
    //freopen("ans.txt", "w", stdout);
    while(scanf("%d%d", &n, &m) != EOF){
        memset(f, 0, sizeof(f));
        memset(in_girl, 0, sizeof(in_girl));
        memset(in_boy, 0, sizeof(in_boy));
        memset(girl, 0, sizeof(girl));
        memset(boy, 0, sizeof(boy));

        for(int i = 0; i < m; i++)
            scanf("%d%d", &x, &y), f[x][y] = 1;
        ans = n;
        in_girl[1] = 1;
        dfs_boy(1);
        printf("%d\n", ans);
    }
}


