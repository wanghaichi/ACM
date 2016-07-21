#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
int sg[(1<<20)+1000];
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    for(int i = 1;i < (1<<20); i++){
        int h[25];
        memset(h, -1, sizeof(h));
        int last = -1;
        for(int j = 0; j < 20; j++){

            if(!((i >> j) & 1))
                last = j;
            if(((i >> j) & 1)){
                if(last != -1){
                    h[sg[(i ^ (1 << j)) ^ (1 << last)]]=1;
                }
            }
        }
        int j=0;
        while(h[j] != -1) j++;
        sg[i]=j;
    }
    int T;
    scanf("%d", &T);
    while(T--){
        int n, tmp, m, ans=0;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%d", &m);
            tmp = 0;
            for(int j = 1; j <= m; j++){
                int x;
                scanf("%d", &x);
                tmp ^= 1 << (20 - x);
            }
            ans ^= sg[tmp];

        }
        if(ans)
            puts("YES");
        else
            puts("NO");
    }
}
