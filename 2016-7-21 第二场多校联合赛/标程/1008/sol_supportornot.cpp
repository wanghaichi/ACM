#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std ;

#define clr( a , x ) memset ( a , x , sizeof a )

const int MAXN = 2000005 ;

struct Seg { 
	int x1 , x2 , y , f ;
	Seg () {}
	Seg ( int x1 , int x2 , int y , int f ) : x1 ( x1 ) , x2 ( x2 ) , y ( y ) , f ( f ) {}
	bool operator < ( const Seg& a ) const {
		return y < a.y ;
	}
} ;

struct Node {
	int x , y , idx ;
	bool operator < ( const Node& a ) const {
		return y < a.y ;
	}
} ;


Seg seg[MAXN] ;
Node nod[MAXN] ;
int val[MAXN] ;
int cnt ;
int X[MAXN] , cntx ;
int n , m ;
int ans[MAXN] ;
int c[MAXN] ;

void addedge ( int x1 , int x2 , int y1 , int y2 ) {
	seg[cnt ++] = Seg ( x1 , x2 , y1 , 1 ) ;
	seg[cnt ++] = Seg ( x1 , x2 , y2 , -1 ) ;
	X[++ cntx] = x1 ;
	X[++ cntx] = x2 ;
}

int unique ( int a[] , int n ) {
	sort ( a + 1 , a + n + 1 ) ;
	int c = 1 ;
	for ( int i = 2 ; i <= n ; ++ i ) {
		if ( a[i] != a[i - 1] ) a[++ c] = a[i] ;
	}
	return c ;
}

int search ( int x , int a[] , int l , int r ) {
	while ( l < r ) {
		int m = l + r >> 1 ;
		if ( a[m] >= x ) r = m ;
		else l = m + 1 ;
	}
	return l ;
}

void add ( int x , int v ) {
	for ( int i = x ; i ; i -= i & -i ) {
		c[i] += v ;
	}
}

int sum ( int x , int res = 0 ) {
	for ( int i = x ; i <= cntx ; i += i & -i ) {
		res += c[i] ;
	}
	return res ;
}

void solve () {
	cnt = cntx = 0 ;
	scanf ( "%d%d" , &n , &m ) ;
	for ( int i = 1 ; i <= n ; ++ i ) {
		scanf ( "%d" , &val[i] ) ;
	}
	for ( int i = 1 ; i <= n ; ++ i ) {
		int x = 0 , y = 0 ;
		if ( i & 1 ) addedge ( 0 , val[i] , 0 , 1 ) ;
		else addedge ( 0 , 0 , 0 , val[i] + 1 ) ;
		for ( int j = i + 1 ; j <= n ; ++ j ) {
			if ( i & 1 ) {
				if ( j & 1 ) addedge ( x , x + val[i] + val[j] , y , y + 1 ) ;
				else addedge ( x , x + val[i] , y , y + val[j] + 1 ) ;
			} else {
				if ( j & 1 ) addedge ( x , x + val[j] , y , y + val[i] + 1 ) ;
				else addedge ( x , x , y , y + val[i] + val[j] + 1 ) ;
			}
			if ( j & 1 ) x += val[j] ;
			else y += val[j] ;
		}

	}
	for ( int i = 0 ; i < m ; ++ i ) {
		scanf ( "%d%d" , &nod[i].x , &nod[i].y ) ;
		nod[i].idx = i ;
		X[++ cntx] = nod[i].x ;
	}
	cntx = unique ( X , cntx ) ;
	for ( int i = 1 ; i <= cntx ; ++ i ) {
		c[i] = 0 ;
	}
	for ( int i = 0 ; i < cnt ; ++ i ) {
		seg[i].x1 = search ( seg[i].x1 , X , 1 , cntx ) ;
		seg[i].x2 = search ( seg[i].x2 , X , 1 , cntx ) ;
	}
	for ( int i = 0 ; i < m ; ++ i ) {
		nod[i].x = search ( nod[i].x , X , 1 , cntx ) ;
	}
	sort ( seg , seg + cnt ) ;
	sort ( nod , nod + m ) ;
	for ( int i = 0 , j = 0 ; i < m ; ++ i ) {
		while ( j < cnt && seg[j].y <= nod[i].y ) {
			add ( seg[j].x1 - 1 , -seg[j].f ) ;
			add ( seg[j].x2 , seg[j].f ) ;
			++ j ;
		}
		ans[nod[i].idx] = sum ( nod[i].x ) > 0 ;
	}
	for ( int i = 0 ; i < m ; ++ i ) {
		printf ( "%d" , ans[i] ) ;
	}
	printf ( "\n" ) ;
}

int main () {
	int T ;
	scanf ( "%d" , &T ) ;
	for ( int i = 1 ; i <= T ; ++ i ) {
		solve () ;
	}
	return 0 ;
}
