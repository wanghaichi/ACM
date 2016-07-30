/**********AC自动机模板*******************

AC自动机实在Trie树的基础上，进行状态转移的过程。
每个节点都会有失陪指针（fail）表示当前结点匹配失败时应当转移的地方。
每个fail指针相当于Trie数上的边，而每条边相当于状态转移的过程。与动态规划有些相似。

*****************************************/



const int K = 26; //字符种类

const int maxn = 500100; //所有字符串的字符长度综合

//Trie树结点结构
struct node{
	//fail表示适配指针
	node* ch[K], *fail;
	//当前匹配数
	int match;
	//初始化
	void clear(){
		memset(this, 0, sizeof(node));
	}
};
//bfs构造适配指针时是用的队列
node* que[maxn];
//nodes储存Trie树，root表示根节点，superRoot是虚拟根节点，是根节点的父亲节点，可以节省许多代码量，cur表示最后一个节点的位置
node nodes[maxn], *root, *superRoot, *cur;
//创建新的节点
node* newNode(){
	cur->clear();
	return cur++;
}
//初始化操作，可以发现根节点的失陪指针指向超级根节点，并且超级根节点的所有子节点都指向根节点
void clear(){
	cur = nodes;
	superRoot = newNode();
	root = newNode();
	root->fail = superRoot;
	for(int i = 0; i < K; i ++)
		superRoot->ch[i] = root;
	//-1表示没有匹配
	superRoot->match = -1;
}
//构建Trie树，插入单词
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

//在构造好Trie树之后，构造适配指针的过程，通过bfs实现
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
//根据目标串s求出Trie树中有多少个模式串在s中出现
int run(char *s){
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

int main()
{
	
	return 0;
}
