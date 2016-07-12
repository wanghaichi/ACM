#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>
using namespace std;
const int N = 10000001;
int f[N];
void init()
{
    f[1] = 0;
    memset(f, 0, sizeof(f));
    for(int i = 2; i < N; i ++){
        if(f[i] == 0){
            f[i] = 1;
            for(int j = 2; j * i < N; j ++){
                f[i*j] ++;
            }
        }
    }
}

int main()
{
    int T, cnt = 1;
    scanf("%d", &T);
    init();
    while(T --){
        int a, b, k, ans = 0;
        scanf("%d%d%d", &a, &b, &k);
        for(int i = a; i <= b; i ++){
            if(f[i] == k){
                ans ++;
            }
        }
        printf("Case #%d: %d\n",cnt++,  ans);
    }
    return 0;
}