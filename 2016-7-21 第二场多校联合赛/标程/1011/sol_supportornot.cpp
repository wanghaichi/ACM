#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std ;

#define clr( a , x ) memset ( a , x , sizeof a )

void solve () {
	int c = 0 , x , n ;
	long long num = 0 ;
	scanf ( "%d" , &n ) ;
	for ( int i = 1 ; i <= n ; ++ i ) {
		scanf ( "%d" , &x ) ;
		num += x / 2 ;
		if ( x & 1 ) c ++ ;
	}
	if ( !c ) printf ( "%I64d\n" , num * 2 ) ;
	else printf ( "%I64d\n" , 1 + ( num / c ) * 2 ) ;
}

int main () {
	int T ;
	scanf ( "%d" , &T ) ;
	for ( int i = 1 ; i <= T ; ++ i ) {
		solve () ;
	}
	return 0 ;
}
