/*************************************************************

FILENAME:                   hdu5857.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-19 10:23:51

LAST MODIFIED:         2016-08-19 12:28:46

ID: hdu 5857 

TYPE: 模拟

DETAIL: 给出一串有序的序列，给出两个段范围，组成新的一段序列，求中位数

TATICS: 注意longlong 不然会炸

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
const int maxn = 1e6+7;

ll num[maxn];

int main()
{
	int T, n, m, l1, r1, l2, r2;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			scanf("%lld", &num[i]);
		while(m --){
			scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
			if(l1 > l2){
				swap(l1, l2);
				swap(r1, r2);
			}
			int len = r1 - l1 + r2 - l2 + 2;
			int tlen = (len + 1)/2;
			double ans;
			if(r1 < l2){
				if(r1 - l1 + 1 >= tlen){
					if(len & 1){
						ans = num[l1 + tlen - 1];
					}else{
						if(r1 - l1 + 1 == tlen)
							ans = num[l1 + tlen - 1] + num[l2];
						else
							ans = num[l1 + tlen-1] + num[l1 + tlen];
						ans /= 2;
					}
				}
				else{
					if(len&1){
						ans = num[l2 + (tlen-r1+l1-1) - 1];
					}
					else{
						ans = num[l2 + tlen - r1 + l1 - 2] + num[l2+tlen-r1+l1-1];
						ans /= 2;
					}
				}
			}
			else{
				if(r1 < r2){
					swap(r1, r2);
				}
				if(l2-l1 >= tlen){
					if(len&1)
						ans = num[l1+tlen-1];
					else{
						ans = num[l1+tlen-1] + num[l1+tlen];
						ans /= 2;
					}
				}
				else if (2*(r2-l2+1)+l2-l1 >= tlen){
					int pos = tlen - (l2 - l1) + 1;
					if(len&1){
						ans = num[l2 + pos/2 - 1];
					}
					else{
						if(pos&1)
							ans = num[l2 + pos/2 - 1] + num[l2 + pos/2];
						else
							ans = 2 * num[l2 + pos/2 - 1];
						ans /= 2;
						//cout << "h : " << l2 + pos/2 - 1 << endl;
					}
				}
				else{
					tlen -= (l2-l1 + 2*(r2-l2+1));
					if(len & 1)
						ans = num[r2 + tlen];
					else{
						ans = num[r2 + tlen] + num[r2+tlen+1];
						ans /= 2;
					}
				}
			}
			printf("%.1f\n", ans);
		}
	}


	return 0;
}

