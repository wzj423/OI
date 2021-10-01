/**
等价表达式
Luogu P1054
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
typedef long long LL;
string example;
LL N;
LL fitin[40];
LL testdata[]= {1231,3721,19,217};
const LL mod=1000007;
string option[40];
stack <LL> numStack;
stack <LL> chStack;
LL prio[300];
// code
void clearStack(stack <LL> & s)
{
    while(!s.empty()) s.pop();
}
void init()
{
    freopen("equal.in","r+",stdin);
    freopen("equal.out","w+",stdout);
    getline(cin,example);
    example='('+example+')';
    cin>>N;
    getline(cin,option[0]);
    for(LL i=1; i<=N; ++i)
    {
        getline(cin,option[i]);
        option[i]='('+option[i]+')';
    }
    //设置优先级
    prio['+']=1;
    prio['-']=2;
    prio['*']=3;
    prio['/']=4;
    prio['^']=5;
    prio['(']=-10;
    prio[')']=10;

}
LL poww(LL x,LL y)
{
    //算次幂
    long long a=1;
    for(LL i=0; i<y; i++)
        a=a*x%mod;
    return a;
}
LL checkNum(LL x,LL y,LL ch)
{
    switch(ch)
    {
    case '+':
        return (x+y)%mod;
    case '-':
        return (x-y)%mod;
    case '*':
        return ((x%mod)*(y%mod))%mod;
    case '^':
        return poww(x,y);
    }
}
LL calc(string & ss,LL x)
{
    clearStack(numStack);
    clearStack(chStack);
    LL len=ss.size();
    bool isAnalysingNum=true;
    for(LL i=0; i<len; ++i)
    {
        if(ss[i]==' ') continue;//删除额外空格
        if(isdigit(ss[i]))//如果是数字
        {
            if(isAnalysingNum==false)//之前没有
            {
                //printf("Pushed num:%d\n",ss[i]-'0');
                numStack.push(ss[i]-'0');//新加一个数字
                isAnalysingNum=true;//标记
            }
            else
            {
                LL t=numStack.top();//更改数字
                numStack.pop();
                t=t*10+ss[i]-'0';
                numStack.push(t);
                //printf("Pushed num(readd):%d\n",numStack.top());
            }
        }
        else if(isalpha(ss[i]))//是未知数
        {
            numStack.push(x);
            //printf("Pushed x:%d\n",x);
            isAnalysingNum=false;
        }
        else//是字母
        {
            isAnalysingNum=false;//取消数字痕迹
            if(ss[i]=='(')
            {
                //printf("Pushed character:%c\n",ss[i]);
                chStack.push(ss[i]);
            }
            else if(ss[i]==')')
            {
                //printf("Met character:%c\n",ss[i]);
                while(chStack.top()!='(')
                {
                    LL y=numStack.top();
                    numStack.pop();
                    LL x=numStack.top();
                    numStack.pop();
                    char ch=chStack.top();
                    chStack.pop();
                    //cout<<x<<ch<<y<<"="<<checkNum(x,y,ch)<<endl;
                    numStack.push(checkNum(x,y,ch));
                         //          cout<<char(chStack.top())<<endl;
                         //         cout<<LL(numStack.top())<<endl;
                }
                //cout<<chStack.size()<<endl;
                //cout<<"leave calc"<<endl;
                chStack.pop();
                //cout<<"del the ("<<endl;
            }
            else if(prio[ss[i]]>prio[chStack.top()])//优先级高的直接插入
            {
                //printf("Pushed character:%c\n",ss[i]);
                chStack.push(ss[i]);
            }
            else
            {
                //先结算
                while(prio[ss[i]]<=prio[chStack.top()])//高层次运算符要全部删除
                {
                    LL y=numStack.top();
                    numStack.pop();
                    LL x=numStack.top();
                    numStack.pop();
                    char ch=chStack.top();
                    chStack.pop();
                    //cout<<x<<ch<<y<<"="<<checkNum(x,y,ch)<<endl;
                    numStack.push(checkNum(x,y,ch));
                }

                //printf("Pushed character:%c\n",ss[i]);
                chStack.push(ss[i]);//再插入符号
            }
        }

    }
   // cout<<chStack.size()<<endl;
    while(!chStack.empty()&&chStack.top()!='(')
    {
        LL y=numStack.top();
        numStack.pop();
        LL x=numStack.top();
        numStack.pop();
        char ch=chStack.top();
        chStack.pop();
        //cout<<x<<ch<<y<<endl;
        numStack.push(checkNum(x,y,ch));
        //cout<<(numStack.top())<<endl;
    }
    //cout<<"endCalc"<<endl;
    return numStack.top();
}
void work()
{
    LL stdAns=(calc(example,1231)+mod)%mod;
    for(int i=1;i<=N;++i)
    {
        if((calc(option[i],1231)+mod)%mod==stdAns)
            //printf("\n----------------------\n%c\n-----------------------------------\n",i+'A'-1);
            printf("%c",i+'A'-1);
        //cout<<"calc"<<i<<"="<<calc(option[i],1231)<<"|"<<stdAns<<endl;
    }
}
int main()
{
    init();
    //cout<<poww(2,40)<<endl;
    //calc(option[3],100);
    //cout<<numStack.top()<<endl;
    work();
    //cout<<calc(option[6],1231);
    return 0;
}
