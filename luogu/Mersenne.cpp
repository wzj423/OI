/**
NOIp2003 麦森数
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

int P;
const int lenDigit=505;
int ans[510];
int base[510];
int help[510];
//int help[510];
void mul(int *to,int *from1,int *from2)
{
    memset(to,0,sizeof(help));
    for(int i=0; i<from1[lenDigit]; i++)
        for(int j=0; j<from2[lenDigit]; j++)
        {
            if(i+j>=500)
                continue;
            to[i+j]+=from1[i]*from2[j];
            if(to[i+j]>=10)
            {
                to[i+j+1]+=(to[i+j]/10);
                to[i+j]%=10;
            }
        }
    to[lenDigit]=from1[lenDigit]+from2[lenDigit];
    if(to[lenDigit]>=500)
        to[lenDigit]=500;
    else if(to[lenDigit]<=500&&to[to[lenDigit]-1]==0)
        to[lenDigit]--;

}
void init()
{
    base[0]=2;
    ans[0]=1;
    ans[lenDigit]=1;
    base[lenDigit]=1;
}
void display(int * op)
{
    cout<<"Length:"<<op[lenDigit]<<endl;
    for(int i=op[lenDigit]-1;i>=0;i--)
        cout<<op[i];
    cout<<endl;
}
int main()
{
    init();
    cin>>P;
    cout<<(long long )(P*log10(double(2))+1)<<endl;
    while(P)
    {
        if(P&1)
        {
            mul(help,ans,base);
            memcpy(ans,help,sizeof(help));
        }
        mul(help,base,base);
        memcpy(base,help,sizeof(help));
        P>>=1;
    }
    for(int i=500-1;i>=1;i--)
    {
        cout<<ans[i];
        if(i%50==0)
            cout<<endl;
    }
    cout<<ans[0]-1<<endl;
    return 0;
}
