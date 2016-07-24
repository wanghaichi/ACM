#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int N = 30;
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
};

struct circle{
	//圆心
	point o;
	//半径
	double r;
	circle(){}
	circle(point _o, double _r):o(_o), r(_r){}
	double area(){
		return Pi*r*r;
	}
	//求两个圆相交面积
	double interarea(circle t){
		double d = (t.o-o).len();
		//相离的情况
		if(d > r + t.r + eps )
			return 0;
		//内含的情况
		if(t.r+d < r - eps)
			return t.area();
		if(r+d < t.r - eps)
			return area();
		double xita = acos((r*r+d*d-t.r*t.r)/(2*r*d));
		double arf = acos((t.r*t.r+d*d-r*r)/(2*t.r*d));
		//a圆对应扇形的面积	
		double S1 = xita*r*r;
		//b圆对应扇形的面积
		double S2 = arf*t.r*t.r;
		//两圆圆心和交点构成的四边行的面积
		double S3 = d*r*sin(xita);
		//相交面积
		return S1+S2-S3;
	}
}cr[N];

int main()
{
	int T, n;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%lf%lf%lf", &cr[i].o.x, &cr[i].o.y, &cr[i].r);
		}
		double ans = 30000;
		for(int i = 0; i < n; i ++){
			double l = 0, r = 30000, mid;
			circle cur(cr[i].o, r);
			bool flag;
			while(fabs(l - r) > eps){
				flag = false;
				cur.r = (l+r)/2;
				//cout << cur.r << endl;
				for(int j = 0; j < n; j ++){
					if(cur.interarea(cr[j])*2 >= cr[j].area())
						continue;
					else{
						flag = true;
						break;
					}
				}
				if(flag)
					l = cur.r;
				else
					r = cur.r;
			}
			ans = min(cur.r, ans);
		}
		printf("%.4f\n", ans);
	}
	return 0;
}

