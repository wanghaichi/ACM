/*************************************************************

FILENAME:                   hdu5510.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-10-02 14:54:16

LAST MODIFIED:         2016-10-02 15:13:50

ID: 

TYPE: 

DETAIL: 

TATICS: 

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

int Next[2010];

void getNext(char *s){
    int j = 0, k = -1;
    Next[0] = -1;
    while(s[j] != '\0'){
        while(k != -1 && s[j] != s[k]){
            k = Next[k];
        }
        if(s[++j] == s[++k]){
            Next[j] = Next[k];
        }
        else
            Next[j] = k;
    }
}
int kmp(char *s, char *p){
    getNext(s);
    int i = 0, j = 0;
    while(p[i] != '\0'){
        while(j != -1 && p[i] != s[j]){
            j = Next[j];
        }
        i ++; j ++;
        if(j != -1 && s[j] == '\0'){
            return i - j + 1;
        }
    }
    return -1;
}



int main()
{
    int T, n, ct = 1;
    char s[510][2010];
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%s", s[i]);
        }
        int l = 1, r, ans = -1;
        for(r = 2; r <= n; r ++){
            while(l < r){
                if(kmp(s[l], s[r]) == -1){
                    ans = r;
                    break;
                }
                else{
                    l ++;
                }
            }
        }
        printf("Case #%d: %d\n", ct++ , ans);
    }


	return 0;
}

