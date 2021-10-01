/**
Noip2006 PJ T4
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>

#include <queue>
#include <stack>
#include <algorithm>
#include <bitset>
using namespace std;
bitset <64> s;
typedef unsigned long long ull;
typedef bitset<64> B;
int Base;
int N;
ull ans;
int main()
{
    cin>>Base;
    cin>>N;
    s=B(N);
    for(int i=0;i<=63;i++)
        if(s[i])
            ans+=pow(ull(Base),ull(i));
    cout<<ans<<endl;
    return 0;
}
