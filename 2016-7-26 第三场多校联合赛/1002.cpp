#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;

struct node{
	double x, y;
}no[N];

int main()
{
	int T, n, m;
	double x, y;
	while(~scanf("%d", &n)){
		double ans = 0;
		if(n == 1){
			scanf("%lf", &x);
			printf("%.6lf\n", x);
			continue;
		}
		for(int i = 0; i < n; i ++){
			scanf("%lf", &x);
			if(i == 0 || i == n-1){
				ans += x * 0.5;
			}
			else{
				ans += x / 3.0;
			}
		}
		printf("%.6lf\n", ans);
	}





	return 0;
}
