#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>

#include <algorithm>
#include <queue>

using namespace std;
struct carpet
{
    int a=-1;
    int b=-1;
    int g=0;
    int k=0;
    bool isIncluded(int x,int y);
}Array[10010];
bool carpet::isIncluded(int x,int y)
{
    if(a<=x&&b<=y&&a+g>=x&&b+k>=y)
        return true;
    else
        return false;
}
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>Array[i].a>>Array[i].b>>Array[i].g>>Array[i].k;
    }
    int x1,y1;
    cin>>x1>>y1;
    for(int i=N;i>=1;i--)
    {
        if(Array[i].isIncluded(x1,y1))
            {
                cout<<i<<endl;
                exit(0);
            }
    }
    cout<<-1;
    return 0;
}
