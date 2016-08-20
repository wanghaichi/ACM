/*************************************************************

FILENAME:                   uva11178.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-19 13:46:28

LAST MODIFIED:         2016-08-20 10:38:33

ID: uva11178.cpp 

TYPE: 计算几何

DETAIL: 给出一个三角形，求其三个角的三等分线的交点

TATICS: 旋转求交即可

************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a))

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7;
const double eps = 1e-9;

struct Point{
	double x, y;
	Point(double _x = 0, double _y = 0):x(_x), y(_y){}
};

//向量与点等价，表示从原点到这个点的向量
typedef Point Vector;

Vector operator + (Vector A, Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator - (Vector A, Vector B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator * (Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator / (Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator < (const Vector& A, const Vector& B){
	return A.x < B.x || (A.x == B.x && A.y < B.y);
}
//判断浮点数的正负
int dcmp(double x){
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
bool operator == (const Vector& A, const Vector& B){
	return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0;
}
/* 求极角
	向量(x, y) 的级角为 atan2(y, x);
*/
//点积
double Dot(Vector A, Vector B){return A.x*B.x + A.y*B.y;}
//利用点积求长度
double Length(Vector A){return sqrt(Dot(A, A));}
//求两个向量的角度
double Angle(Vector A, Vector B){
	return acos(Dot(A, B)/ Length(A)/Length(B));
}
//叉积
double Cross(Vector A, Vector B){return A.x*B.y - A.y*B.x;}
double Area(Point A, Point B, Point C){return Cross((B-A), C-A)/2;}
//将向量旋转一定的角度
Vector Rotate(Vector A, double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad) ,A.x*sin(rad) + A.y*cos(rad));
}
//求一个向量的法线，即旋转90°再单位化
Vector Normal(Vector A){
	double L = Length(A);
	return Vector(-A.y/L, A.x/L);
}

//直线可以表示成一个起点P和方向向量v l: P+tv t为参数
//若已知直线上的两个点，则参数方程为A+(B-A)t
//对于上面的参数方程，线段 0 < t < 1 射线 t > 0
//求直线交点
//调用前确保两条之前有且只有一个交点，当且仅当Cross(v, w) != 0;
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
//点到直线距离，利用叉积
double DistanceToLine(Point P, Point A, Point B){
	Vector v1 = B - A, v2 = P - A;
	return fabs(Cross(v1, v2)) / Length(v1); 
}
//点到线段距离，需要考虑点到线段的垂线是否在线段上
double DistanceToSegment(Point P, Point A, Point B){
	if(A == B) return Length(P-A);
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
	else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
	else return fabs(Cross(v1, v2)) / Length(v1);
}
//求点在直线上的投影
Point GetLineProjection(Point P, Point A, Point B){
	Vector v = B - A;
	return A + v*(Dot(v, P-A) / Dot(v, v));
}

//判断点是否在线段上（可以在端点）
bool onSegment(Point p, Point a1, Point a2){
	return dcmp(Cross(a1-p, a2-p) == 0) && dcmp(Dot(a1-p, a2-p)) <= 0;
}
//判断两条线段是否相交
bool IsLineIntersection(Point a1, Point a2, Point b1, Point b2){
	double c1 = Cross(a2-a1, b1-a1);
	double c2 = Cross(a2-a1, b2-a1);
	double c3 = Cross(b2-b1, a1-b1);
	double c4 = Cross(b2-b1, a2-b1);
	return dcmp(c1)*dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
}
//多边形求面积，适用于凸多边形和凹多边形
double ConvexPolygonArea(Point *p, int n){
	double res = 0;
	for(int i = 1; i < n - 1; i ++)
		res += Cross(p[i] - p[0], p[i+1] - p[0]);
	return res / 2;
}

Point solve(Point A, Point B, Point C){
	double b = Angle(A-B, C-B);
	Vector v = Rotate(C-B, b/3);
	double c = Angle(B-C, A-C);
	Vector w = Rotate(B-C, -c/3);
	Point D = GetLineIntersection(B, v, C, w);
	return D;
}

int main()
{
	Point A, B, C, D, E, F;
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
		D = solve(A, B, C);
		E = solve(B, C, A);
		F = solve(C, A, B);
		printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", D.x, D.y, E.x, E.y, F.x, F.y);
	}


	return 0;
}

