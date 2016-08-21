/*************************************************************

FILENAME:                   uva1342.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-20 10:50:08

LAST MODIFIED:         2016-08-21 10:20:52

ID: uva1342 

TYPE: 计算几何

DETAIL: 给出二维平面的封闭图形，求平面的数量。

TATICS: 使用欧拉定理，二维平面上，点+面-边=2

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
const int maxn = 310;
const double eps = 1e-9;

struct Point{
	double x, y;
	Point(double _x = 0, double _y = 0):x(_x), y(_y){}
};
typedef Point Vector;

Point operator + (Point A, Point B){return Vector(A.x+B.x, A.y+B.y);}
Point operator - (Point A, Point B){return Vector(A.x-B.x, A.y-B.y);}
Point operator * (Point A, double p){return Vector(A.x*p, A.y*p);}
Point operator / (Point A, double p){return Vector(A.x/p, A.y/p);}
int dcmp(double x){
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
bool operator < (Point A, Point B){
	return dcmp(A.x-B.x) < 0 || (dcmp(A.x - B.x) == 0 && dcmp(A.y < B.y));
}
bool operator == (Point A, Point B){
	return dcmp(A.x-B.x) == 0 && dcmp(A.y - B.y) == 0;
}
double Dot(Point A, Point B){return A.x*B.x + A.y*B.y;}
double Cross(Point A, Point B){return A.x*B.y - A.y*B.x;}


bool IsSegmaIntersection(Point a1, Point a2, Point b1, Point b2){
	double c1 = Cross(a2-a1, b1-a1);
	double c2 = Cross(a2-a1, b2-a1);
	double c3 = Cross(b2-b1, a1-b1);
	double c4 = Cross(b2-b1, a2-b1);
	return dcmp(c1*c2) < 0 && dcmp(c3*c4) < 0;
}

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}

bool OnSegma(Point C, Point A, Point B){
	return dcmp(Cross(C-A, C-B)) == 0 && dcmp(Dot(A-C, B-C)) < 0;
}
Point po[maxn], v[maxn*maxn];

int main()
{
	int n, ce, cv, cnt = 1;
	while(~scanf("%d", &n) && n){
		cv = 0;
		ce = n - 1;
		for(int i = 0; i < n - 1; i ++){
			scanf("%lf%lf", &po[i].x, &po[i].y);
			v[cv++] = po[i];
		}
		scanf("%lf%lf", &po[n-1].x, &po[n-1].y);
		for(int i = 0; i < n - 1; i ++){
			for(int j = i + 1; j < n - 1; j ++){
				if(IsSegmaIntersection(po[i], po[i+1], po[j], po[j+1])){
					v[cv++] = GetLineIntersection(po[i], po[i+1]-po[i], po[j], po[j+1]-po[j]);
				}
			}
		}
		//求出不同的点对的数量
		sort(v, v+cv);
		cv = unique(v, v + cv) - v;
		for(int i = 0; i < cv; i ++){
			for(int j = 0; j < n - 1; j ++){
				if(OnSegma(v[i], po[j], po[j+1]))
					ce ++;
			}
		}
		printf("Case %d: There are %d pieces.\n",cnt ++, ce+2-cv );
	}


	return 0;
}

