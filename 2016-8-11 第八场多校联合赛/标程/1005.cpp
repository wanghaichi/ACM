#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<bitset>
#include<utility>
#include<functional>
#include<iomanip>
#include<sstream>
#include<ctime>
#include<cassert>
using namespace std;
#define y0 y0z
#define y1 y1z
#define yn ynz
#define j0 j0z
#define j1 j1z
#define jn jnz
#define tm tmz
#define buli(x) (__builtin_popcountll(x))
#define bur0(x) (__builtin_ctzll(x))
#define bul2(x) (63-__builtin_clzll(x))
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fil(a,b) memset((a),(b),sizeof(a))
#define cl(a) fil(a,0)
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();it++)
#define rep(i,a,b) for (int i=(a),_ed=(b);i<_ed;i++)
#define per(i,a,b) for (int i=(b)-1,_ed=(a);i>=_ed;i--)
#define pw(x) ((ll(1))<<(x))
#define upmo(a,b) (((a)=((a)+(b))%mo)<0?(a)+=mo:(a))
#define mmo(a,b) (((a)=1ll*(a)*(b)%mo)<0?(a)+=mo:(a))
void getre(){int x=0;printf("%d\n",1/x);}
void gettle(){int res=1;while(1)res<<=1;printf("%d\n",res);}
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
template<typename T,typename S>inline bool upmin(T&a,const S&b){return a>b?a=b,1:0;}
template<typename T,typename S>inline bool upmax(T&a,const S&b){return a<b?a=b,1:0;}
template<typename N,typename PN>inline N flo(N a,PN b){return a>=0?a/b:-((-a-1)/b)-1;}
template<typename N,typename PN>inline N cei(N a,PN b){return a>0?(a-1)/b+1:-(-a/b);}
template<typename N>N gcd(N a,N b){return b?gcd(b,a%b):a;}
template<typename N>inline int sgn(N a){return a>0?1:(a<0?-1:0);}
#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define lld "%I64d"
#else
    #define lld "%lld"
#endif
inline void gn(long long&x){
	int sg=1;char c;while(((c=getchar())<'0'||c>'9')&&c!='-');c=='-'?(sg=-1,x=0):(x=c-'0');
	while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';x*=sg;
}
inline void gn(int&x){long long t;gn(t);x=t;}
inline void gn(unsigned long long&x){long long t;gn(t);x=t;}
inline void gn(double&x){double t;scanf("%lf",&t);x=t;}
inline void gn(long double&x){double t;scanf("%lf",&t);x=t;}
inline void gs(char *s){scanf("%s",s);}
inline void gc(char &c){while((c=getchar())>126 || c<33);}
inline void pc(char c){putchar(c);}
#ifdef JCVB
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) 
#endif
typedef long long ll;
typedef double db;
inline ll sqr(ll a){return a*a;}
inline db sqrf(db a){return a*a;}
const int inf=0x3f3f3f3f;
const db pi=3.14159265358979323846264338327950288L;
const db eps=1e-6;
const int mo=0;
int qp(int a,ll b){int n=1;do{if(b&1)n=1ll*n*a%mo;a=1ll*a*a%mo;}while(b>>=1);return n;}
int n,m;
int fac[15];
struct edge{
	int v,next;
}e[51111111];int g[11333333];int etot=0;
int f[11333333];
void ae(int u,int v){
	e[etot].v=v;e[etot].next=g[u];g[u]=etot++;
}
int getid(int *a){
	int arr[15];
	rep(i,1,n+1)arr[i]=1;
	int su=0;
	rep(i,1,n+1){
		int x=a[i];
		arr[x]=0;
		rep(j,1,x)if(arr[j])su+=fac[n-i];
	}
	return su+1;
}
int ord[15];
int cur[15];


void expand(){
	int me=getid(ord);
	rep(i,1,n+1){
		int x=ord[i];
		if(x==1)continue;
		ae(me+(x-1)*fac[n],me+(x-2)*fac[n]);
		rep(j,i+1,n+1)if(ord[j]<x){
			rep(t,1,n+1)cur[t]=ord[t];
			int u=i;
			while(u!=j){
				int v=j;
				for (int k=u+1;k<j;k++)if(cur[k]<x && cur[k]>cur[v])v=k;
				swap(cur[u],cur[v]);
				u=v;
			}
			ae(me+(x-1)*fac[n],getid(cur)+(x-2)*fac[n]);
		}
	}
}
int ned[333333];
int main()
{
#ifdef JCVB
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int _time_jc=clock();
#endif
	fac[0]=1;
	rep(i,1,12)fac[i]=fac[i-1]*i;
	int te;gn(te);
	while(te--){
		gn(n);gn(m);
		int vid=n*fac[n];
		rep(i,1,vid+1)g[i]=-1,f[i]=0;
		etot=0;
		rep(i,1,n+1)ord[i]=i;
		do{
			expand();
		}while(next_permutation(ord+1,ord+1+n));
		rep(t,1,m+1){
			rep(i,1,n+1)gn(ord[i]);
			ned[t]=getid(ord);
			f[ned[t]+(n-1)*fac[n]]++;
		}
		per(u,1,vid+1){
			for (int i=g[u];~i;i=e[i].next)f[e[i].v]+=f[u];
		}
		ll res=0;
		rep(i,1,m+1)res+=f[ned[i]];
		printf(lld"\n",res);
	}
#ifdef JCVB
	debug("time: %d\n",int(clock()-_time_jc));
#endif
	return 0;
}

