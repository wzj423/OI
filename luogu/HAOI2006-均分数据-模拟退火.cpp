#include <bits/stdc++.h>
#define db double
using namespace std;
int N,M;
int a[25];
//dp=================================
db f[25][25];
/*
	f[i][j] 表示1-i的数字分成j组最小的(sum-aver)^2之和
	因为aver已知,所以可以dp
	f[i][j]=f[k][j-1]+(sum(k+1,i)-aver)^2
*/
db aver,pre[25];
db calc_ans() {
    for(int i=0;i<=N;++i) for(int j=0;j<=M;++j) f[i][j]=1e15;
    for(int i=1;i<=N;++i) pre[i]=a[i]+pre[i-1];
    f[0][0]=0;
    for(int i=1;i<=N;++i) {
		for(int j=1;j<=M;++j) {
			for(int k=0;k<i;++k)
				f[i][j]=min(f[i][j],f[k][j-1]+(pre[i]-pre[k]-aver)*(pre[i]-pre[k]-aver));
		}
    }
    return f[N][M];
}
//simulated anneal====================
int rnd() {
    return rand()*2-RAND_MAX;
}
const db delta=0.991;
db ans=1e17,t;
int seq[25];
void simu_anne() {
	srand(rand());
	t=3000;
	db now=ans;
    while(t>1e-14) {
        int x=rand()%(N)+1,y=rand()%(N)+1;
        while(x==y) y=rand()%(N)+1;
        //cerr<<x<<" "<<y<<endl;
        swap(a[x],a[y]);
        db nowans=calc_ans(),DE=nowans-now;
        if(DE<0) {
            ans=now=nowans;
        } else if(exp(-DE/t)*RAND_MAX>rand()) {
			now=nowans;
        } else {
			swap(a[x],a[y]);
        }
        t*=delta;
    }
}
void SA() {
	for(int i=1;i<=10;++i)
		simu_anne();
	ans=sqrt(ans/M);
    printf("%.2lf\n",ans);
}
//main================================
int main() {
	srand(19260817);
	for(int i=1;i<=10;++i) srand(rand());
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i) scanf("%d",a+i),aver+=a[i];
	aver/=M;
	SA();
	return 0;
}
