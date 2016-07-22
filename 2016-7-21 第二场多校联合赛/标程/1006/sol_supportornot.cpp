#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std ;

#define clr( a , x ) memset ( a , x , sizeof a )

const int MAXN = 200005 ;
const int mod = 1e9 + 7 ;

vector < int > G[MAXN] , V[MAXN] , E[MAXN] ;
int n , m ;
int w[MAXN] , iw[MAXN] ;
int dfn[MAXN] , low[MAXN] ;
int S[MAXN] , top ;
int is[MAXN] ;
int dfs_clock ;
int bcc_cnt ;
int belong[MAXN] , vis[MAXN] ;
int pre[MAXN] ;
int dp[MAXN] ;

void init () {
	top = 0 ;
	bcc_cnt = n ;
	dfs_clock = 0 ;
	clr ( dfn , 0 ) ;
	clr ( is , 0 ) ;
	clr ( vis , 0 ) ;
}

int powmod ( int x , int n ) {
	int res = 1 ;
	while ( n ) {
		if ( n & 1 ) res = 1LL * res * x % mod ;
		x = 1LL * x * x % mod ;
		n >>= 1 ;
	}
	return res ;
}

void tarjan ( int u , int f ) {
	dfn[u] = low[u] = ++ dfs_clock ;
	S[top ++] = u ;
	int son = 0 ;
	for ( int i = 0 ; i < G[u].size () ; ++ i ) {
		int v = G[u][i] ;
		if ( !dfn[v] ) {
			++ son ;
			tarjan ( v , u ) ;
			low[u] = min ( low[u] , low[v] ) ;
			if ( low[v] >= dfn[u] ) {
				is[u] = 1 ;
				++ bcc_cnt ;
				w[bcc_cnt] = 1 ;
				V[bcc_cnt].clear () ;
				while ( 1 ) {
					int x = S[-- top] ;
					w[bcc_cnt] = 1LL * w[bcc_cnt] * w[x] % mod ;
					V[bcc_cnt].push_back ( x ) ;
					if ( x == v ) break ;
				}
				V[bcc_cnt].push_back ( u ) ;
				w[bcc_cnt] = 1LL * w[bcc_cnt] * w[u] % mod ;
			}
		} else if ( v != f ) low[u] = min ( low[u] , dfn[v] ) ;
	}
	if ( f < 0 && son == 1 ) is[u] = 0 ;
}

void dfs ( int u , int f , int o ) {
	pre[u] = f ;
	belong[u] = o ;
	vis[u] = 1 ;
	dp[u] = w[u] ;
	for ( int i = 0 ; i < E[u].size () ; ++ i ) {
		int v = E[u][i] ;
		if ( v == f ) continue ;
		dfs ( v , u , o ) ;
		dp[u] = 1LL * dp[u] * dp[v] % mod ;
	}
	if ( u > n ) {
		for ( int i = 0 ; i < V[u].size () ; ++ i ) {
			belong[V[u][i]] = o ;
			vis[V[u][i]] = 1 ;
		}
	}
}

void solve () {
	scanf ( "%d%d" , &n , &m ) ;
	init () ;
	for ( int i = 1 ; i <= n ; ++ i ) {
		G[i].clear () ;
		scanf ( "%d" , &w[i] ) ;
		iw[i] = powmod ( w[i] , mod - 2 ) ;
	}
	for ( int i = 0 ; i < m ; ++ i ) {
		int u , v ;
		scanf ( "%d%d" , &u , &v ) ;
		G[u].push_back ( v ) ;
		G[v].push_back ( u ) ;
	}
	for ( int i = 1 ; i <= n ; ++ i ) if ( !dfn[i] ) {
		tarjan ( i , -1 ) ;
	}
	for ( int i = 1 ; i <= bcc_cnt ; ++ i ) {
		E[i].clear () ;
	}
	for ( int i = n + 1 ; i <= bcc_cnt ; ++ i ) {
		for ( int j = 0 ; j < V[i].size () ; ++ j ) {
			int v = V[i][j] ;
			if ( is[v] ) {
				E[i].push_back ( v ) ;
				E[v].push_back ( i ) ;
				w[i] = 1LL * w[i] * iw[v] % mod ;
			}
		}
		iw[i] = powmod ( iw[i] , mod - 2 ) ;
	}
	int ans = 0 , res = 0 ;
	for ( int i = 1 ; i <= n ; ++ i ) if ( !vis[i] && is[i] ) {
		dfs ( i , -1 , i ) ;
		ans = ( ans + dp[i] ) % mod ;
	}
	//下面这个没用
	for ( int i = n + 1 ; i <= bcc_cnt ; ++ i ) if ( !vis[i] ) {
		dfs ( i , -1 , i ) ;
		ans = ( ans + dp[i] ) % mod ;
	}
	
	for ( int i = 1 ; i <= n ; ++ i ) if ( !vis[i] ) {
		dfs ( i , -1 , i ) ;
		ans = ( ans + dp[i] ) % mod ;
	}
	
	for ( int i = 1 ; i <= n ; ++ i ) {
		int x = belong[i] ;
		int t = ans ;
		ans = ( ans - dp[x] + mod ) % mod ;
		if ( !is[i] ) {
			if ( i != belong[i] ) ans = ( ans + 1LL * dp[x] * iw[i] % mod ) % mod ;
		} else {
			int tmp = 1LL * dp[x] * powmod ( dp[i] , mod - 2 ) % mod ;
			if ( i != belong[i] ) ans = ( ans + tmp ) % mod ;
			for ( int j = 0 ; j < E[i].size () ; ++ j ) {
				int v = E[i][j] ;
				if ( v == pre[i] ) continue ;
				ans = ( ans + dp[v] ) % mod ;
			}
		}
		res = ( res + 1LL * i * ans ) % mod ;
		ans = t ;
	}
	printf ( "%d\n" , res ) ;
}

int main () {
	int T ;
	scanf ( "%d" , &T ) ;
	for ( int i = 1 ; i <= T ; ++ i ) {
		solve () ;
	}
	return 0 ;
}
