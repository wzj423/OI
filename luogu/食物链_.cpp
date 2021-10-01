/**
Luogu P2024
并查集
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
#include <set>

using namespace std;
enum rela
{
    same=0,

    eat=1,
    beEaten=2,
};
int father[50010];
int faRelation[50010];

int N,K;
int b1,x,y,rx,ry;
int ans;
/**
Help:
    A eat B only when:
    A-C =0  B-C=1
    A-C =1  B-C=2
    A-C =2  B-C=0
    Conclusion:
    A eat B only when:
        A-C=(B-C + 1)%3
---------------------------------
Enum:
    A-B=0 A-C=0 B-C=0
    A-B=0 A-C=1 B-C=1
    A-B=0 A-C=2 B-C=2
    A-B=1 A-C=0 B-C=2
    A-B=1 A-C=1 B-C=0
    A-B=1 A-C=2 B-C=1
    A-B=2 A-C=0 B-C=1
    A-B=2 A-C=1 B-C=2
    A-B=2 A-C=2 B-C=0
Conclusion:
*/
inline int B2C(int _A2B,int _A2C)
{
    return (3-_A2B+_A2C)%3;
}
inline int A2C(int A2B,int B2C)
{
    return (A2B+B2C+3)%3;
}

int getFather(int x)
{
    int root=x;
    int tmp;
    if(father[root]!=0)
    {
        tmp=getFather(father[root]);
        faRelation[root]=A2C(faRelation[root],faRelation[father[root]]);
        root=father[root]=tmp;
    }
    return root;
}
int join(int a,int b,int relation)//!relation A->B
{
    int ra=getFather(a),rb=getFather(b);
    if(ra!=rb)
    {
        father[ra]=rb;//!合并集合
        int a_rb=A2C(relation,faRelation[b]);
        int a_ra=faRelation[a];
        faRelation[ra]=B2C(a_ra,a_rb);
    }
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1; i<=K; ++i)
    {
        scanf("%d%d%d",&b1,&x,&y);
        if(x>N||y>N||(x==y&&b1==2))
        {
            ++ans;
        }
        else
        {
            rx=getFather(x);
            ry=getFather(y);
            if(rx!=ry)
            {
                join(x,y,b1-1);
            }
            else if(faRelation[x]!=(faRelation[y]+b1-1)%3)
            {
                ans++;
            }
        }
    }

    cout<<ans<<endl;
    return 0;
}
