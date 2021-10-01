#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <string>
#include <cmath>
#include <cctype>

#include <algorithm>

using namespace std;
struct P
{
    int index;
    int score;
};
bool operator < (P a,P b)
{
    if(a.score!=b.score)
        return a.score>b.score;
    else
        return a.index<b.index;
}
P people[5005];
int N,M;
int main()
{
    cin>>N>>M;
    for (int i=1;i<=N;i++ )
    {
        cin>>people[i].index>>people[i].score;
    }
    sort(people+1,people+N+1);
    /*for (int i=1;i<=N;i++ )
    {
        cout<<people[i].index<<" "<<people[i].score<<endl;
    }*/
    int tmp=M*1.5;
    int line=people[tmp].score;
    int ans=0;
    for (int i=1;i<=N&&people[i].score>=line;i++) ans++;
    cout<<line<<" "<<ans<<endl;

    for (int i=1;i<=N&&people[i].score>=line;i++ )
    {
        cout<<people[i].index<<" "<<people[i].score<<endl;
    }
    return 0;
}
