#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int N;
int a[10010];
int ans;
int sum;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    const int sta=sum/N;
    for(int i=1;i<=N;i++)
    {
        if(a[i]!=sta)
        {
            a[i+1]+=(a[i]-sta);
            a[i]=sta;
            ans++;
        }
    }
    cout<<ans<<endl;

    return 0;
}
