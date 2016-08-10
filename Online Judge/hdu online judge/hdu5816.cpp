/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 10日 星期三 09:10:20 CST

ID: hdu 5816 第7场多校

TYPE: 计数 DP

DETAIL: 玩炉石，只有两种牌，A种牌可以再摸两张，B种牌让对面掉 Wi 滴血，
敌人有 P 滴血，有n张A，m张B，给出每张B的w，求一回合能击杀对面的概率

TACTICS: 这题其实有 O(2^M) 的做法. 方法用 f[i][j] 表示 A 类牌和 B 类牌分别抽到 i 张和 j 张，且抽牌结束前保证 i>=j 的方案数，这个数组可以用 O(n^2) 的 dp 预处理得到. 接下来枚举 B 类牌的每个子集，如果这个子集之和不小于 P，用 k 表示子集的 1 的个数，将方案总数加上取到这个集合刚好 A 类卡片比 B 类卡片少一（过程结束）的方案数：f[k-1][k] * C(n, k - 1) * (k - 1)! * k! * (n + m – 2*k + 1)! . 如果子集包含了所有的 B 类卡片，则还需要再加上另一类取牌结束的情况，也就是取完所有牌，此时应加上的方案数为 f[n][m] * n! * m! . 最后的总方案数除以 (n+m)! 就是答案.

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 21, maxe = 1e6+7, maxv = 1e6+7;

ll dp[maxn][maxn];

ll C(ll a, ll b){
	a = a > b - a ? b - a : a;
	ll res = 1;
	for(int i = 1; i <= a; i ++){
		res *= (b - i + 1);
		res /= i;
	}
	return res;
}

ll jie(ll a){
	ll res = 1;
	for(int i = 1; i <= a; i ++){
		res *= i;
	}
	return res;
}

ll gcd(ll a, ll b){
	if(b == 0) return a;
	return gcd(b , a % b);
}

int sto[maxn];

int main()
{
	int T, p, n, m;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d%d", &p, &n, &m);
		CL(dp);
		dp[0][0] = 1;
		for(int i = 0; i <= n; i ++){
			for(int j = 0; j <= min(m, i + 1); j ++){
				if(j > 0)
					dp[i][j] = dp[i][j - 1];
				if(i - 1 >= j)
					dp[i][j] += dp[i-1][j];
			}
		}
		for(int i = 0; i < m; i ++){
			scanf("%d", &sto[i]);
		}
		ll ans = 0;
		for(int i = 0; i < (1 << m); i ++){
			int ct = 0, sum = 0;
			for(int j = 0; j < m; j ++){
				if(i & (1 << j)){
					sum += sto[j];
					ct ++;
				}
			}
			if(sum >= p){
				ans += dp[ct-1][ct] * C(ct - 1, n) * jie(ct-1) * jie(ct) * jie(n+m-2*ct+1);
				//使用了全部B牌的情况
				if(ct == m && ct - 1 != n){
					ans += dp[n][m] * jie(n) * jie(m);
				}
			}
		}
		ll dd = jie(n+m);
		ll cc = gcd(dd, ans);
		printf("%lld/%lld\n", ans/cc, dd/cc);
	}
	
	return 0;
}







