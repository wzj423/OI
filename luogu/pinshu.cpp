#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool cp(string a,string b)
{
    return a+b<b+a;
}
string shuru[22];
int main()
{
    int n,k;
    cin>>n;
    k=n;
    while(n--)
        cin>>shuru[n];
    sort(shuru,shuru+k,cp);
    while(k--)
        cout<<shuru[k];
    return 0;
}
