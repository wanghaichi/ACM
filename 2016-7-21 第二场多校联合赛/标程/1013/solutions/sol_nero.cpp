#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 2000 + 5;
int R[N],C[N];
int K;
int next[N],prev[N];
int perm[4];
int n,m;
int sum[N][N];

inline int tm(int r1,int c1,int r2,int c2) {
    if (r1 > r2) std::swap(r1,r2);
    if (c1 > c2) std::swap(c1,c2);
    return sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
}

int work() {
    for (int i = 0; i < K; ++ i) {
        for (int j = i + 1; j < K; ++ j) {
            if (R[i] > R[j] || R[i] == R[j] && C[i] > C[j]) {
                std::swap(R[i],R[j]);
                std::swap(C[i],C[j]);
            }
        }
    }
    std::vector<int> index(K);
    std::iota(ALL(index),0);
    std::sort(ALL(index),[&](int a,int b) {
                if (C[a] != C[b]) return C[a] < C[b];
                return R[a] < R[b];
            });

    int result = 0;
    for (int i = 0; i < K; ++ i) {
        int last = -1;
        for (int id : index) {
            if (R[id] >= R[i]) {
                prev[id] = last;
                if (last != -1) next[last] = id;
                next[id] = -1;
                last = id;
            }
        }
        std::vector<int> vec;
        for (int j = K - 1; j > i; -- j) {
            if (j < K - 1 && R[j] != R[j + 1]) {
                for (int k = j + 1; k < K && R[k] == R[j + 1]; ++ k) {
                    int a = prev[k],b = next[k];
                    if (a != -1) next[a] = b;
                    if (b != -1) prev[b] = a;
                }
            }
            if ((perm[0] - perm[3]) * (C[i] - C[j]) <= 0) continue;
            int up = std::min(perm[0],perm[3]);
            int down = 3 - std::max(perm[0],perm[3]);
            if (tm(R[i],C[i],R[j],C[j]) != 4 - up - down) continue;
            vec.clear();
            vec.push_back(i);
            vec.push_back(j);
            int a = i,b = j;
            if (C[a] > C[b]) std::swap(a,b);
            for (int w = next[a]; w != b; w = next[w]) {
                if (C[w] == C[prev[w]]) goto boom;
                if (w == -1) {
                    exit(233);
                }
                vec.emplace_back(w);
                if ((int)vec.size() > 4 - up - down) goto boom;
            }
            for (int w = prev[a]; w != -1; w = prev[w],-- up) {
                if (C[w] == C[next[w]]) goto boom;
                if (up == 0) {
                    break;
                }
                vec.emplace_back(w);
            }
            for (int w = next[b]; w != -1; w = next[w],-- down) {
                if (C[w] == C[prev[w]]) goto boom;
                if (down == 0) {
                    break;
                }
                vec.emplace_back(w);
            }

            if (vec.size() == 4 && up == 0 && down == 0) {
                std::sort(ALL(vec),[&](int a,int b) {
                            return R[a] < R[b];
                        });
                if (vec[0] != i || vec[3] != j) goto boom;
                for (int k = 0; k + 1 < 4; ++ k) {
                    if (R[vec[k]] == R[vec[k + 1]]) goto boom;
                    for (int r = k + 1; r < 4; ++ r) {
                        if ((perm[k] - perm[r]) * (C[vec[k]] - C[vec[r]]) <= 0) goto boom;
                    }
                }
                result ++;
            }
            boom:;
        }
    }
    return result;
}

int main() {
    //freopen("data.in","r",stdin);
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        //fprintf(stderr,"ca = %d\n",++ca);
        scanf("%d%d%d",&n,&m,&K);
        for (int i = 0; i < 4; ++ i) {
            scanf("%d",perm + i); perm[i] --;
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                sum[i][j] = 0;
            }
        }
        for (int i = 0; i < K; ++ i) {
            scanf("%d%d",R + i,C + i);
            sum[R[i]][C[i]] ++;
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
        printf("%d\n",work());
    }
}
