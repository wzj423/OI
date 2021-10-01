/**
侦探游戏
Luogu P1039
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
int M,N,P;
struct _info
{
    string name;
    int myGuilty;//0 说了自己有罪 1 说了自己无罪 -1 不确定
    int otherGuilty[20];//0 编号为i的人有罪 1无罪 -1 不确定
    int today;//0 不确定
    _info()
    {
        memset(otherGuilty,-1,sizeof(otherGuilty));
        today=myGuilty=-1;
    }
} Info[40];
int InfoCnt=0;
int faith[40];//0 编号为i的人诚实 1不诚实 -1 不确定
int guilty[40];
// code
int findId(string & ss)
{
    int pos=ss.find(':');
    string realName=ss.substr(0,pos-0);
    for(int i=1; i<=M; ++i)
        if(Info[i].name==realName)
            return i;
    return -1;
}
int findTarget(string & ss)
{
    int pos1=ss.find(": ");
    int pos2=ss.find(" is");
    string realName=ss.substr(pos1+2,pos2-pos1-2);
    for(int i=1; i<=M; ++i)
        if(Info[i].name==realName)
            return i;
    return -1;
}
int findDate(string &ss)
{
    if(ss.find("Monday")!=string::npos)
        return 1;
    if(ss.find("Tuesday")!=string::npos)
        return 2;
    if(ss.find("Wednesday")!=string::npos)
        return 3;
    if(ss.find("Thursday")!=string::npos)
        return 4;
    if(ss.find("Friday")!=string::npos)
        return 5;
    if(ss.find("Saturday")!=string::npos)
        return 6;
    if(ss.find("Sunday")!=string::npos)
        return 7;
}
void preAnalyse()
{
    string ss;
    char ch=getchar();
    while(isspace(ch)) ch=getchar();
    ungetc(ch,stdin);
    getline(cin,ss,'\n');
    int id=1;
    id=findId(ss);
    //暴力处理
    if(ss.find("I am guilty")!=string::npos)
    {
        Info[id].myGuilty=true;
    }
    else if(ss.find("I am not guilty")!=string::npos)
    {
        Info[id].myGuilty=false;
    }
    else if(ss.find("is guilty")!=string::npos)
    {
        int target=findTarget(ss);
        Info[id].otherGuilty[target]=true;
    }
    else if(ss.find("is not guilty")!=string::npos)
    {
        int target=findTarget(ss);
        Info[id].otherGuilty[target]=false;
    }
    else if(ss.find("Today is")!=string::npos)
    {
        int date=findDate(ss);
        Info[id].today=date;
    }
}
void init()
{
    //freopen("logic.in","r+",stdin);
    //freopen("logic.out","w+",stdout);
    scanf("%d%d%d",&M,&N,&P);
    for(int i=1; i<=M; ++i)
        cin>>Info[i].name;
    string t;
    getline(cin,t);
    for(int i=1; i<=P; ++i)
        preAnalyse();
}
void work()
{
    int guiltyOneCnt=0;
    int guiltyOne=0;
    for(int day=1; day<=7; ++day) // 当前日期
    {
        memset(faith,-1,sizeof(faith));
        for(int gid=1; gid<=M; ++gid) // 有罪的人的编号
        {
            //cout<<"-------------------------------------------------"<<endl;
            //cout<<"day is"<<day<<" And thought gid is:"<<gid<<endl;
            int lieCnt=0,undeterminedCnt=0;
            bool isvalid=true;
            for(int i=1; i<=M; ++i)
            {
                bool T=false,F=false;
                if(Info[i].today!=-1)
                {
                    if(Info[i].today==day)
                    {
                        //cout<<"\t"<<"Set true!"<<endl;
                        T=true;
                    }
                    else
                    {
                        //cout<<"\t"<<"Set false!"<<endl;
                        F=true;
                    }
                }
                if(Info[i].myGuilty!=-1)
                {
                    if(Info[i].myGuilty==true&&i==gid
                       ||Info[i].myGuilty==false&&i!=gid)
                    {
                        //cout<<"\t"<<"Set true!"<<endl;
                        T=1;
                    }
                    else
                    {
                        //cout<<"\t"<<"Set false!"<<endl;
                        F=1;
                    }
                }
                for(int j=1; j<=M; ++j)
                {
                    if(Info[i].otherGuilty[j]==-1)
                        continue;
                    if((Info[i].otherGuilty[j]==true&&j==gid)||(Info[i].otherGuilty[j]==false&&j!=gid))
                    {
                        //cout<<"\t"<<"Set true!"<<endl;
                        T=true;
                    }
                    else
                    {
                        //cout<<"\t"<<"Set false!"<<endl;
                        F=true;
                    }
                }
                //cout<<Info[i].name<<" True:"<<T<<" False"<<F<<endl;
                if(T&&F)
                {
                    isvalid=false;
                    break;

                }
                else if(F)
                    lieCnt++;
                else if(!T&&!F)
                    undeterminedCnt++;

            }
            if(isvalid)
            {
                //cout<<"determining``"<<lieCnt<<" "<<undeterminedCnt<<endl;
                if(lieCnt>N||lieCnt+undeterminedCnt<N)
                    continue;
                else
                {
                    guilty[gid]=true;
                    //guiltyOneCnt++;
                    guiltyOne=gid;
                    //cout<<"Found the killer!"<<endl;
                    //cout<<Info[gid].name<<endl;
                }
            }
        }
    }
    for(int i=1;i<=M;++i)
    {
        if(guilty[i])
        {
            guiltyOneCnt++;
            guiltyOne=i;
        }
    }
    if(guiltyOneCnt>1)
        cout<<"Cannot Determine"<<endl;
    else if(guiltyOneCnt==0)
        cout<<"Impossible"<<endl;
    else
        cout<<Info[guiltyOne].name<<endl;
}
int main()
{
    init();
    work();
    return 0;
}
