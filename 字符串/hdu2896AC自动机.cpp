/**********HDU2896**************
给出n个模式串
给出m个目标串
对于每个目标串，求出有多少个模式串出现过，分别是什么


******************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const int maxn = 1e5+7, K = 93;
const int mod = 1e9+7;
typedef long long ll;

set<int> net;
set<int>::iterator it;
struct node{
	node* ch[K], *fail;
	int match;
	void clear(){
		memset(ch, 0, sizeof(ch));
		fail = 0;
		match = 0;
	}
};

//node* que[maxn];

node nodes[maxn], *root, *superRoot, *cur;

node* newNode(){
	cur->clear();
	return cur++;
}

void clear(){
	cur = nodes;
	superRoot = newNode();
	root = newNode();
	root->fail = superRoot;
	for(int i = 0; i < K; i ++)
		superRoot->ch[i] = root;
	superRoot->match = -1;
}

void insert(char* s, int pos){
	node* t = root;
	for(; *s; s++){
		int x = *s - 33;
		if(t->ch[x] == NULL)
			t->ch[x] = newNode();
		t = t->ch[x];
	}
	t->match = pos;
}


void build(){
	queue<node*> qq;
	//int p = 0, q = 0;
	qq.push(root);
	//que[q++] = root;
	while(!qq.empty()){
		node* t = qq.front();
		qq.pop();
		for(int i = 0; i < K; i ++){
			if(t->ch[i]){
				t->ch[i]->fail = t->fail->ch[i];
				qq.push(t->ch[i]);
			}
			else
				t->ch[i] = t->fail->ch[i];
		}
	}
}

void run(char* s){
	int ans = 0;
	node* t = root;
	for(; *s; s++){
		int x = *s - 33;
		t = t->ch[x];
		for(node* u = t; u->match != -1; u = u->fail){
			if(u->match != 0)
				net.insert(u->match);
			//ans += u->match;
			//u->match = -1;
		}
	}
	//return ans;
}

char s[10001];

int main()
{
	int m, n;
	clear();
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%s", s);
		insert(s, i);
	}
	build();
	scanf("%d", &m);
	int total = 0;
	for(int i = 1; i <= m; i ++){
		scanf("%s", s);
		net.clear();
		run(s);
		if(net.size() > 0){
			printf("web %d:", i);
			for(it = net.begin(); it != net.end(); it ++){
				printf(" %d", *it);
			}
			puts("");
			total++;
		}
	}
	printf("total: %d\n", total);
	return 0;
}
