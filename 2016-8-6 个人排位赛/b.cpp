/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 19:10:20 CST

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
const int maxn = 1e5+7, maxe = 1e6+7, maxv = 1e6+7;
int a[maxn];
int main()
{
	int T, n;
	int m1, m2, m3, p1 = 0, p2 = 0, p3;
	scanf("%d", &T);
	while(T --){
		m1 = m2 = m3 = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%d", &a[i]);
			if(i == 0)
				continue;
			int tmp = abs(a[i] - a[i-1]);
			if(m3 < tmp){
				if(m2 < tmp){
					if(m1 < tmp){
						p2 = p1; p3 = p2; p1 = i;
						m3 = m2;
						m2 = m1;
						m1 = tmp;
					}
					else{
						p3 = p2;
						p2 = i;
						m3 = m2;
						m2 = tmp;
					}
				}
				else{
					p3 = i;
					m3 = tmp;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++){
			if(i == 0 || i == n-1){
				if(i == 0){
					if(p1 == i + 1)
						ans += m2;
					else
						ans += m1;
				}
				else{
					if(p1 == i)
						ans += m2;
					else
						ans += m1;
				}
			}
			else {
				int tmp = abs(a[i+1] - a[i-1]);
				if(tmp >= m1){
					ans += tmp;
				}
				else{
					if(p1 == i + 1 || p1 == i){
						if(p2 == i + 1 || p2 == i){
							ans += max(m3, tmp);
						}
						else{
							ans += max(m2, tmp);
						}
					}
					else{
						ans += m1;
					}
				}
			}	
		}
		printf("%d\n", ans);
	}
	
	return 0;
}








