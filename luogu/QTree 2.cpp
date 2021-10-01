#include <bits/stdc++.h>
#define ll long long
#define R register int
#define lc c[x][0]
#define rc c[x][1]
using namespace std;
const int MAXN = 3e5 + 9;
int N, M;
struct LineCutTree {
    int c[MAXN][2], fa[MAXN], sz[MAXN], rev[MAXN];
    int top,q[MAXN];
    void pushup( R x ) {
        sz[x] = sz[lc] + 1 + sz[rc];
    }
     void pushdown( R x ) {
        if( rev[x] ) {
            rev[lc] ^= 1, rev[rc] ^= 1, rev[x] ^= 1;
            swap( lc, rc );
        }
    }
    bool isroot( R x ) {
        return c[ fa[x] ][0] != x && c[ fa[x] ][1] != x;
    }
    void rotate( R x ) {
        int y = fa[x], z = fa[y], l = c[y][1] == x, r = l ^ 1;
        if( !isroot( y ) ) {
            c[z][ c[z][1] == y ] = x;
        }
        fa[x] = z, fa[y] = x;

        fa[ c[x][r] ] = y;
        c[y][l] = c[x][r];

        c[x][r] = y;
        pushup( y ), pushup( x );
    }
    void splay( R x ) {
        top = 1;
        q[top] = x;
        for( int i = x; !isroot( i ); i = fa[i] ) q[++top] = fa[i];
        for( int i = top; i; --i )            pushdown( q[i] );
        while( !isroot( x ) ) {
            int y = fa[x], z = fa[y];
            if( !isroot( y ) ) {
                if( ( c[y][1] == x ) == ( c[z][1] == y ) ) rotate( y );
                else                               rotate( x );
            }
            rotate( x );
        }
    }
    void access( R x ) {
        for( int t = 0; x; t = x, x = fa[x] ) splay( x ), c[x][1] = t, pushup( x );
    }
    void makeroot( R x ) {
        access( x );
        splay( x );
        rev[x] ^= 1;
    }
    int find( R x ) { //找到根节点
        access( x );
        splay( x );
        while( lc ) x = lc;
        return x;
    }
    void link( R x, R y ) {
        makeroot( x );
        fa[x] = y;
    }
    void split( int x, int y ) {
        makeroot( x );
        access( y );
        splay( y );
    }
    void cut( R x, R y ) {
        makeroot(x);
        if( find( y ) != x || fa[x] != y || c[x][1] )
            return;
        fa[x] = c[y][0] = 0;
        pushup( y );
    }
} T;
//other data ================================================
int to[MAXN];
//main=======================================================
int main()
{
    freopen("C:\\Users\\Mike-Wu\\Downloads\\testdata (1).in","r",stdin);
    freopen("1.out","w+",stdout);
    scanf( "%d", &N );
    for( int i = 1; i <= N; ++i )   T.sz[i] = 1;
    for( int i = 1; i <= N; ++i ) {
        int x;
        scanf( "%d", &x );
        if( i + x <= N )
            T.fa[i]=i+x,to[i]=i+x;//,printf("link %d ->%d\n",i,i+x);
    }
    scanf("%d",&M);
    for( int i = 1; i <= M; ++i ) {
        int opt,j,k;
        scanf( "%d", &opt );
        if( opt == 1 ) {
            scanf("%d",&j);
            ++j;
            T.access(j);
            T.splay(j);
            printf("%d\n",T.sz[j]);
        } else {
            scanf("%d%d",&j,&k);
            ++j;
            if(to[j]) {
                T.cut(j,to[j]);
                if(j+k<=N) {
                    to[j]=j+k;
                    T.link(j,j+k);
                    //T.fa[j]=to[j];
                }               
            }

        }
    }
    return 0;
}