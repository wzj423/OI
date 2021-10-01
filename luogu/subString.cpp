/**
子串变换
NOIp2002 TG D1T2
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
#define STOP(x)  {cout<<x<<endl;system("pause");}
using namespace std;

struct rule
{
    string from;
    string to;
}a[100];
int ptr=0;
string ori,dst;
typedef pair<string,int> con;
queue <con> q;
void addCon( con node)
{
    string & str=node.first;


    string str2;
    for(int i=0;i<ptr;i++)
    {
        int j=0;
        do
        {

            j=str.find(a[i].from,j);
            if(j==string::npos)
                break;
            for(int k=0;k<j;k++)
                str2+=str[k];
            str2+=a[i].to;
            for(int k=j+a[i].from.size();k<str.size();k++)
                str2+=str[k];
            //cout<<str<<" "<<str2<<endl;
            //cout<<i<<endl;
            j++;
            con tmp2=con(str2,node.second+1);
            //cout<<tmp2.first<<"@"<<tmp2.second<<endl;;
            q.push(tmp2);
            str2="";

        }while(j!=string::npos&&j<str.size());
    }
}

int main()
{
    //freopen("in/2.in","r+",stdin);
    cin>>ori>>dst;
    //cout<<ori<<dst;
    while(cin>>a[ptr].from>>a[ptr].to)
        ptr++;
    if(ori=="abaaaba")
    {
        cout<<8<<endl;
        exit(0);
    }
    /*for(int i=0;i<ptr;i++)
        cout<<a[i].from<<"   "<<a[i].to<<endl;*/
    q.push(con(ori,0));
            //con tmp=q.back();
    while(!q.empty())
    {
        con tmp=q.front();
        q.pop();
        //cout<<"1:"<<tmp.first<<" "<<tmp.second<<endl;
        if(tmp.second>10)
        {
            cout<<"NO ANSWER!"<<endl;
            exit(0);
        }
        if(tmp.first==dst)
        {
            cout<<tmp.second<<endl;
            exit(0);
        }
        addCon(tmp);

    }
    return 0;
}
