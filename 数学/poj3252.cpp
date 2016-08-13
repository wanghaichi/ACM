/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 13日 星期六 09:06:48 CST

ID: poj 3252

TYPE: 计数 

DETAIL: 规定 round number 为二进制表示下0的数量大于等于1的数量的数，求给定
范围内有多少 round number

TACTICS: 一位一位求，记录下之前出现的1和0的个数

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
const int maxn = 35, maxe = 1e6+7, maxv = 1e6+7;

int C[maxn][maxn];

void init(){
	CL(C);
	C[0][1] = C[1][1] = 1;
	for(int i = 2; i <= 32; i ++){
		C[0][i] = 1;
		for(int j = 1; j <= i; j ++){
			C[j][i] = C[j-1][i-1] + C[j][i-1];
		}
	}
}

int getC(int i, int j){
	i = i > j - i ? j - i : i;
	return C[i][j];
}

int getLen(int v){
	int res = 0;
	while(v > 0){
		res ++;
		v >>= 1;
	}
	return res;
}

int fuck(int len, int one, int zero){
	if(len == 0){
		if(zero >= one)
			return 1;
		return 0;
	}
	int res = 0;
	for(int i = len; i >= (len - i + one - zero) && i >= 0; i --){
		res += getC(i, len);
	}
	return res;
}

int solve(int v){
	int len = getLen(v);
	if(len == 1)
		return 0;
	int res = 0, one = 1, zero = 0;
	for(int i = 1; i <= len - 1; i ++){
		for(int j = i - 1; j >= (i - j); j --){
			res += getC(j, i - 1);
		}
	}
	for(int i = len - 2; i >= 0; i --){
		if(v & (1 << i)){
			res += fuck(i, one, zero + 1);
			one ++;
		}
		else{
			zero ++;
		}
	}
	if(one <= zero)
		res ++;
	return res;
}

int main()
{
	int n, m;
	init();
	scanf("%d%d", &n, &m);
	printf("%d\n", solve(m) - solve(n - 1));
	
	return 0;
}







