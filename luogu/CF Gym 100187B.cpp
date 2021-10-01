#include <bits/stdc++.h>

using namespace std;
char ss[200010];
int cnt[30];
int N;
int main() {
    scanf("%s",ss+1);
    N=strlen(ss+1);
    for(int i=1;i<=N;++i) {
        ++cnt[ ss[i]-'a' ];
    }
    double ans=0;
    for(int i=1;i<=N;++i) {
        ans+=1.0*cnt[ss[i]-'a']/N;
    }
    printf("%.9lf\n",ans);
    return 0;
}