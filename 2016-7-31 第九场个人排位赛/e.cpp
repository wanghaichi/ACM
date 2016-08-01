#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

const int maxn = 1e6+7;
const int mod = 1e9+7;
typedef long long ll;
const double eps = 1e-6;

int mat[15][15];
double mat1[15][15];
int vis[15];
bool solve(int k){
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < k; i ++){
		int j, n, m;
		for(j = 0; j < k; j ++){
			if(mat[i][j] == 0 || vis[j])
				continue;
			else{
				vis[j] = 1;
				break;
			}
		}
		
		for(n = j + 1; n < k; n ++){
			if(mat[n][i] == 0)
				continue;
			int tmp = __gcd(mat[n][i], mat[j][i]);
			tmp = mat[n][i] / tmp * mat[j][i];
			int b1 = tmp / mat[j][i];
			int b2 = tmp / mat[n][i];
			for(m = i; m < k; m ++){
				mat[j][m] *= b1;
			}
			for(m = i; m < k; m ++){
				mat[n][m] = mat[n][m] * b2 - mat[j][m];
			}
			for(m = i; m < k; m ++){
				mat[j][m] /= b1;
			}
		}
	}
	int ct, res = 0;
	for(int i = 0; i < k; i ++){
		ct = 0;
		for(int j = 0; j < k; j ++){
			if(mat[i][j] == 0)
				ct++;
		}
		if (ct == k)
			res ++;
	}
	if(res == 0)
		return false;
	else{
		return true;
	}
}

int main()
{
	int T, k, ct = 1;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &k);
		for(int i = 0; i < k; i ++){
			for(int j = 0; j < k; j ++){
				scanf("%lf", &mat1[i][j]);
			}
		}
		for(int i = 0; i < k; i ++){
			for(int j = 0; j < k; j ++){
				mat[i][j] = (int)((mat1[i][j])*100);
			} 
		}
		bool res = solve(k);
		if(res)
			printf("1");
		else{
			printf("0");
		}
		if(ct % 5 != 0)
			printf(" ");
		else{
			printf("\n");
		}
		ct++;
	}
	return 0;
}

