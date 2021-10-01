#include <bits/stdc++.h>
const int MAXN=1e5+10;
using namespace std;
int N;
int ls[MAXN],rs[MAXN],vv[MAXN];
int s[MAXN],top;
struct dat{
    int val,id;
    bool operator <(const dat&d) const {
        return val<d.val;
    }
}a[MAXN];
void dfs(int st) {
	if(!st) return;
	printf("%d ",vv[st]);
    dfs(ls[st]);
    dfs(rs[st]);
}
int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d",&a[i].val),a[i].id=i;
    sort(a+1,a+N+1);
    for(int i=1;i<=N;++i) {
        while(top&&a[s[top]].id>a[i].id) top--;
		vv[i]=a[i].val;
        ls[i]=rs[s[top]];
        rs[s[top]]=i;
        s[++top]=i;
    }
 //   for(int i=0;i<=N;++i) printf("ls[%d]=%d,rs[%d]=%d vv[%d]=%d\n",i,ls[i],i,rs[i],i,vv[i]);
    dfs(rs[0]);
	return 0;
}
