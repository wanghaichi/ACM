/**************hdu2594************************

给定字符串s1和s2，求s1的的前缀与s2的后缀最长公共部分
将s1与s2拼接成s3，求s3的next数组即可。注意在拼接中间加上分隔符

**********************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;
typedef long long ll;
int Next[N];
void getNext(char b[]){
	int j = 0, k = -1;
	Next[0] = -1;
	while(b[j] != '\0'){
		while(k != -1 && b[j] != b[k])
			k = Next[k];
		Next[++j] = ++k;
	}
}

char s2[N], s1[N], s3[N];
int main()
{
	while(~scanf("%s%s", s1, s2)){
		int i, j;
		//字符串操作，复制和添加
		strcpy(s3, s1);
		strcat(s3, "*");
		strcat(s3, s2);
		getNext(s3);
		int len = strlen(s3);
		int ans = Next[len];
		if(ans <= 0)
			puts("0");
		else{
			for(int k = 0; k < ans; k ++)
				putchar(s3[k]);
			printf(" %d\n", ans);
		}
	}
	return 0;
}
