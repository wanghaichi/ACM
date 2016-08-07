/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 12:50:33 CST

ID: codeforces 282D

TYPE: 威佐夫博弈 

DETAIL: 威佐夫博弈：有2堆石子，每次有两种操作可选，从一堆中拿走任意石子，
或从所有堆中拿走任意数量相同的石子。具体的分析见百度百科。

TACTICS: 对于威佐夫博弈，定义当前走必输的状态为奇异态，则（0，0）为第一个
奇异态。若（an, bn）为第n个奇异态，则有an为前面所有奇异态为出现的最小正整数
，bn = an + n。
更一般的，an = n * (sqrt(5) + 1) / 2, bn = an + n
当n为奇数的时候，威佐夫博弈与一般的nim游戏一样。

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;


int sto[310];

int main()
{
	int n;
	double w = (1 + pow(5, 0.5)) / 2;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &sto[i]);
	}
	if(n == 2){
		if(sto[0] > sto[1])
			swap(sto[0], sto[1]);
		bool flag = false;
		for(int i = 0; i < 300; i ++){
			if(sto[0] == int (w * i) && sto[1] == sto[0] + i){
				flag = true;
				break;
			}
			else if (sto[0] < int(w * i))
				break;
		}
		if(flag)
			puts("BitAryo");
		else
			puts("BitLGM");
	}
	else{
		int sum = 0;
		for(int i = 0; i < n; i ++){
			sum ^= sto[i];
		}
		if(sum == 0)
			puts("BitAryo");
		else
			puts("BitLGM");
	}
	return 0;
}








