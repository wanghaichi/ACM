/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 16:55:35 CST

ID: hdu 4135

TYPE: 容斥原理

DETAIL: 求解 A 到 B 中有多少个与 N 互质的个数， 1 <= A <= B <= 1e15
N <= 1e9
首先对N进行质因子分解，由其数据范围可知不会超过9个质因子。
利用容斥原理，总数-能被一个质因子整除的+能被两个质因子整除的...
由于质因子比较小，使用状态压缩

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;

ll prime[maxn], isNotPrime[maxn], cnt;

void init(){
	CL(prime);
	CL(isNotPrime);
	cnt = 0;
	for(int i = 2; i < maxn; i ++){
		if(!isNotPrime[i])
			prime[cnt++] = i;
		for(int j = 0; j < cnt && prime[j] * i < maxn; j ++){
			isNotPrime[prime[j] * i] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}
vector<int> su;

void getSu(ll n){
	su.clear();
	ll tmp = n;
	for(int i = 0; i < cnt && prime[i] * prime[i] <= tmp; i ++){
		if(tmp % prime[i] == 0){
			su.push_back(prime[i]);
			while(tmp % prime[i] == 0){
				tmp /= prime[i];
			}
		}
	}
	if(tmp > 1)
		su.push_back(tmp);
}



int main()
{		
	int T, cc = 1;
	ll a, b ,n;
	scanf("%d", &T);
	init();
	while(T --){
		scanf("%lld%lld%lld", &a, &b, &n);
		getSu(n);
		int len = su.size();
		ll ans = 0;
		//枚举每一种状态
		for(int i = 0; i < (1 << len); i ++){
			ll tmp = i, ct = 0, count = 0, idx, sum = 1;
			ll c1, c2;
			while(tmp > 0){
				if(tmp&1){
					sum *= su[count];	
					ct ++;
				}
				tmp >>= 1;
				count ++;
			}
			idx = 1;
			if(ct & 1){
				idx = -1;
			}
			c1 = (a-1)/sum;
			c2 = b / sum;
			ans += (idx * (c2 - c1));
		}
		printf("Case #%d: %lld\n", cc++, ans);
	}
	return 0;
}








