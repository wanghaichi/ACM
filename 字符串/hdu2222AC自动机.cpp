#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e6+7, K = 26;
const int mod = 1e9+7;
typedef long long ll;

struct node{
	node* ch[K], *fail;
	int match;
	void clear(){
		memset(this, 0, sizeof(node));
	}
};

node* que[maxn];

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

void insert(char* s){
	node* t = root;
	for(; *s; s++){
		int x = *s - 'a';
		if(t->ch[x] == NULL)
			t->ch[x] = newNode();
		t = t->ch[x];
	}
	t->match++;
	
}


void build(){
	int p = 0, q = 0;
	que[q++] = root;
	while(p != q){
		node* t = que[p++];
		for(int i = 0; i < K; i ++){
			if(t->ch[i]){
				t->ch[i]->fail = t->fail->ch[i];
				que[q++] = t->ch[i];
			}
			else
				t->ch[i] = t->fail->ch[i];
		}
	}
}

int run(char* s){
	int ans = 0;
	node* t = root;
	for(; *s; s++){
		int x = *s - 'a';
		t = t->ch[x];
		for(node* u = t; u->match != -1; u = u->fail){
			ans += u->match;
			u->match = -1;
		}
	}
	return ans;
}

char s[maxn];

int main()
{
	int T, n;
	scanf("%d", &T);
	while(T --){
		clear();
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%s", s);
			insert(s);
		}
		build();
		scanf("%s", s);
		int ans = run(s);
		printf("%d\n", ans);
	}
	return 0;
}
