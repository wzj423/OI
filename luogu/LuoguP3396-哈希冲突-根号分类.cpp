#include <bits/stdc++.h>

using namespace std;
/*
当p很大时,可以直接暴力做
当p很小时,可以分类前缀和,修改时暴力修改每一类前缀和
复杂度O(N\sqrt N)
*/
//tool====================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
//defs====================
int N,M,UP;
int a[160000],x,y;
int b[800][800];
char _t[10];
//main====================
int main() {
    N=rd(),M=rd();UP=sqrt(N);
    for(int i=1;i<=N;++i) {
        a[i]=rd();
        for(int j=1;j<=UP;++j)
            b[j][i%j]+=a[i];
    }
	for(int i=1;i<=M;++i) {
        scanf("%s",_t);
        x=rd(),y=rd();
        if(_t[0]=='A') {
            if(x>UP) {
				int ret=0;
				for(int j=y;j<=N;j+=x) ret+=a[j];
				printf("%d\n",ret);
            } else {
				printf("%d\n",b[x][y]);
            }
        } else {
            for(int j=1;j<=UP;++j)
				b[j][x%j]=b[j][x%j]-a[x]+y;
            a[x]=y;
        }

	}
	return 0;
}
