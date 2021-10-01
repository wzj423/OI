#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
char digit[]={"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
string result;
int base;
int inputNum;
void deal_with(int num,int b)
{
    int tempResult=num/b;
    int remainder=num%b;
    if(remainder<0)
    {
        remainder-=b;
        tempResult++;
    }
    result=digit[remainder]+result;
    //cout<<tempResult<<" "<<remainder<<endl;
    if(tempResult<abs(b)&&tempResult>0)
        {
            result=digit[tempResult]+result;
            return;
        }
    else
        deal_with(tempResult,b);
}
int main()
{
    //cout<<digit<<endl;
    //cout<<-937%-2<<-937/-2<<endl;
    cin>>inputNum>>base;
    deal_with(inputNum,base);
    cout<<inputNum<<"=";
    cout<<result;
    cout<<"(base"<<base<<")"<<endl;
    return 0;
}
