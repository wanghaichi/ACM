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

struct line{
	point s, t;
};

//判断两个直线是否相交，只需要没个线段两个端点分别位于另一条线段的两侧。
//对于AB CD 两条线段，若AB向量与AC向量叉乘大于零，则说明C点位于AB直线的逆时针方向，若等于零说明C点在AB之线上，若小于零说明C点在AB直线的顺时针方向，通过这个特点来判断两点是否位于一条直线的同一侧。
bool intersect(point x1, point y1, point x2, point y2){ 
	double d1, d2, d3, d4;
	//d1,d2表示x1，y1是否位于x2->y2这条向量的两侧
	d1 = (y2-x2)*(x1-x2); 
	d2 = (y2-x2)*(y1-x2);
	//d3,d4同理
	d3 = (y1-x1)*(x2-x1);
	d4 = (y1-x1)*(y2-x1);
	if(d1*d2<0 && d3*d4<0)
		return true;
	return false;
}

int main()
{
	int w, h, l;
	while(~scanf("%d%d", &w, &h) && (w != 0 || h != 0)){
		scanf("%d", &l);
		for(int i = 0; i <= l; i ++){
			scanf("%lf%lf", &no[i].x, &no[i].y);
		}
		int ans = l + 1;
		double x0 = no[0].x, y0 = no[0].y;
		for(int i = 0; i < l; i ++){
			for(int j = i + 2; j < l; j ++){
				if(intersect(no[i], no[i+1], no[j], no[j+1])){
					ans ++;
				}
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}

