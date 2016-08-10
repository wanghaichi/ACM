/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 10日 星期三 18:10:25 CST

ID: poj 1141

TYPE: 动态规划

DETAIL: ()[]([])形如这样匹配的括号为完美匹配，给出一串括号，求出一个最短的完美
匹配，包含给出的字符串

TACTICS: dp[i][j] 表示从i到j最少需要添加括号的数量，pos[i][j] 表示从i到j要分
的位置，-1表示不需要分
dp[i][j] = min(dp[i][k] , dp[k+1][j]);
特别的 当s[i] == s[j]的时候，dp[i][j] = dp[i+1][j-1] pos[i][j] = -1

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
const int maxn = 1e2+7, maxe = 1e6+7, maxv = 1e6+7;

char s[maxn];

int dp[maxn][maxn], pos[maxn][maxn];
//递归输出结果
void Print(int x, int y){
	if(x > y)
		return;
	if(x == y){
		if(s[x] == '(' || s[x] == ')')
			printf("()");
		else
			printf("[]");
	}
	else if (pos[x][y] == -1){
		printf("%c", s[x]);
		Print(x + 1, y - 1);
		printf("%c", s[y]);
	}
	else{
		Print(x, pos[x][y]);
		Print(pos[x][y] + 1, y);
	}
}


int main()
{	
	scanf("%s", s);
	int n = strlen(s);
	CL(dp);
	for(int i = 0; i <= n; i ++)
		dp[i][i] = 1;
	for(int k = 1; k <= n; k ++){
		for(int i = 0; i + k < n; i ++){
			int j = i + k;
			dp[i][j] = inf;
			if((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')){
				dp[i][j] = dp[i+1][j-1];
				pos[i][j] = -1;
			}
			for(int l = i; l <= j; l ++){
				if(dp[i][l] + dp[l+1][j] < dp[i][j]){
					dp[i][j] = dp[i][l] + dp[l+1][j];
					pos[i][j] = l;
				}
			}
		}
	}
	Print(0, n-1);
	puts("");
	
	return 0;
}







