#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int a[200010];
int N;
int Max;
int MaxInArray=-0x3f3f3f3f;
int ans;
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
        {
            cin>>a[i];
            MaxInArray=max(MaxInArray,a[i]);
        }
    for(int i=1;i<=N;i++)
    {
        if(Max+a[i]>0)
            Max+=a[i];
        else
            Max=0;
        ans=max(Max,ans);
    }
    if(MaxInArray<=0)
        cout<<MaxInArray;
    else
        cout<<ans<<endl;
}
