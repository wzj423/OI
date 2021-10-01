#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
#define N 3000000+1
typedef long long ll;
ll phi[N];
void init()
{
    for(int i=1; i<N; i++)
        phi[i]=i;
    for(int i=2; i<N; ++i)
    {
        if(i==phi[i])
            for(int j=i; j<N; j+=i)
            {
                phi[j]=phi[j]/i*(i-1);
            }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    init();
    int cas,a,b;
    while(cin>>a>>b)
    {
        ll ans=0;
        for(int i=a; i<=b; i++)
            ans+=phi[i];
        cout<<ans<<endl;
    }
    return 0;
}
