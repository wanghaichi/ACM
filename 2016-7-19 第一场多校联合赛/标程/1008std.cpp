#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std ;

const int MAXN = 300000 ;
const int MOD  = 313 ;
const double Pi2 = 2*3.14159265358979323846264338327950288 ;

int n , a[MAXN] , F[MAXN] ;
int fft_a[MAXN], fft_b[MAXN], fft_c[MAXN];

/***FFT***/
#define CpX pair<double,double>
#define IS_(x,t) x.first=cos(t), x.second=sin(t)
#define IS(x,u,v) x.first=u, x.second=v
#define Add(x,u,v) x.first=u.first+v.first, x.second=u.second+v.second
#define Minus(x,u,v) x.first=u.first-v.first, x.second=u.second-v.second
#define Mul_(x,u,v) x.first=u.first*v.first-u.second*v.second, x.second=u.first*v.second+u.second*v.first
void Mul(CpX &x,CpX u,CpX v) { x.first=u.first*v.first-u.second*v.second, x.second=u.first*v.second+u.second*v.first; }
int Size;
int Rev(int x) {
    int T = Size, Ans = 0;
    for (; T > 1; T >>= 1, x >>= 1) Ans = (Ans << 1) | (x & 1);
    return Ans;
}
#define FFT_d(A,Ret,T) \
    for(int i=0;i<Size;++i) Ret[Rev(i)]=A[i]; \
    for(int i=2;i<=Size;i<<=1){ \
        IS_(wm,T*Pi2/(double)i); \
        for(int k=0;k<Size;k+=i){ \
            IS(w,1.0,0.0); \
            for(int j=0;(j<<1)<i;j++) \
                Mul_(t,w,Ret[k+j+(i>>1)]), u=Ret[k+j], Add(Ret[k+j],u,t), Minus(Ret[k+j+(i>>1)],u,t), Mul(w,w,wm); \
        } \
    }
CpX Ret1[MAXN], Ret2[MAXN], wm , w , t , u ;
CpX ArrA[MAXN], ArrB[MAXN], ArrC[MAXN] ;
void FFT_Multiply() {
    int _Size = Size ; Size = 1 ;
    while (Size <= _Size) Size <<= 1 ; Size <<= 1; // Double it for multiplication
    for (int i = 0; i < _Size; i++) IS(ArrA[i] , fft_a[i] , 0.0) ;
    for (int i = 0; i < _Size; i++) IS(ArrB[i] , fft_b[i] , 0.0) ;
	for (int i = _Size; i < Size; i++) IS(ArrA[i] , 0.0 , 0.0) ;
	for (int i = _Size; i < Size; i++) IS(ArrB[i] , 0.0 , 0.0) ;
	FFT_d(ArrA,Ret1,1); FFT_d(ArrB,Ret2,1);
    for (int i = 0; i < Size; i ++) Mul_(ArrC[i] , Ret1[i] , Ret2[i]);
    FFT_d(ArrC,Ret1,-1);
    for (int i = 0; i < Size; i ++) Ret1[i].first/=(double)Size ;
    for (int i = 0; i < Size; i ++) fft_c[i] = (int)(Ret1[i].first+0.5) % MOD;
}
/*********/

void fold(int l) {
    if ( l <= 512 ) {
        for (int i = 0; i < l * 2; ++i) fft_c[i] = 0;
        for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j)
            fft_c[i + j] = (fft_c[i + j] +  fft_a[i] * fft_b[j]) % MOD;
    } else {
        Size = l;
        for (int i = l; i < l * 2; ++i) fft_a[i] = fft_b[i] = 0;
        FFT_Multiply();
    }
}

void dealfold( int l1 , int r1 , int l2 , int r2 , int l3 , int r3 ) {
    if ( l1 == 1 && l2 == 1 ) {
        int l = r1 - l1 + 2 ;
        fft_a[0] = 0 ; for ( int i = l1 ; i <= r1 ; i ++ ) fft_a[i-l1+1] = a[i] ;
        fft_b[0] = 0 ; for ( int i = l2 ; i <= r2 ; i ++ ) fft_b[i-l2+1] = F[i] ;
        fold(l) ;
        for ( int i = l3 ; i <= r3 ; i ++ ) F[i] = (F[i] + fft_c[l+i-l3]) % MOD ;
    } else {
        int l = (r1 - l1 + 1)*2 + 1 ;
        fft_a[0] = 0 ; for ( int i = 1 ; i < l ; i ++ ) fft_a[i] = a[i+l1-1] ;
        fft_b[0] = 0 ; for ( int i = 1 ; i < l ; i ++ ) fft_b[i] = 0 ;
                       for ( int i = l2 ; i <= r2 ; i ++ ) fft_b[i-l2+1] = F[i] ;
        fold(l) ;
        for ( int i = l3 ; i <= r3 ; i ++ ) F[i] = (F[i] + fft_c[r1 - l1 + 2 + i - l3]) % MOD ;

        l = (r1 - l1 + 1)*2 + 1 ;
        fft_a[0] = 0 ; for ( int i = 1 ; i < l ; i ++ ) fft_a[i] = 0 ;
                       for ( int i = l2 ; i <= r2 ; i ++ ) fft_a[i-l2+1] = a[i] ;
        fft_b[0] = 0 ; for ( int i = 1 ; i < l ; i ++ ) fft_b[i] = F[i+l1-1] ;
        fold(l) ;
        for ( int i = l3 ; i <= r3 ; i ++ ) F[i] = (F[i] + fft_c[r1 - l1 + 2 + i - l3]) % MOD ;
    }
}
void Solve( int l , int r ) {
    if ( l < r ) {
        int mid = (l+r) >> 1 ;
        Solve( l , mid ) ;
        dealfold( 1 , mid-l+1 , l , mid , mid+1 , r ) ;
        Solve( mid+1 , r ) ;
    } else
        F[l] = (F[l] + a[l]) % MOD ;
}
int main() {
   // freopen("input.txt", "r", stdin) ;
    //freopen("output.txt", "w", stdout) ;
    while ( 1 == scanf("%d" , &n) && n ) {
        int u = 1 ; for ( ; u < n ; u *= 2 ) ;
        for ( int i = 1 ; i <= n ; i ++ ) scanf("%d" , &a[i]) , a[i] %= MOD ;
        for ( int i = 1 ; i <= u ; i ++ ) F[i] = 0 ;
        Solve( 1 , u ) ;
        printf("%d\n" , F[n]) ;
    }
}
