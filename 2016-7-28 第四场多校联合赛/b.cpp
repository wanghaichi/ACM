#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;
typedef long long ll;

char a[N], b[N];
int Next[N];
int n, m, T, len;
vector<int> sto;
ll dp[N], yunhao[N];
void getNext(){
	int j = 0, k = -1;
	Next[0] = -1;
	while(b[j] != '\0'){
		while(k != -1 && b[j] != b[k])
			k = Next[k];
		if(b[++j] == b[++k])
			Next[j] = Next[k];
		else
			Next[j] = k;
	}
}

void kmp(){
	//ans.clear();
	getNext();
	int ans = 0, i = 0, j = 0;
	while(a[i] != '\0'){
		while(j != -1 && a[i] != b[j])
			j = Next[j];
		i++;
		j++;
		if(j != -1 && b[j] == '\0'){
			sto.push_back(i - j);
			i = i - j + 1;
			j = 0;
		}
	}
}

ll zuhe(ll a, ll b){
	if (a > b - a)
	{
		a = b - a;
	}
	ll res = 1;
	for(int i = 0; i < a; i ++){
		res = res * (b - i) / (i + 1);
		res %= mod;
	}
	return res;
}

int main()
{
	int T, cnt = 1;
	scanf("%d", &T);
	while(T --){
		sto.clear();
		scanf("%s%s", a, b);
		kmp();
		if(sto.size() == 0){
			printf("Case #%d: 1\n", cnt++);
			continue;
		}
		int len = strlen(b);
		int slen = sto.size();
		memset(yunhao, -1, sizeof(yunhao));
		for(int i = 1; i < slen; i ++){
			for(int j = i - 1; j >= 0; j --){
				if(sto[j] + len <= sto[i]){
					yunhao[i] = j;
					break;
				}
			}
		}
		dp[0] = 2;
		for(int i = 1; i < slen; i++){
			if(sto[i] - sto[i-1] >= len){
				dp[i] = dp[i-1] * 2;
				dp[i] %= mod;
			}
			else{
				dp[i] = dp[i-1];
				if(yunhao[i] == -1){
					dp[i] += 1;
					dp[i] %= mod;
				}
				else{
					dp[i] += dp[yunhao[i]];
					dp[i] %= mod;
				}
			}
		}
		printf("Case #%d: %I64d\n",cnt++, dp[slen-1]);

	}
	return 0;
}

