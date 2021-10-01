#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <queue>
#define isOK(x) (x>0&&x<=M&&vis[x]==0)
using namespace std;
int help[410];//help[i] 第help[i]步到达第i层
bool vis[410];
int floor[210];//floor[i] -> 电梯代表数
int M,A,B;
queue <int> q;
void bfs(int id)
{
    q.push(id);
    while(!q.empty())
    {
        int temp=q.front();
        q.pop();
        if(temp==B)
            {
                //help[B]=help[temp];
                cout<<help[temp]<<endl;
                exit(0);
                return;
            }
        if(isOK(temp+floor[temp]))
        {
            q.push(temp+floor[temp]);
            help[temp+floor[temp]]=help[temp]+1;
            vis[temp+floor[temp]]=1;
        }
        if(isOK(temp-floor[temp]))
        {
            q.push(temp-floor[temp]);
            help[temp-floor[temp]]=help[temp]+1;
            vis[temp-floor[temp]]=1;
        }
    }
}
int main()
{
    cin>>M>>A>>B;
    for(int i=1;i<=M;i++)
        cin>>floor[i];
    help[A]=0;
    bfs(A);
    if(A==B)
        cout<<0<<endl;
    if(vis[B])
        cout<<help[B]<<endl;
    else
        cout<<-1<<endl;
    return 0;
}
