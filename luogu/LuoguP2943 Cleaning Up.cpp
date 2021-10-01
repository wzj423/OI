#include <bits/stdc++.h>
const int MAXN=80010;
using namespace std;
int N,M,a[MAXN];
/*
    1.易知答案的上限是N 每次都清理
	2.答案随N单调不减
    ->所以对于一段长度为x的区间,其颜色数量一定不超过sqrt(x) 否则一定更劣
    因而,我们只需找到最长的区间满足区间中颜色数量为j的进行转移,
    也就是对于选择的区间按照颜色数量分类,有sqrt(N)类,每种分类仅考虑一个转移,(因为2.)
    转移复杂度O(Nsqrt(N))
    现在考虑如何求出所需的区间,不妨令pos[j]为当前位置向前回溯满足颜色数量为j中的最大区间的左端点坐标
    转移时分别考虑每一个pos[j],那么因为每一个pos[j]都单调不降,所以对于每一个pos[j],均摊O(N),有sqrt(N)种,
    预处理O(Nsqrt(N))
    由于一开始只有一种颜色,所以不妨反向贪心,使得pos[j]的颜色<=j就可以了.
    因而总复杂度O(Nsqrt(N))
*/
int nxt[MAXN],pre[MAXN],but[MAXN];
int pos[MAXN],cnt[MAXN];
int f[MAXN],_UP;
int main() {
	scanf("%d%d",&N,&M);_UP=sqrt(N);
	for(int i=1;i<=N;++i) {
		scanf("%d",a+i);
        nxt[but[a[i]]]=i;
        pre[i]=but[a[i]];
        nxt[i]=80005;
        but[a[i]]=i;
	}
	memset(pos,-1,sizeof pos);memset(f,0x3f,sizeof f);
    for(int i=1;i<=_UP;++i) pos[i]=cnt[i]=1;
    f[1]=1;f[0]=0;
    for(int i=2;i<=N;++i) {
        for(int j=1;j<=_UP;++j) {
            if(pre[i]<pos[j]) ++cnt[j];
            if(cnt[j]>j) {
				--cnt[j];
                while(nxt[pos[j]]<=i) ++pos[j];
				++pos[j];
            }
        }
		for(int j=1;j<=_UP;++j) {
			if(pos[j]!=-1)
				f[i]=min(f[i],f[pos[j]-1]+j*j);
		}
    }
    printf("%d\n",f[N]);
	return 0;
}
