#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[21], b[21], n;
bool dp[51];

bool dfs(int d, int lim, int id) {
    int i, j;
    if (d == lim) {
        memset(dp, false, sizeof(dp));
        dp[0] = true;
        for (i = 0;i < lim;i++) {
            for (j = 50-b[i];j >= 0;j--) {
                if (dp[j]) dp[j+b[i]] = true;
            }
        }
        for (i = 0;i < n;i++) {
            if (!dp[a[i]]) return false;
        }
        return true;
    }
    for (i = id;i <= 50;i++) {
        b[d] = i;
        if (dfs(d+1, lim, i+1)) return true;
    }
    return false;
}

int main() {
    int i, j;
    while (~scanf("%d", &n)) {
        for (i = 0;i < n;i++) scanf("%d", a+i);
        for (i = 1;!dfs(0, i, 1);i++);
        printf("%d\n", i);
    }
}
