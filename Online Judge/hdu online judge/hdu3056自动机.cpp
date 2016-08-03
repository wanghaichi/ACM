#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const int maxn = 1e5+7, K = 26;
const int mod = 1e9+7;
typedef long long ll;
int vis[1001];
struct node{
	node* ch[K], *fail;
	int match;
	void clear(){
		memset(this, 0, sizeof(node));
	}
};


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
		int x = *s - 'A';
		if(t->ch[x] == NULL)
			t->ch[x] = newNode();
		t = t->ch[x];
	}
	t->match = pos;
}


void build(){
	queue<node*> qq;
	qq.push(root);
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
		if(*s < 'A' || *s > 'Z'){
			t = root;
			continue;
		}
		int x = *s - 'A';
		t = t->ch[x];
		for(node* u = t; u->match != -1; u = u->fail){
			if(u->match != 0){
				vis[u->match]++;
			}
		}
	}
	//return ans;
}

char s[2000010], s1[1010][55];
int main()
{
	int n;
	while(~scanf("%d", &n)){
		clear();
		memset(vis, 0 ,sizeof(vis));
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
			scanf("%s", s1[i]);
			insert(s1[i], i);
		}
		build();
		scanf("%s", s);
		run(s);
		for(int i = 1; i <= n; i ++){
			if(!vis[i])
				continue;
			printf("%s: %d\n",s1[i], vis[i]);
		}
	}
	return 0;
}
