#include <set>
#include <map>
#include <queue>
#include <deque>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

#define dprint(expr) fprintf(stderr, #expr " = %d\n", expr)
#define MP make_pair
#define PB push_back

using namespace std;

typedef long long LL;
typedef pair <int, int> PII;

const int N = 1e5 + 7;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const double EPS = 1e-6;
const double PI = acos(-1.0);

vector <PII> gcd[N];

map <int, LL> Ans;

int n;

int num[N];

int main(void){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T, Test = 0;
	scanf("%d", &T);
	while (T--) {
		//cerr << T << endl;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &num[i]);
		}
		Ans.clear();
		for (int k = 1; k <= n; ++k) {
			int last = 0;
			for (int i = 0; i < gcd[k - 1].size(); ++i) {
				int u = gcd[k - 1][i].first, v = gcd[k - 1][i].second;
				int g = __gcd(u, num[k]);
				if (g == last) continue;
				last = g;
				gcd[k].PB(MP(g, v));
			}
			if (num[k] != last) {
				gcd[k].PB(MP(num[k], k));
			}
			for (int i = 0; i < gcd[k].size(); ++i) {
				Ans[gcd[k][i].first] += (i == gcd[k].size() - 1 ? k + 1 : gcd[k][i + 1].second) - gcd[k][i].second;
			}
		}
		int Q;
		scanf("%d", &Q);
		printf("Case #%d:\n", ++Test);
		while (Q--) {
			int u, v, k;
			scanf("%d%d", &u, &v);
			for (k = 0; k < gcd[v].size(); ++k)
				if (gcd[v][k].second > u)
					break;
//			for (int i = 0; i < gcd[v].size(); ++i) {
//				printf("%d -> %d\n", i, gcd[v][i]);
//			}
			printf("%d %I64d\n", gcd[v][k - 1].first, Ans[gcd[v][k - 1].first]);
		}
		for (int i = 0; i <= n; ++i)
			gcd[i].clear();
	}
	return 0;
}
