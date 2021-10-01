#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <algorithm>
#include <queue>
#include <stack>


using namespace std;
int N;
int lis[100000];
int main()
{
    cin>>N;
    priority_queue <int,vector<int>,greater<int> >que;
    int tmp;
    for(int i=0;i<N;i++)
    {
        cin>>tmp;
        que.push(tmp);
    }
    int ans=0;
    while(!que.empty())
    {
        int tmp1=que.top();
        que.pop();
        if(que.empty())
            break;
        int tmp2=que.top();
        que.pop();
        ans+=(tmp1+tmp2);
        que.push(tmp1+tmp2);
    }
    cout<<ans;
    return 0;
}
