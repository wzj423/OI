#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
typedef long long LL;
int N,M;
const int prime[]= {35109,20423,99997,85791};
LL a[110][10];//取模后的常数
string ss;
vector<LL> ans;
// code
void init()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<=N; ++i)
    {
        cin>>ss;
        bool b=false;
        for(int j=0; j<ss.size(); ++j)
        {
            if(ss[j]=='-')
                b=true;
            else
                for(int k=0; k<4; ++k)
                    a[i][k]=(a[i][k]*10+ss[j]-'0')%prime[k];
        }
        if(b)
            for(int k=0; k<4; ++k)
                a[i][k]=(prime[k]-a[i][k])%prime[k];
    }
    if(0)for(int k=0; k<4; ++k)
        {
            for(int i=0; i<=N; ++i)
                printf("%lld ",a[i][k]);
            puts("");
        }
}
void work()
{
    LL fans[4];
    for(int i=1; i<=M; ++i)
    {
        memset(fans,0,sizeof fans);
        for(int j=N; j>=0; --j)
        {
            for(int k=0; k<4; ++k)
            {
                fans[k]*=i;
                fans[k]+=a[j][k];
                fans[k]%=prime[k];
            }
        }
        if(fans[0]==0&&fans[1]==0&&fans[2]==0&&fans[3]==0)
            ans.push_back(i);
        //printf("try %d, res is %lld %lld %lld\n",i,fans[0],fans[1],fans[2]);

    }
    cout<<ans.size()<<endl;
    for(int i=0; i<ans.size(); ++i)
        printf("%lld\n",ans[i]);
}
int main()
{
    //freopen("C:\\Users\\Mike-Wu\\Downloads\\equationa6.in","r+",stdin);
    freopen("equationa.out","w+",stdout);
    freopen("equationa.in","r+",stdin);
    init();
    work();
    return 0;
}