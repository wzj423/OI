#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
const int base=129;
const int mod1=10020423,mod2=13010319;
int N;
int ht1[15000010],ht2[15000010],ans;
string t;
// code

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        cin>>t;
        int vv1=0,vv2=0;
        for(int i=0;i<t.size();++i)
            vv1=(vv1*base+t[i])%mod1,vv2=(vv2*base+t[i])%mod2;
        if(!ht1[vv1]&&!ht2[vv2])
            ht1[vv1]=i,ht2[vv2]=i,++ans;
    }
    printf("%d\n",ans);
    return 0;
}
