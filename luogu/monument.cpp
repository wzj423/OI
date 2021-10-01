/**
Luogu P1094
纪念品分组
*/
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
int a[30005];
int W,N;
int ans=0;
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>W>>N;
    for(int i=0;i<N;i++)
        cin>>a[i];
    sort(a,a+N);
    int lp=0,rp=N-1;
    while(lp<rp)
    {
        if(a[lp]+a[rp]<=W)
        {
            lp++;
            rp--;
            ans++;
        }
        else
        {
            rp--;
            ans++;
        }
    }
    if(lp==rp)
        ans++;
    cout<<ans<<endl;
    return 0;
}
