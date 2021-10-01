#include <bits/stdc++.h>
#define check(x) (((x)&hate)||(~(x)&love))
#define maxx(x,y) ((x)>(y)?(x):(y))
using namespace std;

//defs&tools============
inline int rd() {
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
const int MAXN=50010,bits=(1<<5);
int N,C;
int num[MAXN][bits+10];
int f[MAXN][bits+10];
int ans=0;
//main==================
int main() {
	N=rd(),C=rd();
    for(int i=1;i<=C;++i) {
        int e=rd(),b=rd(),c=rd();
        int love=0,hate=0;
        for(int j=1;j<=b;++j) {
            int t=rd();t=(t-e+N)%N;love|=1<<t;
        }
		for(int j=1;j<=c;++j) {
            int t=rd();t=(t-e+N)%N;hate|=1<<t;
        }
        for(int j=0;j<bits;++j) {
            num[e][j]+=check(j);
        }
    }
    //自小到大越来越新
    for(int state=0;state<bits;++state) {
        memset(f,0xc0,sizeof f);
        f[0][state]=0;
        for(int i=1;i<=N;++i) {
			for(int j=0;j<bits;++j) {
                f[i][j]=maxx(f[i-1][(j&15)<<1],f[i-1][(j&15)<<1|1])+num[i][j];
			}
        }
        ans=maxx(ans,f[N][state]);
    }
    printf("%d\n",ans);
	return 0;
}
