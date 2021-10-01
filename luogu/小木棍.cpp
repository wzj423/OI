/**
小木棍
LuoguP1120
*/
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
int N,sum,totNum;
int a[110],cnt;
int b[60];
bool used[110];
int stickLength;
/// code
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {
        int t;
        scanf("%d",&t);
        if(t<=50)
        {
            a[++cnt]=t;
            ++b[t];
            sum+=t;
        }
    }
    totNum=sum;
    sort(a+1,a+cnt+1,greater<int>());
    if(0)for(int i=1; i<=cnt; ++i)
        {
            printf("%d\n",a[i]);
        }
}
/*bool dfs(int stickDone,int lenDone)
{
    if(stickDone==sum/stickLength)
    {
        printf("%d",stickLength);
        exit(0);
    }
    if(stickLength-lenDone>totNum)
        return false;
    for(int i=50; i>=1; --i)
    {
        if((b[i]>0)&&(lenDone+i<=stickLength))
        {
            --b[i];
            totNum-=i;
            dfs(stickDone+(lenDone+i)/stickLength,(lenDone+i)%stickLength);
            totNum+=i;
            ++b[i];
            if(stickDone==0&&lenDone==0)
            {
                break;
            }
        }
    }
    return false;
}*/
bool dfs(int stickDone,int lenDone,int next=1)//从第next根木棒开始选
{
    int i,j;
    if(stickDone==sum/stickLength)
    {
        printf("%d",stickLength);
        exit(0);
    }
    if(stickLength-lenDone>totNum)
        return false;
    /*for(j=cnt; j>=1; --j)
    {
        if(used[j]==false)
        {
            if((lenDone+a[j])>stickLength)
            {
                return false;
            }
            else
            {
                break;
            }
        }
    }*/
    /*for(i=cnt; i>=1; --i)
    {
        if((!used[i])&&(lenDone+a[i]<=stickLength))
        {
            used[i]=true;
            totNum-=a[i];
            dfs(stickDone+(lenDone+a[i])/stickLength,(lenDone+a[i])%stickLength);
            totNum+=a[i];
            used[i]=false;
            if(lenDone==0)
            {
                break;
            }
            if(stickLength==lenDone+a[i])
            {
                break;
            }
            //int t=a[i];
            while(a[i-1]==a[i]) --i;
        }
        //else if(lenDone+a[i]>stickLength)
        //    break;
    }*/
    for(i=next; i<=cnt; ++i)
    {
        if((!used[i])&&(lenDone+a[i]<=stickLength))
        {
            used[i]=true;
            totNum-=a[i];
            //dfs(stickDone+(lenDone+a[i])/stickLength,(lenDone+a[i])%stickLength);
            if(lenDone+a[i]<stickLength)
            {
                dfs(stickDone,lenDone+a[i],i+1);
            }
            else
            {
                dfs(stickDone+1,0,1);
            }
            totNum+=a[i];
            used[i]=false;
            if(lenDone==0)
            {
                break;
            }
            if(stickLength==lenDone+a[i])
            {
                break;
            }
            while(a[i+1]==a[i]) ++i;
        }
        //else if(lenDone+a[i]>stickLength)
        //    break;
    }
    return false;
}
void work()
{
    for(int i=a[1]; i<=sum/2; ++i)
    {
        if(sum%i==0)
        {
            stickLength=i;
            //cout<<"dfs in"<<stickLength<<endl;
            dfs(0,0);
        }
    }
    printf("%d",sum);
}
int main()
{
    if(0)
    {
        freopen("sticka.in","r+",stdin);
        freopen("sticka.out","w+",stdout);
    }
    init();
    work();
    return 0;
}
