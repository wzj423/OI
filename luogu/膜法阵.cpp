#include<cstdio>  
#include<algorithm>  
#include<iostream>  
#include<cstring>  
#include<cmath>  
int n,m,dis,y;  
int a[15001],b[15001],c[15001],d[15001];//a，b，c，d分别表示每件物品四个位置的个数  
int h[40001],w[15001];//h表示物品的魔法值，w表示每个魔法值出现的次数  
int main()  
{  
    scanf("%d%d",&n,&m);  
    for(int i=1;i<=m;i++){scanf("%d",&h[i]);w[h[i]]++;}  
      
    for(int i=1;i<=n/9;i++)//枚举i  
    {  
        dis=8*i+1;y=0;//dis表示A到C的最小距离，y表示A、B的个数  
        for(int j=n-9*i-1;j>=1;j--)//j就是A点，j+2i就是B点  
        {  
            y+=w[j+dis]*w[j+dis+i];//A、B的个数取决于C、D有多少对，所以用C、D个数来乘  
            a[j]+=y*w[j+i+i];  
            b[j+i+i]+=y*w[j];  
        }  
        dis=9*i+1;y=0;//dis表示D到A的最小距离，y表示C、D的个数  
        for(int j=9*i+2;j<=n;j++)//j就是D点，j-i就是C点  
        {  
            y+=w[j-dis]*w[j-dis+i+i];//<span style="font-family: Arial, Helvetica, sans-serif;">C、D的个数取决于A、B有多少对，所以用A、B个数来乘</span>  
            c[j-i]+=y*w[j];  
            d[j]+=y*w[j-i];  
        }  
    }  
    for(int i=1;i<=m;i++)//输出  
    {  
        printf("%d %d %d %d\n",a[h[i]],b[h[i]],c[h[i]],d[h[i]]);  
    }  
}  