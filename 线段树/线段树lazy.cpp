#include <iostream>
#include<cstdio>
#include<string.h>

using namespace std;

const int N = 1e5+7;
typedef long long ll;

struct node{
	int lv, rv, num;
}tr[N*4+7];

void build(int root, int l, int r)
{
	tr[root].lv = l;
	tr[root].rv = r;
	tr[root].num = 0;
	if(l == r)
		return;
	int mid = (l+r) >>1;
	build(root<<1, l, mid);
	build(root<<1|1, mid+1, r);
}


void update(int root, int l, int r, int v)
{
	if(tr[root].lv == l && tr[root].rv == r){
		tr[root].num = v;
		return;
	}
	if(tr[root].num != 0){
		update(root<<1,tr[root<<1].lv, tr[root<<1].rv, tr[root].num );
		update(root<<1|1, tr[root<<1|1].lv, tr[root<<1|1].rv, tr[root].num);
		tr[root].num = 0;
	}
	int mid = (tr[root].lv + tr[root].rv) / 2;
	if(l > mid)
		update(root<<1|1, l, r, v);
	else if (r <= mid)
		update(root<<1, l, r, v);
	else{
		update(root<<1, l, mid, v);
		update(root<<1|1, mid+1, r, v);
	}
}
int ans;
void query(int root){
	if(tr[root].num != 0){
		ans += (tr[root].num - 1)*(tr[root].rv - tr[root].lv + 1);
		return;
	}
	if (tr[root].lv == tr[root].rv)
		return;
	query(root<<1);
	query(root<<1|1);
}



int main()
{
	int T, cnt = 1, n, a[N];
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		build(1, 1, n);
		int q;
		scanf("%d", &q);
		ans = n;
		int x, y , v;
		while(q--){
			scanf("%d%d%d", &x, &y, &v);
			update(1, x, y ,v);
		}
		query(1);
		printf("Case %d: The total value of the hook is %d.\n",cnt ++, ans);
	}
	

	return 0;
}
