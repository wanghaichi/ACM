#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int N = 110;

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
}no[N];


int main()
{
	int n;
	while(~scanf("%d", &n) && n){
		for(int i = 0; i < n; i ++){
			scanf("%lf%lf", &no[i].x, &no[i].y);
		}
		//no[n] = no[0];这样就不用后面额外再加上最后一个点和第一个点的情况了
		point n0(0,0);
		double ans = 0;
		//任选一个点，按照逆时针或顺时针方向，与每两个点依次做叉积，所得结果除以2就是多边形的面积
		for(int i = 0; i < n-1; i ++){
			ans += (no[i]-n0)*(no[i+1]-n0);
		}
		//最后一个点和第一个点也要加上
		ans += (no[n-1]-n0)*(no[0]-n0);

		printf("%.1f\n", ans/2);
	}
	return 0;
}

