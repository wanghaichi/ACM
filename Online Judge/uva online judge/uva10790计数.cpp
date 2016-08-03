/**************uva10790********

基础计数问题，上下两条边，分别有ａ个点和ｂ个点，在两者之间连线，问形成的点的个数。

******************************/



#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

int main()
{
	ll a, b;
	int cnt = 1;
	while(~scanf("%lld%lld", &a, &b) && (a != 0 || b != 0)){
		ll ans = (a-1)*a*b*(b-1)/4;
		printf("Case %d: %lld\n",cnt++, ans);
	}
}

