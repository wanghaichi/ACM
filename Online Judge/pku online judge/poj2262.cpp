/*************************************************************

FILENAME:                   poj2262.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-18 09:50:59

LAST MODIFIED:         2016-08-18 09:57:07

ID: poj 2262 

TYPE: 数论

DETAIL: 给出一个大于６的偶数　找出两个奇素数的和是ｎ

TATICS: 暴力枚举就行

************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a))

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1000001;

int prime[maxn], isNotPrime[maxn], cnt;
void init(){
	CL(prime);
	CL(isNotPrime);
	for(int i = 2; i < maxn; i ++){
		if(!isNotPrime[i])
			prime[cnt++] = i;
		for(int j = 0; j < cnt && i * prime[j] < maxn; j ++){
			isNotPrime[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}

int main()
{
	int n;
	init();
	while(~scanf("%d", &n) && n){
		for(int i = 1; i < cnt; i ++){
			if(!isNotPrime[n - prime[i]]){
				printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
				break;
			}
		}
	}
	return 0;
}

