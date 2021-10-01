
#include<bits/stdc++.h>
using namespace std;
int q[255];
char s[205];
char p[]={'W','I','N','G'};
int f[205][205][4],num[4];
char a[4][20][2];
bool dp(int l,int r,int k){
  if(l==r)return (s[l]==p[k]);
  int &res=f[l][r][k];
  if(res!=-1)return res;
  for(int i=1;i<=num[k];i++)
    for(int j=l;j<r;j++)
      if(dp(l,j,q[a[k][i][0]])&&dp(j+1,r,q[a[k][i][1]]))return res=1;
  return res=0;
}
 
int main(){
  memset(f,-1,sizeof(f));
  for(int i=0;i<4;i++)scanf("%d",&num[i]);
  q['W']=0;q['I']=1;q['N']=2;q['G']=3;
  for(int i=0;i<4;i++)
    for(int j=1;j<=num[i];j++)scanf("%s",a[i][j]);
 
  scanf("%s",s);
  int len=strlen(s);
  bool flag=1;
  for(int i=0;i<4;i++)
    if(dp(0,len-1,i))flag=0,printf("%c",p[i]);
  if(flag)puts("The name is wrong!");
  return 0;
}