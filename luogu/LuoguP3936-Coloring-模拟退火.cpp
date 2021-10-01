#include <bits/stdc++.h>
#define db double
using namespace std;
int __tm,__nw;
//defs============================
int N,M,C;
int p[1010],b[1010];
int a[22][22],res[22][22];
const int _x[]={0,0,-1,1};
const int _y[]={-1,1,0,0};
//simulated annealing=========================
int ans=1e9;
db T;
const db delta=0.99999;
int rnd() { return rand()*2-RAND_MAX; }
int update(int x) {
    if(x<ans) {
		ans=x;
		for(int i=1;i<=N;++i) for(int j=1;j<=M;++j) res[i][j]=a[i][j];
    }
}
int get_cell(int x,int y) {
	int ret=0;
	for(int i=0;i<4;++i) if(a[x][y]!=a[x+_x[i]][y+_y[i]]) ++ret;
	return ret;
}
int get_mat() {
	int ans=0;
	for(int i=1;i<=N;++i) for(int j=1;j<=M;++j) ans+=get_cell(i,j);//,printf("(%d,%d)=%d\n",i,j,get_cell(i,j));
	return ans;
}
void simu_anne() {
    int now=ans;
    srand(2002042388);srand(rand());srand(rand());
    T=3000000;
    while(T>1e-12) {
        int x1=rand()%N+1,y1=rand()%M+1,x2=rand()%N+1,y2=rand()%M+1;
        while(x1==x2&&y1==y2) x2=rand()%N+1,y2=rand()%M+1;
        int newans=now-get_cell(x1,y1)*2-get_cell(x2,y2)*2;
        swap(a[x1][y1],a[x2][y2]);
        newans+=(get_cell(x1,y1)+get_cell(x2,y2))*2;
        int DE=newans-now;
        if(DE<0) {
			now=newans;
        } else if(exp(-DE/T)*RAND_MAX>rand()) {
            now=newans;
        } else {
			swap(a[x1][y1],a[x2][y2]);
        }
        update(now);
        T*=delta;
    }
}
void SA() {
	while(true) {
		__nw=clock();
		simu_anne();
		if(1.0*(__nw-__tm)/CLOCKS_PER_SEC>2.0) break;
	}
}
//main=================================
void display() {
    for(int i=1;i<=N;++i)
		for(int j=1;j<=M;++j)
			printf("%d%c",a[i][j],j==M?'\n':' ');
}
int main() {
	__tm=clock();
	scanf("%d%d%d",&N,&M,&C);
	for(int i=1;i<=C;++i) scanf("%d",p+i);
	int t=0;
    for(int i=1;i<=N;++i) for(int j=1;j<=M;++j) {
		if(b[t]==p[t]) ++t;
        a[i][j]=t; ++b[t];
        //printf("%d ",a[i][j]);
    }
   // display();
    ans=get_mat();
    //printf("%d\n",ans);
    SA();
    display();
	//printf("%d\n",(ans-2*N-2*M)/2);
	//printf("%d\n",get_mat()/2-N-M);
	return 0;
}
