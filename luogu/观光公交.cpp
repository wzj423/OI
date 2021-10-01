#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
int N,M,K;
int D[1010];
int stt[1010];//到站时间
int edt[1010];//出站时间
int late[1010];//最晚乘客到达时间
int down[1010];//每站下车的数量
int people[10010][3];//0 时间 1 始站 2 终站
int num[1010];
// code
void init()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1; i<N; ++i)
        scanf("%d",&D[i]);
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d",&people[i][0],&people[i][1],&people[i][2]);
        ++down[people[i][2]];
        late[people[i][1]]=max(late[people[i][1]],people[i][0]);
    }
}
void update_time()//重新计算时间
{
    for(int i=1; i<=N; ++i)
    {
        stt[i]=max(late[i-1],stt[i-1])+D[i-1];//edt[i-1]+D[i-1];
        edt[i]=max(late[i],stt[i]);
        //printf("id=%d st:%d ed:%d \n",i,stt[i],edt[i]);
    }
}
void put_ac()
{
    int target=-1,maxNum=0;
    memset(num,0,sizeof num);
    for(int i=N-1; i>=1; --i) //遍历每一段i,i+1
    {
        if(D[i]==0)
            continue;
        if(stt[i+1]<=late[i+1])
            num[i]=down[i+1];
        else
            num[i]=down[i+1]+num[i+1];
    }
    for(int i=1; i<N; ++i)
        if(num[i]>maxNum)
        {
            maxNum=num[i];
            target=i;
        }
    if(target!=-1)
        --D[target];
    //printf("Choose seg %d help %d people ,curtime is %d\n",target,maxNum,D[target]);
}
void work()
{
    for(int i=1; i<=K; ++i)
    {
        update_time();
        put_ac();
    }
    update_time();
    int ans=0;
    for(int i=1; i<=M; ++i)
    {
        int st=people[i][0],ed=stt[people[i][2]];
        ans+=ed-st;
    }
    printf("%d\n",ans);
}
int main()
{
    freopen("bus.in","r+",stdin);
    freopen("bus.out","w+",stdout);
    init();
    work();
    return 0;
}