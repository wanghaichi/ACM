#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;
typedef long long ll;

int main()
{
    int T;
    scanf("%d", &T);
    ll dp[30][30], a[30];  //这里不用ll会wa
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= 25; i ++){
        dp[i][0] = dp[i-1][0]*10 - dp[i-1][1];
        dp[i][1] = dp[i-1][0];
        dp[i][2] = dp[i-1][2]*10 + dp[i-1][1];
    }
    while(T --){
        ll n;
        scanf("%I64d", &n);
        n ++;
        int len = 0;
        a[0] = 0;
        while(n > 0){
            a[++len] = n % 10;
            n /= 10;
        }
        a[len+1] = 0;
        int flag = 0;
        ll ans = 0;
        for(int i = len; i >= 1; i --){
            ans += a[i] * dp[i-1][2];
            if(!flag && a[i] > 4)
                ans += dp[i-1][1];
            if(flag)
                ans += a[i] * dp[i-1][0];
            if(a[i] == 9 && a[i+1] == 4)
                flag = 1;
        }
        printf("%I64d\n", ans);

    }
    return 0;
}
