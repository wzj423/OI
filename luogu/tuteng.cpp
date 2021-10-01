#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
char Map[2100][2100];
char Eg[8][8]={" /\\ ","/__\\"};
int N;
int main()
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            cout<<Eg[i][j];
        cout<<endl;
    }
    return 0;
}
