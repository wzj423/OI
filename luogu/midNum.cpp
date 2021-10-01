/**
中位数
Luogu P1168
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

int N;
int a[100010];
priority_queue<int> qBig;
priority_queue<int,vector<int>,greater<int> > qSmall;
int main()
{
    scanf("%d",&N);
    for(int i=1; i<=N; i++)
        scanf("%d",&a[i]);
    qBig.push(a[1]);
    printf("%d\n",a[1]);
    for(int i=2; i<=N; ++i)
    {
        /*qBig.push(a[i]);
        while(qBig.size()-qSmall.size()>1)
        {
            qSmall.push(qBig.top());
            qBig.pop();
        }

        if(i&1)
            printf("%d ",qBig.top());*/
        if(a[i]>qBig.top())
            qSmall.push(a[i]);
        else
            qBig.push(a[i]);

        if(i&1)
        {
            for(int j=qBig.size(); j<i/2+1; j++)///QBig小
            {
                qBig.push(qSmall.top());
                //cout<<"qBig pushed:"<<qSmall.top()<<endl;
                qSmall.pop();
            }
            for(int j=qSmall.size(); j<i/2; j++) ///QBig大
            {
                qSmall.push(qBig.top());
                qBig.pop();
            }

            printf("%d\n",qBig.top());
        }

    }
    return 0;
}
