#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cctype>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <bits/stdc++.h>

using namespace std;
int Bucket[1010];
int N;
int ans;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int tmp;
        cin>>tmp;
        Bucket[tmp]++;
    }
    for(int i=1;i<=1005;i++)
        if(Bucket[i]!=0)
            ans++;
    cout<<ans<<endl;
    for(int i=1;i<=1005;i++)
        if(Bucket[i]!=0)
            cout<<i<<" ";

    return 0;
}
