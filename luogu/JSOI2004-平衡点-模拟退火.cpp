#include <bits/stdc++.h>
#define db double
using namespace std;
struct node {
    int x,y,w;
}a[100005];
int N;
db xans,yans,ans=1e17,t;
const db delta=0.993;
//modules-================================
int rnd() {
	return 2*rand()-RAND_MAX;
}
db dis(db dx,db dy) {
	return sqrt(dx*dx+dy*dy);
}
db sn(db x,db y) {//势能
    db sum=0;
    for(int i=1;i<=N;++i) {
		sum+=dis(a[i].x-x,a[i].y-y)*a[i].w;
    }
    return sum;
}
void do_simuanne() {//模拟退火
	srand(rand());
    db xx=xans,yy=yans;
    t=300;//温度
    while(t>1e-14) {
        double xtemp=xans+rnd()*t;
        double ytemp=yans+rnd()*t;

        double new_ans=sn(xtemp,ytemp);
        double DE=new_ans-ans;
        if(DE<0) {
			xans=xx=xtemp,yans=yy=ytemp;
			ans=new_ans;
        } else if(exp(-DE/t)*RAND_MAX>rand()) {
			xx=xtemp,yy=ytemp;
        }
        t*=delta;
    }
}
void SA() {
    for(int i=1;i<=2;++i)
		do_simuanne();
}
int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;++i) {
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	}
	SA();
	printf("%.3lf %.3lf\n",xans,yans);
}
