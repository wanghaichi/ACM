#include<iostream>
#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;
const int N = 25000;
struct node{
	int lv, rv;
	bool vis;
}tr[3*N];
bool flag;
struct sto{
	int pos, num;
}post[N];


void creat(int lv,int  rv,int root)
{
    tr[root].lv = lv;
    tr[root].rv = rv;
    tr[root].vis = false;
	if(lv == rv){
		return;
	}
	int mid = (lv+rv)>>1;
	creat(lv, mid, root<<1);
	creat(mid+1, rv, root<<1|1);
}

void query(int l,int r, int root)
{
	if(tr[root].vis)
		return;

	if(tr[root].lv == l && tr[root].rv == r){
		tr[root].vis = true;
		flag = true;
		return;
	}
	int mid = (tr[root].lv + tr[root].rv)>>1;
	if(r <= mid)
		query(l, r, root<<1);
	else if(l > mid)
		query(l, r, root<<1|1);
	else{
		query(l, mid, root<<1);
		query(mid+1, r, root<<1|1);
	}
	tr[root].vis = tr[root<<1].vis & tr[root<<1|1].vis;
}

bool cmp1(sto s1, sto s2){
	return s1.pos < s2.pos;
}

bool cmp2(sto s1, sto s2){
	if(s1.num == s2.num)
		return s1.pos < s2.pos;
	return s1.num > s2.num;
}



int main()
{
	int T, x, y, n;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%d%d", &post[2*i].pos, &post[2*i+1].pos);
			post[2*i].num = post[2*i+1].num = i;
		}
		sort(post, post+2*n, cmp1);
		int k = 0, pre = 0;
		for(int i = 0; i < 2*n; i ++){
			if(post[i].pos != pre){
				pre = post[i].pos;
				post[i].pos = ++k;
			}
			else
				post[i].pos = k;
		}

		creat(1, k, 1);
		sort(post, post+2*n, cmp2);
		int ans = 0;
		for(int i = 0; i < 2*n; i += 2){
			int l = post[i].pos;
			int r = post[i+1].pos;
			flag = false;
			query(l, r, 1);
			if(flag)
				ans ++;
		}
		printf("%d\n", ans);

	}



	return 0;
}
