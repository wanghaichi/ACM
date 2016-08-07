/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 19:34:32 CST

ID:

TYPE:

DETAIL:

TACTICS:

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
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;

int a[maxn], b[maxn];

int main()
{
	int T, n, m, k;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d%d", &n, &m, &k);
		CL(b);
		for(int i = 0; i < n; i ++){
			scanf("%d", &a[i]);
			if(a[i] >= m){
				b[i] = 0;
			}
			else{
				b[i] = 1;
			}
			b[i] += b[i-1];
		}
		ll ans = 0;
		for(int i = k-1; i < n; i ++){
			int l, r, mid;
			l = 0;
			r = i - k + 1;
			while(l < r){
				int mid = (l+r)/2;
				if(b[i] - b[mid] <= k){
					l = mid + 1;
				}
				else{
					r = mid - 1;
				}
			}
			if( l > 0 && b[i] - b[l-1] <= k)
				l --;
			ans += (i - l + 1);
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}








