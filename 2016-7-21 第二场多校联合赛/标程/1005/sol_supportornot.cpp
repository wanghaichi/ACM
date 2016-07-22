#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<string>
#include<vector>
#include<set>
#include<queue>
#include<time.h>
#include<assert.h>
#include<iostream>
#include<map>
using namespace std;
const int M=1e9+7;
typedef long long LL;
typedef pair<int,int>pi;
const int Maxn=100020;
map<pi,int>::iterator it1,it2;
int pw[Maxn];
map<pi,int>Mp;
int n;
struct Node{
	int x,y,tl;
	Node(){}
	Node(int x,int y,int tl):x(x),y(y),tl(tl){}
	bool operator <(const Node &a)const{
		return x==a.x?y<a.y:x<a.x;
	}
};
int main(){
	pw[0]=1;
	for(int i=1;i<Maxn;i++)pw[i]=(pw[i-1]+pw[i-1])%M;
	int _;scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		Mp.clear();
		for(int i=0;i<n;i++){
			int x,y;scanf("%d%d",&x,&y);
			Mp[pi(x,y)]++;
		}
		int ans=0;
		for(it1=Mp.begin();it1!=Mp.end();it1++){
			pi u=it1->first;
			//printf("x=%d y=%d it1->second=%d\n",u.first,u.second,it1->second);
			vector<Node>V;
			for(it2=it1,it2++;it2!=Mp.end();it2++){
				pi v=it2->first;
				int dx=v.first-u.first;
				int dy=v.second-u.second;
				if(dx<0){dx=-dx;dy=-dy;}
				if(dx==0||dy==0){
					if(dx==0)dy=1;
					else dx=1;
					V.push_back(Node(dx,dy,it2->second));
				}
				else{
					int gc=__gcd(abs(dx),abs(dy));
					dx/=gc,dy/=gc;
					V.push_back(Node(dx,dy,it2->second));
				}
			}
			int cnt=it1->second;
			sort(V.begin(),V.end());
			for(int i=0,j;i<V.size();i=j){
				int tot=V[i].tl;
				for(j=i+1;j<V.size();j++){
					if(V[j].x!=V[i].x||V[j].y!=V[i].y)break;
					tot+=V[j].tl;
				}
				//printf("tot=%d\n",tot);
				ans+=1LL*(pw[cnt]-1)*(pw[tot]-1)%M;
				ans%=M;
			}
			if(cnt>=2){
				ans+=((pw[cnt]-1-cnt)%M+M)%M;
				ans%=M;
			}
			//printf("ans=%lld\n",ans);
		}
		ans=(ans+M)%M;
		printf("%d\n",ans);
	}
	return 0;
}
