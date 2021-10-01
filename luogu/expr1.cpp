#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;
string expr;
int s;
int main()
{
    cin>>expr;
    int len=expr.size();
    for(int i=0;i!=len;i++)
    {
        if(expr[i]=='(')
            s++;
        if(expr[i]==')')
            s--;
        if(s<0)
        {
            cout<<"NO"<<endl;
            exit(0);
        }
    }
    if(s>0)
        cout<<"NO"<<endl;
    else
        cout<<"YES"<<endl;
    return 0;
}
