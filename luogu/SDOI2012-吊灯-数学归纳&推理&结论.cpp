#include <bits/stdc++.h>

using namespace std;
//thoughts==================
/*
考虑一颗被完全合法染色的树
根据反证法可以得出:一定有一个同色联通块,它的每一个节点都不是其他异色节点的父节点,其大小为floor(sz[tot]/K)
我们把这种不同颜色染色块之间的"父子"关系抽象成一条有向边
那么以颜色为节点,这一定是一个有向无环图
所以类似拓扑排序那样删边之后,上述结论一定成立
那么之前题解提到的,
满足条件时颜色的节点数为k，当且仅当有 n/k 个节点满足它的子树是k的倍数(显然还有 k|n )的结论就很显然了.
*/
//tool======================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
//main======================
const int MAXN=2e6;
typedef int arr[MAXN];
arr fa,num,sz;
int N,T;
int main() {
	N=rd();
	for(T=1;T<=10;++T) {
		for(int i=2;i<=N;++i)
			if(T==1) fa[i]=rd();
			else fa[i]=(fa[i]+19940105)%(i-1)+1;
		//for(int i=2;i<=N;++i) printf("fa[%d]=%d\n",i,fa[i]);
        for(int i=1;i<=N;++i) sz[i]=1,num[i]=0;
        for(int i=N;i>1;--i) sz[fa[i]]+=sz[i];
        for(int i=1;i<=N;++i) ++num[sz[i]];
        printf("Case #%d:\n1\n",T);
		for(int i=2;i<=N;++i) if(N%i==0) {
			int t=0;
			for(int j=1;i*j<=N;++j) {
                t+=num[i*j];
			}
			if(t*i>=N) printf("%d\n",i);
		}
	}
	return 0;
}
