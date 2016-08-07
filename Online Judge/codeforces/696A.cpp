/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 07日 星期日 12:35:01 CST

ID:

TYPE:

DETAIL:

TACTICS:

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;

struct node{
	ll u, v, w;
	node(ll _u, ll _v, ll _w):u(_u), v(_v), w(_w){}
};

vector<node> vec;

ll getlca(ll u, ll v){
	while( u != v){
		if(u > v)
			u /= 2;
		else
			v /= 2;
	}
	return u;
}

ll getPath(ll u, ll v){
	ll res = 0;
	while(v != u){
		v /= 2;
		res ++;
	}
	return res;
}

ll getCost(node n, ll u, ll v){
	ll len = getPath(u, v);
	ll tu = n.u;
	ll tv = n.v;
	ll tw = n.w;
	ll tmp = getlca(v, tv);
	if(tmp <= u || tmp <= tu)
		return 0;
	if(tu <= u){
		return getPath(u, tmp) * tw;
	}
	else{
		return getPath(tu, tmp) * tw;
	}
}

int main()
{	
	int T, k;
	ll u, v, w;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &k);
		if(k == 1){
			scanf("%I64d%I64d%I64d", &u, &v, &w);
			ll tmp = getlca(u , v);
			if(tmp != u){
				vec.push_back(node(tmp, u, w));
			}
			if(tmp != v){
				vec.push_back(node(tmp, v, w));
			}
		}else {
			ll ans = 0;
			scanf("%I64d%I64d", &u, &v);
			ll tmp = getlca(u, v);
			ll len1 = 0, len2 = 0;
			for(int i = 0; i < vec.size(); i ++){
				ans += getCost(vec[i], tmp, u);
				ans += getCost(vec[i], tmp, v);
			}
			printf("%I64d\n", ans);
		}
	}
	return 0;
}








