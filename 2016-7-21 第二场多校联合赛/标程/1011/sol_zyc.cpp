#include<bits/stdc++.h>
using namespace std;

int a[102400];

int main() {
	int T, n;
	for(scanf("%d", &T); T--; ) {
		scanf("%d", &n);
		int s = 0, c = 0;
		for(int i = 0, t; i < n; ++i) {
			scanf("%d", &t);
			if(t&1) ++c;
			s += t;
		}
		printf("%d\n", c ? (s-c >> 1)/c * 2 + 1 : s);
	}
}
