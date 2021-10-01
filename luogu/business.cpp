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
struct busiInfo
{
    int price;
    int num;
}busiList[10010];
int endOfList;
bool operator < (busiInfo a,busiInfo b)
{
    return a.price<b.price;
}
int expectPrice;
int upperStep;
int main()
{
    cin>>expectPrice;
    for(int i=0;;i++)
    {
        cin>>busiList[i].price>>busiList[i].num;
        if(busiList[i].price==-1)
            endOfList=i,break;
    }
    cin>>upperStep;
    for(int i=0;;i++)
    {
        for(int j=0;j<endOfList;j++)
        {

        }
    }
    return 0;
}
