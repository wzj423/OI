#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define maxn 50015
int n,k,A[maxn],ans[maxn];
void Init()
{
  scanf("%d%d",&n,&k);
  for(int i=1;i<=n;i++)scanf("%d",&A[i]);
  sort(A+1,A+1+n);
  return;
}
void work()
{
  int Ans=0,j=1;
  for(int i=1;i<=n;i++)
  {
    while(A[j]-A[i]<=k && j<=n)j++;
    ans[i]=j-i;
  }
  for(int i=n;i>=1;i--)
  {
    Ans=max(Ans,ans[i]+ans[i+ans[i]]);
    ans[i]=max(ans[i],ans[i+1]);
  }
  printf("%d\n",Ans);
  return;
}
int main()
{
  //freopen("in.txt","r",stdin);
  Init();
  work();
  return 0;
}

