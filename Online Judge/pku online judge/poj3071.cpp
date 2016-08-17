/*************************************************************

FILENAME:                   poj3071.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-17 15:14:00

LAST MODIFIED:         2016-08-17 17:55:37

ID: poj 3071

TYPE: 概率 模拟

DETAIL: 给出2^n个人，两两比赛，给出任意两个人比赛获胜的概率，求最终获胜概率最高的人

TATICS: 模拟

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

double ans[150][2], p[150][150];
int po[10];
int main()
{
    po[0] = 1;
    for(int i = 1; i < 10; i ++)
        po[i] = po[i-1] * 2;
    int n;
    while(~scanf("%d", &n) && n != -1){
        for(int i = 0; i < po[n]; i ++){
            for(int j = 0; j < po[n]; j ++){
                scanf("%lf", &p[i][j]);
            }
        }
        CL(ans);
        for(int i = 0; i < po[n]; i ++)
            ans[i][0] = 1;
        for(int k = 1; k <= n; k ++){
            for(int i = 0; i < po[n-k]; i ++){
                for(int j = i * po[k]; j < i * po[k] + po[k]; j ++){
                    if(j < i*po[k] + po[k-1]){
                        for(int m = i*po[k] + po[k-1]; m < i*po[k] + po[k]; m ++){
                            ans[j][k&1] += (ans[j][(k-1)&1] * p[j][m] * ans[m][(k-1)&1]);
                        }
                    }
                    else{
                        for(int m = i*po[k]; m < i*po[k] + po[k-1]; m ++){
                            ans[j][k&1] += (ans[j][(k-1)&1] * p[j][m] * ans[m][(k-1)&1]);
                        }
                    }
                }
                /*for(int i = 0; i < po[n]; i ++){*/
                    //printf("%f ", ans[i][k&1]);
                //}
                /*printf("\n");*/
            }
            for(int i = 0; i < po[n]; i ++){
                ans[i][(k-1)&1] = 0;
            }
          /*  printf("%d\n", k);*/
            //for(int i = 0; i < po[n]; i ++){
                //printf("%f ", ans[i][k&1]);
            //}
            /*puts("");*/
        }
        double res = 0;
        int pos = 0;
        for(int i = 0; i < po[n]; i ++){
            if(res < ans[i][n&1]){
                res = ans[i][n&1];
                pos = i + 1;
            }
        }
        printf("%d\n", pos);
    }
    

	return 0;
}

