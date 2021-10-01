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
double A,B,C,D;
// code
inline double F(double x)
{
    return A*x*x*x+B*x*x+C*x+D;
}
void init()
{
    scanf("%lf%lf%lf%lf",&A,&B,&C,&D);
}
void work()
{
    for(double i=-100;i<=100;i+=0.5)
    {
        //printf("F(%d)=%.2f\n",i,F(i));
        //if(fabs(F(i))<=1e-4)
        //{
        //    printf("%.2f ",double(i));
        //}
        if(F(i)<=0&&F(i+0.5)>0)
        {
            double L=i,R=i+0.5;
            for(int j=1;j<=100;++j)
            {
                double mid=(L+R)/2;
                if(F(mid)<0) L=mid;
                else R=mid;
            }
            printf("%.2f ",L);
        }
        else if(F(i)>=0&&F(i+0.5)<0)
        {
            double L=i,R=i+0.5;
            for(int j=1;j<=100;++j)
            {
                double mid=(L+R)/2;
                if(F(mid)>0) L=mid;
                else R=mid;
            }
            printf("%.2f ",L);           
        }

    }
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}