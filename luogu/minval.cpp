/**
minval
Luogu P 2085
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define  ll long long
ll N,M;
ll a[3];
priority_queue <ll/*,vector<int>,less<int>*/ > q;
#define val(a,b,c,x) (a*x*x+b*x+c)
/*inline ll val(ll a,ll b,ll c,ll x)
{
    return a*x*x+b*x+c;
}*/
void calc()
{
    for(int j=1; j<=M; j++)
    {
        if(val(a[0],a[1],a[2],j)>=q.top())
            break;
        q.pop();
        q.push(val(a[0],a[1],a[2],j));

    }
}
int res[1000000];
int main()
{
    freopen("minval.in","r+",stdin);
    freopen("minval.out","w+",stdout);
    //std::ios::sync_with_stdio(false);
    /*cin>>N>>M;
    cin>>a[0]>>a[1]>>a[2];*/
    //if(N==)
    scanf("%d%d",&N,&M);
    scanf("%d%d%d",&a[0],&a[1],&a[2]);
    for(int i=1;i<=M;i++)
        q.push(val(a[0],a[1],a[2],i));
    for(int i=1; i<N; i++)
    {
        scanf("%d%d%d",&a[0],&a[1],&a[2]);
        calc();
        //cout<<i<<endl;
    }
    //system("pause");
    //cout<<q.size()<<endl;
    for(int i=M-1;i>=0&&!q.empty();i--)
    {
        res[i]=q.top();
        q.pop();
    }
    for(int i=0;i<M;i++)
        cout<<res[i]<<" ";
    cout<<endl;
    return 0;
}
