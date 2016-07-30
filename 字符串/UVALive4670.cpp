#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int K = 26;
const int maxn = 75*155;

int vis[155], mans;

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

void insert(char* s, int i){
	node* t = root;
	for(; *s; s++){
		int x = *s - 'a';
		if(t->ch[x] == NULL)
			t->ch[x] = newNode();
		t = t->ch[x];	
	}
	t->match = i;
}

void build(){
	int q = 0, p = 0;
	que[q++] = root;
	while(q != p){
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

void run(char* s){
	int ans = 0;
	node* t = root;
	for(; *s; s++){
		int x = *s - 'a';
		t = t->ch[x];
		for(node* u = t; u->match != -1; u = u->fail){
			if(u->match > 0){
				vis[u->match] ++;
				mans = max(mans, vis[u->match]);
			}
		}
	}
}

char s1[155][75], s[1000010];

int main()
{
	int n;
	while(~scanf("%d", &n) && n){
		clear();
		memset(vis, 0 ,sizeof(vis));
		for(int i = 1; i <= n; i ++){
			scanf("%s", s1[i]);
			insert(s1[i], i);
		}
		build();
		scanf("%s", s);
		mans = 0;
		run(s);
		printf("%d\n", mans);
		for(int i = 1; i <= n; i ++){
			if(vis[i] == mans){
				printf("%s\n", s1[i]);
			}
		}
	}
	return 0;
}








