#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1111;
int n, m, x[MAXN], y[MAXN], blockx[MAXN], blocky[MAXN];
char a[MAXN][MAXN];
long long ans;
inline void calc(const int &n, int x[])
{
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            ans += (long long)(j - i) * x[i] * x[j];
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int fuck;
    scanf("%d", &fuck);
    while (fuck--)
    {
        scanf("%d%d", &n, &m);
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        memset(blockx, 0, sizeof(blockx));
        memset(blocky, 0, sizeof(blocky));
        for (int i = 1; i <= n; i++)
            scanf("%s", a[i] + 1);
        long long cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (a[i][j] == '#')
                    x[i]++, y[j]++, cnt++;
                else
                    blockx[i] = j, blocky[j] = i;
        cnt *= cnt;
        ans = 0;
        calc(n, x);
        calc(m, y);
        ans *= 2;
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (blockx[i] > blockx[i - 1])
                sum += blockx[i] - 1;
            else if (!blockx[i])
                sum = 0;
            else
                sum = blockx[i] - 1;
            int tmp = m;
            if (blockx[i])
                tmp -= blockx[i];
            ans += 4 * tmp * sum;
        }
        sum = 0;
        for (int i = n; i >= 1; i--)
        {
            if (blockx[i] < blockx[i + 1])
                sum = 0;
            int tmp = m;
            if (blockx[i])
                tmp -= blockx[i];
            ans += 4 * tmp * sum;
            if (blockx[i] > blockx[i + 1])
                sum += blockx[i] - 1;
            else if (!blockx[i])
                sum = 0;
            else
                sum = blockx[i] - 1;
        }
        sum = 0;
        for (int i = 1; i <= m; i++)
        {
            if (blocky[i] > blocky[i - 1])
                sum += blocky[i] - 1;
            else if (!blocky[i])
                sum = 0;
            else
                sum = blocky[i] - 1;
            int tmp = n;
            if (blocky[i])
                tmp -= blocky[i];
            ans += 4 * tmp * sum;
        }
        sum = 0;
        for (int i = m; i >= 1; i--)
        {
            if (blocky[i] < blocky[i + 1])
                sum = 0;
            int tmp = n;
            if (blocky[i] != -1)
                tmp -= blocky[i];
            ans += 4 * tmp * sum;
            if (blocky[i] > blocky[i + 1])
                sum += blocky[i] - 1;
            else if (!blocky[i])
                sum = 0;
            else
                sum = blocky[i] - 1;
        }
        printf("%.4f\n", (double)ans / cnt);
    }
    return 0;
}
