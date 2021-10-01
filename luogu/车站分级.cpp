/**
车站分级
Luogu P1983
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
typedef long long LL;
int N,M;
int mat[1010][1010];
int inWayCnt[1010];
int outWayCnt[1010];
//TopSort data
queue <int> q;
bool vis[1010];
// code
void addEdge(int st,int ed)
{
    if(mat[st][ed]==0)
    {
        mat[st][ed]=1;
        ++inWayCnt[ed];
        ++outWayCnt[st];
    }

}
void delEdge(int st)
{
    for(int i=1; i<=N; ++i)
    {
        if(mat[st][i])
        {
            mat[st][i]=0;
            --outWayCnt[st];
            --inWayCnt[i];
        }
    }
}
void init()
{
    vector<int> stopSta;
    vector<int> unstopSta;
    scanf("%d%d",&N,&M);
    int up;
    for(int i=1; i<=M; ++i)
    {
        int x=0,y=0;
        scanf("%d%d",&up,&x);
        stopSta.push_back(x);
        //cout<<"Pushed stopped:"<<x<<endl;
        for(int j=2; j<=up; ++j)
        {

            scanf("%d",&y);
            stopSta.push_back(y);
            //cout<<"Pushed stopped:"<<y<<endl;
            for(int k=x+1; k<y; ++k)
            {
                unstopSta.push_back(k);
                //cout<<"Pushed unstopped:"<<k<<endl;
            }
            x=y;
        }
        for(int m=stopSta.size()-1; m>=0; --m)
            for(int n=unstopSta.size()-1; n>=0; --n)
            {
                addEdge(stopSta[m],unstopSta[n]);
                //cout<<"Add Edge:"<<stopSta[m]<<">>"<<unstopSta[n]<<endl;
            }
        stopSta.clear();
        unstopSta.clear();

    }
}
void TopSort()
{
    if(0)for(int i=1; i<=N; ++i)
    {
        cout<<"in"<<inWayCnt[i]<<" out"<<outWayCnt[i]<<endl;
    }
    int ans=0,delNum=0;
    for(ans=0; ans<=N; ++ans)
    {

        if(delNum==N)
            break;
        for(int j=1; j<=N; ++j)
        {
            if(inWayCnt[j]==0&&vis[j]==false)
            {
                q.push(j);

                vis[j]=true;
                delNum++;
            }
        }
        while(!q.empty())
        {
            int t=q.front();
            q.pop();
            delEdge(t);
        }

    }
    cout<<ans<<endl;
}
void work()
{
    TopSort();
}
int main()
{
    init();
    work();
    return 0;
}
