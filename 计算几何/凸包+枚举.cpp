#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 15;
const double eps = 1e-9;
const double Pi = acos(-1.0);

struct point{
	double x, y, v, l;
	point(){}
	point(double _x, double _y):x(_x), y(_y){}
	point operator + (point t){
		return point(x+t.x, y+t.y);
	}
	point operator - (point t){
		return point(x-t.x, y-t.y);
	}
	point operator * (double a){
		return point(x*a, y*a);
	}
	point operator / (double a){
		return point(x/a, y/a);
	}
	double operator * (point t){ // 向量叉积，返回向量|a|*|b|*sin(θ)方向垂直u,v 且遵循右手定则
		return x*t.y - y*t.x;
	}
	double operator ^ (point t){ // 向量点积，返回值 |a|*|b|*cos(θ)
		return x*t.x + y*t.y;
	}
	double len(){
		return sqrt( x*x + y*y );
	}
}no[N+5], s[N+5], tu[N+5];

bool cmp(point p1, point p2){
	if (p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

void Convex(point *p, int& n){
	int i, j, r, top, m;
	sort(p, p+n, cmp);
	s[0] = p[0];
	s[1] = p[1];
	top = 1;
	for(i = 2; i < n; i ++){
		while(top>0 && (p[i]-s[top-1])*(s[top]-s[top-1]) >= 0)top--;
		s[++top] = p[i];
	}
	m = top;
	s[++top] = p[n-2];
	for(i = n-3; i >= 0; i --){
		while(top>m && (p[i]-s[top-1]) * (s[top]-s[top-1]) >= 0)top--;
		s[++top] = p[i];
	}
	n = top;
}

int count(int v){
	int res = 0;
	while(v > 0){
		if(v&1) res++;
		v >>= 1;
	}
	return res;
}

void solve(int v, int n, double& ans, int& state, double& exw){
	int cnt = 0;
	double cl = 0, cv = 0, clen = 0;
	for(int i = 0; i < n; i ++){
		if(v&(1<<i)){
			cl += no[i].l;
			cv += no[i].v;
		}
		else{
			tu[cnt++] = no[i];
		}
	}
	if(cnt == 0 || cnt == 1){
		if(fabs(ans-cv) < eps){
			if(count(state) > count(v)){
				state = v;
				exw = cl;
			}
		}else if (ans > cv){
			state = v;
			exw = cl;
			ans = cv;
		}
	}
	else if (cnt == 2){
		clen = (tu[0]-tu[1]).len();
		if(2*clen <= cl){
			if(fabs(ans-cv) < eps){
				if(count(state) > count(v)){
					state = v;
					exw = cl - 2*clen;
				}
			}else if (ans > cv){
				state = v;
				exw = cl - 2*clen;
				ans = cv;
			}
		}
	}
	else{
		Convex(tu, cnt);
		for(int i = 0; i < cnt; i ++){
			clen += (s[i]-s[i+1]).len();
		}
		if(cl >= clen){
			if(fabs(ans-cv) < eps){
				if(count(state) > count(v)){
					state = v;
					exw = cl - clen;
				}
			}else if (ans > cv){
				state = v;
				exw = cl - clen;
				ans = cv;
			}
		}
	}
	return;
}


int main()
{
	int n, ct = 1;
	while(~scanf("%d", &n) && n){
		for(int i = 0; i < n; i ++){
			scanf("%lf%lf%lf%lf", &no[i].x, &no[i].y, &no[i].v, &no[i].l);
		}
		double ans = 1510000, exw;
		int state;
		for(int i = 1; i < (1<<n)-1; i ++){
			solve(i, n, ans, state, exw);	
		}
		printf("Forest %d\nCut these trees:",ct++);
		for(int i = 0; i < n; i ++){
			if(state & (1<<i))
				printf(" %d", i+1);
		}
		printf("\nExtra wood: %.2lf\n\n", exw);
	}
	return 0;
}

