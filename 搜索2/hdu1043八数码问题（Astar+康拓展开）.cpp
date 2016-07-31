/************************************************************************
	hdu1043 经典八数码问题，使用A_star+康拓展开
*************************************************************************/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>

const int maxn = 400007;
const int mod = 1e9+7;
const int inf = 1e9;

using namespace std;
//结点信息，储存每一个位置的状态、估值函数、哈希值
struct node{
	//h表示当前状态每一个位置到其正确位置的哈曼吨距离
	//g表示从初始状态走到该状态需要的步数
	//hash为康拓展开后的哈希值
	int ma[3][3], h, g, x, y, hash;
	//这里按照先按h排序再按g排序，速度很快。也可以使用f = g + h 排序
	bool operator < (const node& n1) const {
		return h != n1.h ? h > n1.h : g > n1.g;
	}
	bool check(){
		if(x >= 0 && x < 3 && y >= 0 && y < 3)
			return true;
		return false;
	}
}st; //st表示初始位置结点

//康拓展开对应位置的康拓值，0! 1! 2! 3! ...
int hash[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int des = 322560, vis[maxn], pre[maxn];
int way[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//获取一个结点的哈希值
int getHash(node _u){
	int a [10], k = 0, res = 0;
	for(int i = 0; i < 3; i ++){
		for(int j = 0; j < 3; j ++){
			a[k++] = _u.ma[i][j];
		}
	}
	//对于每个结点找前面比他大的数，乘以当前位置的阶乘
	//也可以找每个结点见面比他小的数
	for(int i = 0; i < 9; i ++){
		k = 0;
		for(int j = 0; j < i; j ++){
			if(a[j] > a[i]) // a[j] < a[i] 找小的数
				k ++;
		}
		res += hash[i] * k;
	}
	return res;
}
//判断逆序数的奇偶性 考虑每次移动，如果是同一层的移动，逆序数不变，若是上下层之间移动，则逆序数变化要么+-2，要么不变，因此奇偶性一定不会发生改变。
bool isok(node _u){
	int a[9], k = 0, sum = 0;
	for(int i = 0; i < 3; i ++){
		for(int j = 0; j < 3; j ++){
			a[k++] = _u.ma[i][j];
		}
	}
	for(int i = 0; i < 9; i ++){
		for(int j = i + 1; j < 9; j ++){
			//注意这里不算0的奇偶性
			if(a[j] != 0 && a[i] != 0 && a[i] > a[j])
				sum ++;
		}
	}
	return !(sum&1);
}
//获取估值函数h的值，为每一个点到目标点的哈曼吨距离之和
int get_h(node _u){
	int ans = 0;
	for(int i = 0; i < 3; i ++){
		for(int j = 0; j < 3; j ++){
			if(_u.ma[i][j] != 0){
				ans += abs(i - (_u.ma[i][j] - 1)/3) + abs(j - (_u.ma[i][j] - 1)%3);
			}
		}
	}
	return ans;
}

void a_star(){
	priority_queue<node> q;
	q.push(st);
	node u, v;
	while(!q.empty()){
		u = q.top();
		q.pop();
		for(int i = 0; i < 4; i ++){
			v = u;
			v.x += way[i][0];
			v.y += way[i][1];
			if(v.check()){
				std::swap(v.ma[v.x][v.y], v.ma[u.x][u.y]);
				v.hash = getHash(v);
				if(vis[v.hash] == -1 && isok(v)){
					vis[v.hash] = i;
					v.g ++;
					pre[v.hash] = u.hash;
					v.h = get_h(v);
					q.push(v);
				}
				if(v.hash == des)
					return;
			}
		}
	}
}

void print(){
	string ans;
	ans.clear();
	int next = des;
	while(pre[next] != -1){
		if(vis[next] == 0)
			ans += "r";
		else if (vis[next] == 1)
			ans += "l";
		else if (vis[next] == 2)
			ans += "d";
		else if (vis[next] == 3)
			ans += "u";
		next = pre[next];
	}
	for(int i = ans.size()-1; i >= 0; i --){
		putchar(ans[i]);
	}
	puts("");
}


int main()
{
	char s[100];
	while(gets(s) != NULL){
		
		int k = 0;
		memset(vis, -1, sizeof(vis));
		memset(pre, -1, sizeof(pre));
		for(int i = 0; i < 3; i ++){
			for(int j = 0; j < 3; j ++){
				if(s[k] <= '9' && s[k] >= '0' || s[k] == 'x'){
					if(s[k] == 'x'){
						st.ma[i][j] = 0;
						st.x = i; st.y = j;
					}
					else
						st.ma[i][j] = s[k] - '0';
				}
				else{
					j --;
				}
				k ++;
			}
		}
		if(!isok(st)){
			puts("unsolvable");
			continue;
		}
		st.hash = getHash(st);
		if(st.hash == des){
			puts("");
			continue;
		}
		vis[st.hash] = -2;
		st.g = 0; st.h = get_h(st);
		a_star();
		print();
	}
	return 0;
}
