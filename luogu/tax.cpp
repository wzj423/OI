/**
税收与补贴问题
NOIp 2000 PJ T2
*/
//TODO
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

struct con
{
    int money;
    int num;
}a[100001];
int ptr=0;
int expect;
int maxBelow;

double lowBnd=-1000000,highBnd=1000000;


bool cmp(con a,con b)
{
    return a.money<b.money;
}
/*int calcSales(int money)
{
    bool b=false;
    int i;
    for(i=0;i<ptr;i++)
        if(a[i].money>=money)
            {
                b=true;
                break;
            }
    if(b)
        return a[i].num-(a[i].num-a[i-1].num)*(a[i].money-money)/(a[i].money-a[i-1].money);
    else
        return a[ptr-1].num-(money-a[ptr-1].money)*maxBelow;
}*/
void solve(int money)
{

}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>expect;
    do
    {
        cin>>a[ptr].money>>a[ptr].num;
        //ptr++;
    } while (a[ptr++].money!=-1);
    ptr--;
    cin>>maxBelow;
    sort(a,a+ptr,cmp);
    for(int i=0;i<ptr;i++)
        cout<<a[i].money<<a[i].num<<endl;
    for(int i=a[0].money;i<=a[ptr-1].money;++i)
    {
        solve(i);
    }
    return 0;
}
