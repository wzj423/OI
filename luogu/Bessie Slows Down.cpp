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
vector<int> tf,xf;
int N;
char ch;
int t;
// code

int main()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {   
        scanf("%1s%d",&ch,&t);
        if(ch=='T') tf.push_back(t);
        else        xf.push_back(t);
    }
    sort(tf.begin(),tf.end());
    sort(xf.begin(),xf.end());

    double dis=0,tim=0;
    int i=0,j=0,fnum=1;
    while(dis<1000)
    {
        if(i<tf.size()&&j<xf.size())
        {
            double timex=tf[i]-tim;
            double timey=(xf[j]-dis)*fnum;
            if(timex<timey)
            {
                tim+=timex;
                dis+=timex/fnum;
                ++i;
                ++fnum;
            }
            else
            {
                tim+=timey;
                dis+=timey/fnum;
                ++j;
                ++fnum;
            }
        }
        else if(i<tf.size())
        {
            double timex=tf[i]-tim;
            tim+=timex;
            dis+=timex/fnum;
            ++i;
            ++fnum;
        }
        else if(j<xf.size())
        {
            double timey=(xf[j]-dis)*(double)(fnum);
            tim+=timey;
            dis+=timey/fnum;
            ++j;
            ++fnum;
        }
        else
        {
            tim+=(1000-dis)*fnum;
            dis=1000;
        }
    }
    printf("%d\n",int(tim+0.5));
    return 0;
}