#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 50001;
const double eps = 1e-8;
const double Pi = acos(-1.0);

struct point{
	double x, y;
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
}no[N], s[N];

bool cmp(point p1, point p2){
	if (p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}
//凸包求法，按照x轴排序，则第一个点一定是凸包的顶点。枚举后面每一个点，若当前栈中只有一个点，则直接入栈，否则判断是否发生右旋，若发生右旋，将栈顶的元素弹出，直到发生左旋，讲当前点入栈，从前向后扫一边，从后向前扫一边就能求出凸包

void Convex(point *p, int& n){
	int i, j, r, top, m;
	sort(p, p+n, cmp);
	//先入队前两个点
	s[0] = p[0];
	s[1] = p[1];
	top = 1;
	for(i = 2; i < n; i ++){
		//这里判断是否发生左旋的时候>=0，若等于0说明当前点是凸包边上的一个顶点，可以不用考虑，如果要求凸包所有的顶点的话则改成>0
		while(top>0 && (p[i]-s[top-1])*(s[top]-s[top-1]) >= 0)top--;
		s[++top] = p[i];
	}
	m = top;
	//最后一个点当前一定位于栈顶
	s[++top] = p[n-2];
	for(i = n-3; i >= 0; i --){
		while(top>m && (p[i]-s[top-1]) * (s[top]-s[top-1]) >= 0)top--;
		s[++top] = p[i];
	}
	//当前的栈顶是第一个点，top就是凸包的顶点数
	n = top;
}

int main()
{
	int n;
	while(~scanf("%d", &n) && n){
		for(int i = 0; i < n; i ++){
			scanf("%lf%lf", &no[i].x, &no[i].y);
		}
		Convex(no, n);
		double ans = 0;
		for(int i = 0; i < n; i ++){
			for(int j = i + 1; j < n; j ++){
				for(int k = j + 1; k < n; k ++){
					ans = max( fabs((s[i]-s[j]) * (s[i]-s[k])) / 2, ans);
				}
			}
		}
		printf("%.2f\n", ans);
	}
	return 0;
}

