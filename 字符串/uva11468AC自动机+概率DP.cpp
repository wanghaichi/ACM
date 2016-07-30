/*******************uva11468************

AC自动机加上状态DP，每个结点都有状态数组d。


*****************************************/


#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int K = 62;
const int maxn = 410;

double px[62];

int idx(char ch){
	if(ch >= 'a' &&  ch <= 'z')
		return ch - 'a';
	else if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 26;
	else
		return ch - '0' + 52;
}

struct node{
	node* ch[K], *fail;
	double d[105];
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
		int x = idx(*s);
		if(t->ch[x] == NULL)
			t->ch[x] = newNode();
		t = t->ch[x];
	}
	t->match = 1;
}

void build(){
	int q = 0, p = 0;
	que[q++] = root;
	while(q != p){
		node* t = que[p++];
		for(int i = 0; i < K; i ++){
			if(t->ch[i]){
				t->ch[i]->fail = t->fail->ch[i];
				if(t->fail->ch[i]->match == 1)
					t->ch[i]->match = 1;
				que[q++] = t->ch[i];
			}
			else{
				t->ch[i] = t->fail->ch[i];
				if(t->fail->ch[i]->match == 1)
					t->ch[i]->match = 1;
			}
		}
	}
}
//从根节点出发，根据条件进行状态转移。
//不能用队列来完成，之前想的是用两个队列，储存当前能够到达的结点和dp值
//但是到后来结点回很多。
double bfs(int L){
	root->d[0] = 1;
	for(int i = 1; i <= L; i ++){
		for(node* t = root; t != cur; t ++){
			for(int j = 0; j < K; j ++){
				if(t->ch[j]->match == 0 && px[j] > 0){
					t->ch[j]->d[i] += t->d[i-1] * px[j];
				}
			}
		}
	}
	double res = 0;
	for(node* t = root; t != cur; t ++){
		res += t->d[L];
	}
	return res;
}

char s1[25], s2[2];

int main()
{
	int ct = 1, n, T, k, L;
	double tp;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &k);
		clear();
		memset(px, 0, sizeof(px));
		for(int i = 0; i < k; i ++){
			scanf("%s", s1);
			insert(s1);
		}
		build();
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%s %lf", s2, &tp);
			px[idx(s2[0])] = tp;
		}
		scanf("%d", &L);
		double res = bfs(L);
		printf("Case #%d: %f\n",ct++,  res);
	}
	return 0;
}
