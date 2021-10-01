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
const int maxn=5e5+10;
struct node{
    int l,r,sum;
}T[maxn<<6];
int Tcnt;
int Root[maxn],a[maxn];
int N,M;