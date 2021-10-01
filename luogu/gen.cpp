#include <bits/stdc++.h>
#define ll long long
using namespace std;
//defs==================
//tool======================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
int N=10,K=4;
//main==================
int main() {
	srand((ll)(new char));
	freopen("gen.in","w",stdout);
    printf("%d %d\n",N,K);
    for(int i=1;i<=N;++i) printf("%d ",rand());
	return 0;
}

