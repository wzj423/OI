/**
蚯蚓
Luogu P2827
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
int a,b;
// code

void init()
{
    scanf("%d%d",&a,&b);
}
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int ret=exgcd(b,a%b,x,y);
    int t=y;
    y=x-(a/b)*y;
    x=t;
    return ret;
}
void work()
{
    int x,y;

    int A=a;
    int B=-b;
    int C=1;
    int D=exgcd(A,B,x,y);
    x=x*(C/D);
    y*=(C/D);
    x=(x%b+b)%b;
    //cout<<x<<" "<<y<<endl;
    cout<<x<<endl;

}
int main()
{
    init();
    work();
    return 0;
}





