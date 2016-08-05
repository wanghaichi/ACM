/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 05日 星期五 13:59:27 CST

ID: uva 11859

TYPE: Nim 博弈

DETAIL: 给出n*m的矩阵，每次选择一行，任选其中大于1的数，把其变成自己的真因
子，当所有的数都变成1的时候游戏结束，最后不能走的人输

TACTICS: 求出没一行的质因子数目的和（包括重复的），每一次操作相当于从一堆
石子中取出k个石子，转变成n堆石子的Nim游戏，求出没一行质因子数目的异或和，
为0则输，否则赢。

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
const int maxn = 10100, maxe = 1e6+7, maxv = 1e6+7;
int prime[maxn], isNotPrime[maxn], cnt, Count[maxn];

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
	for(int i = 2; i < maxn; i ++){
		int res = 0, tmp = i;
		for(int j = 0; j < cnt && prime[j] * prime[j] <= tmp; j ++){
			if(tmp % prime[j] == 0){
				while(tmp % prime[j] == 0){
					tmp /= prime[j];
					res ++;
				}
			}
		}
		if(tmp > 1){
			res ++;
		}
		Count[i] = res;
	}
}
int sto[55][55];
int main()
{
	int T, n, m, cc = 1;
	scanf("%d", &T);
	init();
	while(T --){
		scanf("%d%d", &n, &m);
		int ans = 0, ct;
		for(int i = 0; i < n; i ++){
			ct = 0;
			for(int j = 0; j < m; j ++){
				scanf("%d", &sto[i][j]);
				ct += Count[sto[i][j]];
			}
			ans ^= ct;
		}
		printf("Case #%d: ", cc++);
		if(ans == 0){
			puts("NO");
		}
		else
			puts("YES");
	}
	
	return 0;
}








