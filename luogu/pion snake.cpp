#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for (int i=a;i<=b;i++)
#define Rep(i,a,b) for (int i=b;i>=a;i--)
using namespace std;

inline int rd(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){ if (ch=='-') f=-1;ch=getchar(); }
    while (ch>='0'&&ch<='9'){ x=x*10+ch-'0';ch=getchar(); }
    return x*f;
}
int _x[300],_y[300];
int a[500][500];
bool vis[500][500];
int N,M,K,C;
struct pos{
    int x,y;
    pos(int a=0,int b=0) {x=a,y=b;}
    bool operator <(const pos& o) const {
        if(o.x!=x) return x<o.x;
        return y<o.y;
    }
    int& var() {
        return a[x][y];
    }
    void set(int vv) {
        a[x][y]=vv;
    }
}; 
struct _snake{
    pos bo[80010];
    char seq[80010];
    int hh,tt,id;
    bool dead;
    bool operator <(const _snake& o) const {
        return bo[hh]<o.bo[hh];
    }
    int len() {
        return hh-tt;
    }
    void death() {
        dead=true;
        for(int i=tt+1;i<=hh;++i) bo[i].set('&');
        hh=tt=0;
    }
    void move(char ch) {
        if(dead) return;
        //printf("start moving!\n");
        pos ano(bo[hh].x+_x[ch],bo[hh].y+_y[ch]);
        if(ano.var()=='.') {
            bo[hh].set('#');
            ++tt;
            bo[tt].set('.');
            ano.set('@');

            bo[++hh]=ano;
        } else if(ano.var()=='&') {
            ano.set('@');
            bo[hh].set('#');
            bo[++hh]=ano;	
        } else if(ano.var()=='#'||ano.var()=='@'||ano.var()==0) {
            death();
        }
    }
    void dfs(int x,int y,bool top=false) {
        //printf("in (%d,%d)\n",x,y);
        //system("pause");
        pos now(x,y);
        if(x==0||x>N||y==0||y>M) return;
        if(vis[x][y]) return;
        if(top&&now.var()!='@') return;
        if((!top)&&now.var()!='#') return;
        vis[x][y]=1;
        dfs(x+1,y);
        dfs(x-1,y);
        dfs(x,y+1);
        dfs(x,y-1);
        bo[++hh]=now;
        //printf("(%d,%d)\n",x,y);
        //if(top) puts("HEad!");
    }
    void build(int x,int y,int index) {
        dfs(x,y,1);
        id=index;
    }
}S[30];
void disp() {
    puts("***********************************");
    for(int i=1;i<=N;++i,puts("")) {
        for(int j=1;j<=M;++j) {
            printf("%c ",char(a[i][j]));
        }
    }	
}
int Scnt;
int main(){
    _x['W']=-1,_x['S']=1,_x['A']=_x['D']=0;
    _y['A']=-1,_y['D']=1,_y['W']=_y['S']=0;
    N=rd(),M=rd(),K=rd();
    for(int i=1;i<=N;++i) 
        for(int j=1;j<=M;++j) {
        char ch[3];
        scanf("%1s",ch);
        a[i][j]=ch[0];
    }

    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
            if(a[i][j]=='@') {
                ++Scnt;
                S[Scnt].build(i,j,Scnt);
                //printf("Snake %d (%d,%d)len=%d\n",Scnt,i,j,S[Scnt].len());
            }
        }
    }
    C=Scnt;
    for(int i=1;i<=C;++i) scanf("%s",S[i].seq+1);
    //printf("K=%d C=%d\n",K,C);
    for(int i=1;i<=K;++i) {
        for(int j=1;j<=C;++j) {
            //printf("(%d,%d)\n",j,i);
            S[j].move(S[j].seq[i]);
        }
        //disp();
    }
    int ans=0;
    for(int i=1;i<=C;++i) printf("%d %d\n",S[i].len(),i);
    for(int i=1;i<=N;++i) for(int j=1;j<=M;++j) if(a[i][j]=='&') ++ans;
    printf("%d\n",ans);
    return 0;
}

