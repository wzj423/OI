#include <bits/stdc++.h>

using namespace std;
//data------------------------
int N;
//edge======================
struct edge {
    int ed,next;
}E[7000];
int head[770],Ecnt;
void addEdge(int st,int ed) {
    E[++Ecnt].ed=ed,E[Ecnt].next=head[st],head[st]=Ecnt;
}
//main=======================
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y),addEdge(y,x);
    }
    return 0;
}