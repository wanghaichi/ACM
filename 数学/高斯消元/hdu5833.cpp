/*************************************************************

FILENAME:                   hdu5833.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-15 14:19:00

LAST MODIFIED:         2016-08-15 15:21:53

ID: hdu 5833 

TYPE: 高斯消元 异或消元

DETAIL: 给n个数，保证每个数的质因子最大不会超过2000，问有多少中取法能够使得取出的数的
乘机是完全平方数

TATICS: 将每一个数质因子分解，形成一个0,1矩阵，0表示当前质因子出现偶数次，否则出现奇
数次，然后进行高斯消元，注意消元的时候使用异或消元。
求出秩r，结果为 2^r - 1

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
const double eps = 1e-6;
const int maxn = 305, maxe = 2001;

int prime[303], isNotPrime[maxe], cnt;

void init(){
	CL(prime);
	CL(isNotPrime);
	for(int i = 2; i < maxe; i ++){
		if(!isNotPrime[i]){
			prime[cnt++] = i;
		}
		for(int j = 0; j < cnt && prime[j] * i < maxe; j ++){
			isNotPrime[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}

struct Mat{
	int mat[maxn][maxn];
	int n, m;
	Mat(){
		n = maxn, m = maxn;
	}
	Mat(int _n):n(_n), m(maxn){}
	void init(){
		CL(mat);
	}
	//求秩
	int Rank(){
		int i, j, k, col, max_r, res = 0;
		for(k = 0, col = 0; k < n && col < m; k ++, col++){
			max_r = k;
			for(i = k + 1; i < n; i ++)
				if(mat[i][col] > mat[max_r][col]){
					max_r = i;
				}
			if(mat[max_r][col] == 0){
				k --;
				continue;
			}
			if(k != max_r){
				for(j = col; j < m; j ++){
					swap(mat[k][j], mat[max_r][j]);
				}
			}
			for(int i = k + 1; i < n; i ++){
				if(mat[i][col]){
					for(int j = col; j < m; j ++){
						mat[i][j] ^= mat[k][j];
					}
				}
			}
			res ++;
		}
		return res;
	}
	void print(){
		for(int i = 0; i < n; i ++){
			for(int j = 0; j < m; j ++){
				printf("%d%c", mat[i][j], j == m - 1 ? '\n' : ' ');
			}
		}
	}
};

ll mul(ll a, ll b){
	ll res = 1;
	while(b > 0){
		if(b & 1) res *= a;
		res %= mod;
		a *= a;
		a %= mod;
		b >>= 1;
	}
	return res;
}

int main()
{
	init();
	/*int i;
	for(i = 0; i < cnt; i ++){
		if(prime[i] > 2000)
			break;
	printf("%d %d", prime[i-1], i);
	*/
	//printf("%d", cnt);
	int T, n, tt = 1;
	ll tmp;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		Mat m(n);
		m.init();
		for(int i = 0; i < n; i ++){
			scanf("%I64d", &tmp);
			for(int j = 0; j < cnt; j ++){
				if(tmp % prime[j] == 0){
					int ct = 0;
					while(tmp % prime[j] == 0){
						tmp /= prime[j];
						ct ++;
					}
					m.mat[i][j] = ct & 1;
				}
			}
		}
		int r = n - m.Rank();
	
		ll ans = mul(2, r) - 1;
		ans = (ans + mod) % mod;
		printf("Case #%d:\n%I64d\n",tt ++, ans);
	}


	return 0;
}

