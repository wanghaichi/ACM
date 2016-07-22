#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()
#define showtime printf("time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)

const int N = 1000 + 5;
const int M = 500000 + 5;
int A[N],n,m;
std::pair<int,int> queries[M];
bool result[M];

struct Event {
    int p,l,r,s;
    bool operator < (const Event &rhs) const {
        return p < rhs.p;
    }
};

struct OO : std::vector<int> {
    int get(int x) const {
        return std::lower_bound(begin(),end(),x) - begin();
    }

    void done() {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
    }
} ss;

struct Fenwick {
    std::vector<int> C;

    Fenwick(int _n = 0) {
        C.assign(_n,0);
    }

    void modify(int p,int dt) {
        for (int i = p; i < C.size(); i += ~i & i + 1) C[i] += dt;
    }

    int query(int p) {
        if (p >= C.size()) return 0;
        int ret = 0;
        for (int i = p; i >= 0; i -= ~i & i + 1) ret += C[i];
        return ret;
    }
};

bool cmp(int a,int b) {
    return queries[a].first < queries[b].first;
}

void work() {
    A[n + 1] = 0;
    std::vector<Event> events;
    for (int i = 1; i <= n + 1; ++ i) {
        int sa = 0,sb = 0;
        for (int j = i; j <= n + 1; ++ j) {
            int al = sa,bl = sb;
            int ar = sa,br = sb;
            if (i & 1) br += A[i - 1];
            else ar += A[i - 1];
            if (j & 1) ar += A[j];
            else br += A[j];
            events.push_back(Event{al,bl,br,1});
            events.push_back(Event{ar + 1,bl,br,-1});
            if (j & 1) sa += A[j];
            else sb += A[j];
        }
    }
    std::sort(ALL(events));
    std::vector<int> index(m);
    std::iota(ALL(index),0);
    std::sort(ALL(index),cmp);
    ss.clear();
    for (const auto &e : events) {
        //ss.push_back(e.l - 1);
        ss.push_back(e.l);
        ss.push_back(e.r);
    }
    for (int i = 0; i < m; ++ i) {
        ss.push_back(queries[i].second);
    }
    ss.done();
    Fenwick bit(ss.size() + 1);
    for (int i = 0,j = 0; i < m; ++ i) {
        int id = index[i];
        int a = queries[id].first,b = queries[id].second;
        while (j < (int)events.size() && events[j].p <= a) {
            bit.modify(ss.get(events[j].l),events[j].s);
            bit.modify(ss.get(events[j].r) + 1,-events[j].s);
            ++ j;
        }
        result[id] = bit.query(ss.get(b)) > 0;
    }
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d",A + i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d",&queries[i].first,&queries[i].second);
            result[i] = false;
        }
        work();
        for (int i = 0; i < m; ++ i) {
            printf("%d",result[i]);
        }
        puts("");
    }
}
