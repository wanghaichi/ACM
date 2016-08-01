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

char s[110];

int main()
{
	int T, n;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		scanf("%s", s);
		stack<char> sta;
		sta.push(s[0]);
		int ans = n;
		for(int i = 1; i < n; i ++){
			if(s[i] == '('){
				sta.push(s[i]);
			}
			else{
				if(!sta.empty() && sta.top() == '('){
					sta.pop();
				}
				else
					sta.push(s[i]);
			}
		}
		int k1 = 0, k2 = 0;
		while(!sta.empty()){
			if(sta.top() == ')'){
				k2 ++;
			}
			else{
				k1 ++;
			}
			sta.pop();
		}
		if(k1 % 2 == 1){
			printf("%d\n", k1/2 + k2/2 + 2);
		}
		else{
			printf("%d\n", k1/2 + k2/2);
		}
	}
	return 0;
}

