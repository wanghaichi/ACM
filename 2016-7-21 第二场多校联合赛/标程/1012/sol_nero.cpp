#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 100000 + 5;
const int M = 5000 + 5;
int n,m;
char s[N],t[M];

std::bitset<N> bs[3],w[26];

void work() {
    for (int i = 0; i < 3; ++ i) {
        bs[i].reset();
    }
    for (int i = 0; i < 26; ++ i) {
        w[i].reset();
    }
    for (int i = 0; i < n; ++ i) {
        w[s[i] - 'a'][i] = 1;
    }
    for (int i = 0; i < n; ++ i) {
        bs[0][i] = 1;
    }
    for (int i = 0; i < m; ++ i) {
        int a = t[i] - 'a';
        bs[(i + 1) % 3] = bs[i % 3] & w[a] >> i;
        if (i > 0) {
            int b = t[i - 1] - 'a';
            bs[(i + 1) % 3] |= bs[(i + 2) % 3] & w[a] >> i - 1 & w[b] >> i;
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (bs[m % 3][i] == 1) putchar('1');
        else putchar('0');
    }
    puts("");
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        scanf("%s%s",s,t);
        work();
    }
}
