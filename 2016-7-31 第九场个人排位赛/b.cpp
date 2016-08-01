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

int vis[50000];
int main()
{
	int p, a, b;
	scanf("%d", &p);
	while(~scanf("%d", &a) && a){
		scanf("%d", &b);
		memset(vis, 0, sizeof(vis));
		int x = 2;
		if(b == 1){
			puts("0");
			continue;
		}
		else if (a % p == b){
			puts("1");
			continue;
		}
		int tmp = a;
		bool flag;
		for( ; ; x++){
			tmp *= a;
			tmp %= p;
			if(tmp == b){
				flag = true;
				break;
			}
			else if (!vis[tmp]){
				vis[tmp] = 1;
			}
			else{
				flag = false;
				break;
			}
		}
		if(flag){
			printf("%d\n", x);
		}
		else{
			puts("0");
		}
	}


	return 0;
}

