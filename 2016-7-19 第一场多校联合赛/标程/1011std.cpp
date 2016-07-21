/*************************************************************************
    > File Name: ZNL.cpp
    > Author: znl1087
    > Mail: loveCJNforever@gmail.com
    > Created Time: 三  7/29 11:14:13 2015
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
using namespace std;
const double EPS = 1e-6;
struct Point3{
	double x,y,z;
	Point3(){}
	Point3(double x,double y,double z):x(x),y(y),z(z){}
};

typedef Point3 Vec3;

Vec3 operator + (Vec3 A,Vec3 B){return Vec3(A.x + B.x,A.y + B.y,A.z + B.z);}
Vec3 operator - (Point3 A,Point3 B){return Vec3(A.x-B.x,A.y-B.y,A.z-B.z);}
Vec3 operator * (Vec3 A,double p){return Vec3(A.x * p,A.y * p,A.z * p);}
Vec3 operator / (Vec3 A,double p){return Vec3(A.x / p,A.y / p,A.z / p);}

int dcmp(double x){
	return fabs(x) < EPS ? 0 : (x <0 ? -1:1);
}

double Dot3(Vec3 A, Vec3 B){ return A.x * B.x + A.y * B.y + A.z * B.z;}
double Length3(Vec3 A){ return sqrt(Dot3(A,A));}
double Angle(Vec3 A,Vec3 B){ return acos(Dot3(A,B) / Length3(A) / Length3(B));}
Vec3 Cross3(Vec3 A,Vec3 B){
	return Vec3(A.y * B.z - A.z * B.y,
				A.z * B.x - A.x * B.z,
				A.x * B.y - A.y * B.x);
}
struct Plane{
	Vec3 n;
	Point3 p0;
	Plane(){}
	Plane(Vec3 nn,Point3 pp0){
		n = nn/Length3(nn);
		p0 = pp0;
	}
	Plane(Point3 a,Point3 b,Point3 c){
		Point3 nn = Cross3(b-a,c-a);
		n = nn/Length3(nn);
		p0 = a;
	}
};
Plane jpfPlane(Point3 a1,Point3 a2,Point3 b,Point3 c){
	Plane p1 = Plane(a1, b, c),p2 = Plane(a2,c,b);
	Vec3 temp = p1.n + p2.n;
	return Plane(Cross3(temp, c-b),b);
}
Point3 LinePlaneIntersection(Point3 p1,Point3 p2,Plane a){
	Point3 p0 = a.p0;
	Vec3 n = a.n,v = p2-p1;
	double t = (Dot3(n,p0-p1) / Dot3(n,p2-p1));
	return p1 + v * t;
}
Point3 PlaneInsertion(Plane a,Plane b,Plane c){
	Vec3 nn = Cross3(a.n,b.n),use = Cross3(nn,a.n);
	Point3 st = LinePlaneIntersection(a.p0, a.p0+use,b);
	return LinePlaneIntersection(st, st+nn, c);
}
double DistanceToPlane(Point3 p,Plane a){
	Point3 p0 = a.p0;
	Vec3 n = a.n;
	return fabs(Dot3(p-p0,n)) / Length3(n);
}
bool isOnPlane(Point3 a,Point3 b,Point3 c,Point3 d){
	double t = Dot3(d-a,Cross3(b-a, c-a));
	return dcmp(t)==0;
}

int main(){
    //freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);
	int x,y,z;
	Point3 p[4];
	while(scanf("%d%d%d",&x,&y,&z)==3){
		p[0] = Point3((double)x,(double)y,(double)z);
		for(int i=1;i<4;i++){
			scanf("%d%d%d",&x,&y,&z);
			p[i] = Point3((double)x,(double)y,(double)z);
		}
		if(isOnPlane(p[0],p[1],p[2],p[3])){
			puts("O O O O");
		}else{
			Plane a = jpfPlane(p[0],p[1],p[2],p[3]),
				b = jpfPlane(p[1],p[2],p[3],p[0]),
				c = jpfPlane(p[2],p[3],p[0],p[1]);
			Point3 center = PlaneInsertion(a, b, c);
			double r = DistanceToPlane(center, Plane(p[0],p[1],p[2]));
			printf("%.3f %.3f %.3f %.3f\n",center.x,center.y,center.z,r);
		}
	}
	return 0;
}
