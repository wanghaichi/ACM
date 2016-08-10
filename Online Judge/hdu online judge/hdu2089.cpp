#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;
typedef long long ll;

int main()
{
    int T;
    scanf("%d", &T);
    int dp[30][30], a[30];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= 10; i ++ ){
        for(int j = 0; j < 10; j ++){
            for(int k = 0; k < 10; k ++){
                if(j != 4 && !(j==6 && k==2))
                    dp[i][j] += dp[i-1][k];
            }
        }
    }
    while(T --){
        sacnf("%d", &n);
        int len = 0;
        while(n > 0){
            a[len++] = n % 10;
            n /= 10;
        }

    }
    return 0;
}
