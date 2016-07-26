#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;

typedef long long ll;

int ans[N], dp[N], a[N];
int main()
{
	int T, n;
	scanf("%d", &T);
	while(T --){
		int tail = 0;
		dp[0] = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			int low = 0, high = tail - 1, mid;
			while(low <= high){
				mid = (low + high) / 2;
				if(dp[mid] >= a[i])
					high = mid - 1;
				else 
					low = mid + 1;
			}
			if(low >= tail) tail ++;
			ans[i] = low+1;
			dp[low] = a[i];
		}
		for(int i = 1; i <= n; i ++){
			printf("%d", ans[i]);
			if(i < n)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}
