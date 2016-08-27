/*************************************************************

FILENAME:                   cf710C.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-27 13:30:37

LAST MODIFIED:         2016-08-27 13:49:25

ID: codeforces 710C 

TYPE: 构造

DETAIL: 给一个奇数，用1到n的全排列构造一个正方形，是的每行没列数的和都是奇数

TATICS: 在中间的45度的正方形中放满奇数，剩下的放偶数

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

int sto[50][50];

int main()
{
    int n;
    scanf("%d", &n);
    int cnt1 = 1, cnt2 = 2;
    for(int i = 1; i <= n / 2 + 1; i ++){
        int j = 1;
        for( ; j <= (n - 2*i+1)/2; j ++){
            printf("%d%c", cnt2, j == n ? '\n' : ' ');
            cnt2 += 2;
        }
        for( ; j <= n - (n-2*i+1)/2; j ++){
            printf("%d%c", cnt1, j == n ? '\n' : ' ');
            cnt1 += 2;
        }
        for( ; j <= n; j ++){
            printf("%d%c", cnt2, j == n ? '\n' : ' ');
            cnt2 += 2;
        }
    }
    for(int i = n/2; i >= 1; i --){
        int j = 1;
        for( ; j <= (n - 2*i+1)/2; j ++){
            printf("%d%c", cnt2, j == n ? '\n' : ' ');
            cnt2 += 2;
        }
        for( ; j <= n - (n-2*i+1)/2; j ++){
            printf("%d%c", cnt1, j == n ? '\n' : ' ');
            cnt1 += 2;
        }
        for( ; j <= n; j ++){
            printf("%d%c", cnt2, j == n ? '\n' : ' ');
            cnt2 += 2;
        }
    }
    

	return 0;
}

