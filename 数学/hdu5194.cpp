/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 19:20:27 CST

ID: hdu 5194

TYPE: 推公式２３３３３

DETAIL: 求一个含有n个０m个１的01串中'01'出现的期望
每一位出现01的概率为 n / (n+m) * m / (n + m - 1)
由于最后一位不能出现01故总的期望为 出现01的概率 * （n + m - 1)
***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;


int main()
{
	ll n, m;
	while(~scanf("%lld%lld", &n, &m)){
		ll c = __gcd(n * m, n + m);
		printf("%lld/%lld\n", n*m/c, (n+m)/c );
	}
	return 0;
}








