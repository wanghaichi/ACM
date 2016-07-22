#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int a[MAXN], b[MAXN];

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int p = 0;
		int sum = 0;
		int tot = 0; 
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			sum += a[i];
			if (a[i] & 1){
				p++;
				b[p] = a[i];
			}
			else{
				tot += a[i] / 2;
			}
		}
		if (p == 0)
			printf("%d\n", sum);
		else{
			int q = sum / p;
			if (q % 2 == 0) q--;
			printf("%d\n", q);
			/*
			int high = sum / p + 1, low = b[1], mid;
			while(low + 1 < high){
				mid = high + low >> 1;
				int cnt = 0;
				for(int i = 1; i <= p; i++)
					if (b[i] < mid)
						cnt += (mid - b[i] + 1) / 2;
				if (cnt <= tot)
					low = mid;
				else
					high = mid;
			}
			printf("%d\n", low);*/
		}
		/*
		sort(b + 1, b + p + 1);
		int high = sum / n + 1, low = b[1], mid;
		while(low + 1 < high){
			mid = high + low >> 1;
			
		}*/
	}
	return 0;
}
