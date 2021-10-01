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
//推导：设沸腾温度为a
//则第一杯温度为a,需要加热t1=a 
//第二杯可以中和的最高温度为a/2,需要加热t2=a/2 
//第三杯可以中和的最高温度为t3=(a/4+a)/2=5a/8,需要加热t3=3a/8 
//第四杯可以中和的最高温度为t4=((a/8+5a/8)/2+a)/2=11a/16,需要加热t4=5/16 
//则t3/t2=3/4=1-1/4,  t4/t3=5/6=1-1/6
//继续推导得t(n+1)/t(n)=1-1/2n

int main(){
    int n;
    double res,now;
    cin>>n;
    now = 420000.00/n;
    for(int i=1;i<=n;i++){
        res+=now;
        now*=(1-0.5/i);
    }    
    printf("%.2lf\n", res);
    //system("pause");
    return 0;
} 