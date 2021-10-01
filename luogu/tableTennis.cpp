#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <ctime>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
string race;

void inputString()
{
    char temp=1;
    while ( temp != 'E' )
    {
        cin >> temp;
        if ( !isalpha ( temp ) )
            ;
        else
            race += temp;
    }
}
void deal_with()
{
    int W=0,L=0;
    const int length=race.size();
    for(int i=0;i!=length;i++)
    {
        if(race[i]=='W')
            W++;
        else if(race[i]=='L')
            L++;
        if(max(W,L)>=11&&abs(W-L)>=2)
        {
            cout<<W<<':'<<L<<endl;
            W=L=0;
        }
    }
    cout<<W<<":"<<L<<endl;
    cout<<endl;
    W=0,L=0;
    for(int i=0;i!=length;i++)
    {
        if(race[i]=='W')
            W++;
        else if(race[i]=='L')
            L++;
        if(max(W,L)>=21&&abs(W-L)>=2)
        {
            cout<<W<<':'<<L<<endl;
            W=L=0;
        }
    }
    cout<<W<<":"<<L<<endl;
}
int main()
{
    inputString();
    deal_with();
    return 0;
}
