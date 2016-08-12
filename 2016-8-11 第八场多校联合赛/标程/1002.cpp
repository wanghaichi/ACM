#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define base 233
#define mo 1000000007
#define cl(x) memset(x, 0, sizeof(x))
typedef unsigned long long ull;
using namespace std;
void gn(int &x)
{
	x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
}
ull h[maxn];
int n, m, pre[maxn], f[maxn], g[maxn], ei, ans;
int mark[maxn], cir[maxn], ctot, cc, s[maxn];
bool onc[maxn];
int ifr[maxn], inv[maxn];
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int power(int a, int b)
{
	int c = 1;
	for ( ; b; b >>= 1, a = 1ll * a * a % mo)
		if (b & 1) c = 1ll * c * a % mo;
	return c;
}
struct edge{
	int t, nxt;
}e[maxn];
void ae(int a, int b)
{
	e[++ ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int tmp[maxn];
bool cmp(int x, int y){return h[x] < h[y];}
int C(int n, int m)
{
	int ret = ifr[m];
	for (int i = n; i >= n - m + 1; -- i)
		ret = 1ll * ret * (i % mo) % mo;
	return ret;
}
void dfs(int x)
{
	for (int i = g[x]; i; i = e[i].nxt) dfs(e[i].t);
	int tot = 0;
	for (int i = g[x]; i; i = e[i].nxt) tmp[++ tot] = e[i].t;
	sort(tmp + 1, tmp + tot + 1, cmp);
	h[x] = 7;
	for (int i = 1; i <= tot; ++ i)
		(((h[x] *= base) += h[tmp[i]]) ^= h[tmp[i]]) += h[tmp[i]];
	int last; f[x] = m;
	for (int i = 1; i <= tot; i = last){
		for (last = i; last <= tot && h[tmp[last]] == h[tmp[i]]; ++ last);
		f[x] = 1ll * f[x] * C(last - i + f[tmp[i]] - 1, last - i) % mo;
	}
}
int nxt[maxn];
int kmp(int n)
{
	nxt[0] = -1; int x;
	for (int i = 1; i <= n; ++ i){
		x = nxt[i - 1];
		while (x != -1 && s[x + 1] != s[i]) x = nxt[x];
		nxt[i] = x + 1;
	}
	int c = n - nxt[n];
	if (n % c) return -1;
	return c;
}
ull t[maxn], col[maxn];
void solve()
{
	cl(mark); cl(g); cl(onc); ei = ctot = 0;
	gn(n); gn(m);
	for (int i = 1; i <= n; ++ i) gn(pre[i]);
	ifr[0] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; ++ i) inv[i] = (mo - 1ll * (mo / i) * inv[mo % i] % mo) % mo;
	for (int i = 1; i <= n; ++ i) ifr[i] = 1ll * ifr[i - 1] * inv[i] % mo;
	int x;
	for (int i = 1; i <= n; ++ i){
		if (mark[i]) continue;
		for (x = i; ! mark[x]; x = pre[x]) mark[x] = i;
		if (mark[x] != i) continue;
		for (int y = x; ! onc[y]; y = pre[y]) onc[y] = 1, cir[++ ctot] = y;
	}
	for (int i = 1; i <= n; ++ i)
		if (! onc[i]) ae(pre[i], i);
	for (int i = 1; i <= ctot; ++ i) dfs(cir[i]);
	int tot = 0;
	for (int i = 1; i <= ctot; ++ i) t[++ tot] = h[cir[i]];
	sort(t + 1, t + tot + 1);
	col[cc = 1] = t[1];
	for (int i = 2; i <= tot; ++ i)
		if (t[i] != t[i - 1]) col[++ cc] = t[i];
	for (int i = 1; i <= ctot; ++ i) s[i] = lower_bound(col + 1, col + cc + 1, h[cir[i]]) - col;
	int pat = kmp(ctot);
	if (pat == -1){
		ans = 1;
		for (int i = 1; i <= ctot; ++ i)
			ans = 1ll * ans * f[cir[i]] % mo;
	}else{
		int blo = 1;
		for (int i = 1; i <= pat; ++ i)
			blo = 1ll * blo * f[cir[i]] % mo;
		int len = ctot / pat; ans = 0;
		for (int d = 0; d < len; ++ d)
			ans = (ans + power(blo, gcd(d, len))) % mo;
		ans = 1ll * ans * inv[len] % mo;
	}
	printf("%d\n", ans);
}
int T;
int main()
{
	gn(T);
	while (T --) solve();
	return 0;
}
