/**
序列合并
luogu P1631

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

#define for1(i,down,up) for(int i=down;i<=up;++i)
#define for0(i,down,up) for(int i=down;i<up;++i)
using namespace std;
int N;
int a[100100];
int b[100100];

int result[100100];

/**
fake O(n)
80
*/
/*int main()
{
    //std::ios::sync_with_stdio(false);
    scanf("%d",&N);
    for1(i,1,N)
    scanf("%d",&a[i]);
    for1(i,1,N)
    scanf("%d",&b[i]);
    while(0)for1(i,1,N)
    {
        cout<<a[i]<<"\t"<<b[i]<<endl;
    }
    for1(i,1,N)
    q.push(a[1]+b[i]);
    bool bb=false;
    for1(i,2,N)
    {
        for1(j,1,N)
        {
            if(a[i]+b[j]<q.top())
            {
                q.pop();
                q.push(a[i]+b[j]);
            }
            else
            {
                if(j==1)
                    bb=true;
                break;
            }
        }
        if(bb)
            break;
    }
    for(int i=N; i>=1; --i)
    {
        result[i]=q.top();
        q.pop();
    }
    for(int i=1; i<=N; ++i)
        printf("%d ",result[i]);
    printf("\n");
    return 0;
}*/

struct node
{
    int val;
    int aid;
    int bid;
    friend bool operator <(node a,node b)
    {
        return a.val<b.val;
    }
    friend bool operator >(node a,node b)
    {
        return a.val>b.val;
    }
};
priority_queue <node ,vector<node>,greater<node> > q;
node Node(int v,int a,int b)
{
    static node l_node;
    l_node.aid=a;
    l_node.bid=b;
    l_node.val=v;
    return l_node;
}
int main()
{
    scanf("%d",&N);
    for1(i,1,N)
        scanf("%d",&a[i]);
    for1(i,1,N)
        scanf("%d",&b[i]);
    for(int i=1;i<=N;i++)
        q.push(Node(a[i]+b[1],i,1));
    //for(int i=1;i<=N;i++)
    //    printf("%d",q.top().val),q.pop();
    for(int i=1;i<=N;i++)
    {
        node t=q.top();
        printf("%d ",t.val);

        q.pop();
        t.bid++;
        t.val=a[t.aid]+b[t.bid];
        q.push(t);
    }
    return 0;
}
