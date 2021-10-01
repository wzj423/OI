#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int N;
struct ship
{
    int time;
    int num;
    vector<int> people;
};
queue <ship> Q;
int nation[100010];
// code
void init()
{
    //freopen("in/port14.in","r+",stdin);
    //freopen("port.out","w+",stdout);
    scanf("%d",&N);
}
void work()
{
    int curNum=0,curTime=0;

    for(int i=1;i<=N;++i)
    {
        ship t;
        scanf("%d%d",&t.time,&t.num);
        for(int j=1;j<=t.num;++j)
        {
            int temp;
            scanf("%d",&temp);
            t.people.push_back(temp);
            nation[temp]++;
            if(nation[temp]==1)
                curNum++;
        }
        Q.push(t);
        while(Q.front().time<=t.time-86400)
        {
            for(int j=0;j<Q.front().num;++j)
            {
                int temp=Q.front().people[j];
                nation[temp]--;
                if(nation[temp]==0)
                    curNum--;
            }
            Q.pop();
        }
        printf("%d\n",curNum);
    }
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}