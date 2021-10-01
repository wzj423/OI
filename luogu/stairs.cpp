#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
#define ll long long int
int N,K;

ll check(ll n,ll k)
{
    if(k==1||n==k)
        return 1;
    if(n<k||k<=0)
        return 0;
    return check(n-k,k)+check(n-1,k-1);
}
int main()
{

    cin>>N>>K;
    cout<<check(N,K);

    return 0;
}
