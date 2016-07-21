#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <new>
using std::string;
using std::cin;
using std::cout;
const int N=110000;
struct Metro{
    std::map<string,int> mp;
    std::vector<string> vec;
    int alloc(const string &name){
        std::pair<std::map<string,int>::iterator,bool> got=mp.insert(std::make_pair(name,mp.size()));
        if(got.second){
            vec.push_back(name);
        }
        return got.first->second;
    }
};
struct item{
    int tgt;
    item *next;
    item(){}
    item(int tgt,item *next):tgt(tgt),next(next){}
}*ls[N],*lt[N],storage[4*N];
void insert(item **list,int a,int b,item *&loc){
    list[a]=new(loc++) item(b,list[a]);
    list[b]=new(loc++) item(a,list[b]);
}
int farSel[N];
std::pair<int,int> findFarthest(item **list,int a,int prev){
    std::pair<int,int> r(a,-1);
    for(item *p=list[a];p;p=p->next){
        if(p->tgt!=prev){
            std::pair<int,int> cur=findFarthest(list,p->tgt,a);
            if(cur.second>r.second){
                farSel[a]=p->tgt;
                r=cur;
            }
        }
    }
    r.second++;
    return r;
}
std::pair<int,int> findRoot(item **list){
    int a=findFarthest(list,0,-1).first;
    std::pair<int,int> t=findFarthest(list,a,-1);
    for(int i=0;i<t.second/2;i++){
        a=farSel[a];
    }
    return std::make_pair(a,t.second%2?farSel[a]:-1);
}
const int M=1000000007,MM=100000007;
struct HashPair{
    int a,h;
    HashPair(){}
    HashPair(int a,int h):a(a),h(h){}
    bool operator<(const HashPair &x)const{
        return h<x.h;
    }
};
std::vector<HashPair> hs[N],ht[N];
int hash(item **list,int a,int prev,std::vector<HashPair> *tgt){
    std::vector<HashPair> vec;
    for(item *p=list[a];p;p=p->next){
        if(p->tgt!=prev){
            vec.push_back(HashPair(p->tgt,hash(list,p->tgt,a,tgt)));
        }
    }
    std::sort(vec.begin(),vec.end());
    int r=1;
    for(int i=0;i<(int)vec.size();i++){
        r=((long long)r*MM+vec[i].h)%M;
    }
    tgt[a].swap(vec);
    return r;
}
bool match(std::vector<HashPair> &vs,std::vector<HashPair> &vt,int *res){
    if(vs.size()!=vt.size()){
        return false;
    }
    for(int i=0;i<(int)vs.size();i++){
        for(int j=i;j<(int)vt.size()&&vt[j].h==vs[i].h;j++){
            std::swap(vt[i].a,vt[j].a);
            if(match(hs[vs[i].a],ht[vt[i].a],res)){
                goto lblMatch;
            }
        }
        return false;
lblMatch:
        res[vs[i].a]=vt[i].a;
    }
    return true;
}
int mapping[N];
int main(){
    int size = 8 << 20;
    char *p = (char*)malloc(size) + size;
    //__asm__("movl %0, %%esp\n" :: "r"(p));
    //std::ifstream fin("in.txt");
    //std::ofstream fout("out.txt");
    int n;
    while(cin>>n){
        memset(ls,0,sizeof(ls));
        item *loc=storage;
        Metro src;
        for(int i=0;i<n-1;i++){
            string name;
            cin>>name;
            int a=src.alloc(name);
            cin>>name;
            int b=src.alloc(name);
            insert(ls,a,b,loc);
        }
        memset(lt,0,sizeof(lt));
        Metro tgt;
        for(int i=0;i<n-1;i++){
            string name;
            cin>>name;
            int a=tgt.alloc(name);
            cin>>name;
            int b=tgt.alloc(name);
            insert(lt,a,b,loc);
        }
        std::pair<int,int> rs=findRoot(ls),rt=findRoot(lt);
        std::vector<HashPair> vs,vt;
        vs.push_back(HashPair(rs.first,hash(ls,rs.first,rs.second,hs)));
        if(rs.second!=-1){
            vs.push_back(HashPair(rs.second,hash(ls,rs.second,rs.first,hs)));
        }
        std::sort(vs.begin(),vs.end());
        vt.push_back(HashPair(rt.first,hash(lt,rt.first,rt.second,ht)));
        if(rs.second!=-1){
            vt.push_back(HashPair(rt.second,hash(lt,rt.second,rt.first,ht)));
        }
        std::sort(vt.begin(),vt.end());
        if(match(vs,vt,mapping)){
            for(int i=0;i<n;i++){
                cout<<src.vec[i]<<' '<<tgt.vec[mapping[i]]<<'\n';
            }
        }else{
            cout<<"TAT\n";
        }
    }
    return 0;
}
