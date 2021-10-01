/**
Luogu P 1955
expect 100
fact 90
TLE 1
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
#include <map>
using namespace std;
typedef pair<int,int> c;
typedef map<int,int>::iterator Iter;
map <int,int> codeMap;

int K,N;
int dad[200100];
int rule[200010][3];
int hashLink[200010];
int rulePtr=0;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int get_dad(int x)
{
    int root=x;
    while(dad[root]!=0)
        root=dad[root];
    int tmp;
    while(x!=root)
    {
        tmp=dad[x];
        dad[x]=root;
        x=tmp;
    }
    return root;
}
void join(int a,int b)
{
    int ra=get_dad(a),rb=get_dad(b);
    if(ra!=rb)
        dad[ra]=rb;
}
int get_hashed(int x)
{
    int id=(x%198637);
    while(hashLink[id]!=0&&hashLink[id]!=x)
    {
        id=(id*13)%199037;
    }
    hashLink[id]=x;
    return id;
}
void addRule()
{
    ++rulePtr;
    //scanf("%d%d%d",&rule[rulePtr][0],&rule[rulePtr][1],&rule[rulePtr][2]);
    rule[rulePtr][0]=read();
    rule[rulePtr][1]=read();
    rule[rulePtr][2]=read();
    for(int i=0; i<2; i++)
    {
        rule[rulePtr][i]=get_hashed(rule[rulePtr][i]);
    }
}
void work()
{
    memset(dad,0,sizeof(dad));
    memset(rule,0,sizeof(rule));
    rulePtr=0;
    N=read();
    int e,x,y;
    bool isOk=true;
    for(int i=1; i<=N; ++i)
    {
        addRule();
    }
    for(int i=1; i<=N; ++i)
    {
        if(rule[i][2])
        {
            join(rule[i][0],rule[i][1]);
        }
    }
    for(int i=1; i<=N; ++i)
    {
        if(isOk&&rule[i][2]==0)
        {
            if(get_dad(rule[i][0])==get_dad(rule[i][1]))
            {
                isOk=false;
            }

        }
    }
    if(isOk)
        puts("YES");
    else
        puts("NO");
}

int main()
{
    freopen("D:\\prog.in","r+",stdin);
    freopen("prog.out","w+",stdout);
    K=read();
    for(int i=1; i<=K; ++i)
        work();

    return 0;
}
