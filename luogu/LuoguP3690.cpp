#include <bits/stdc++.h>
#define ll long long
#define R register int
#define lc c[x][0]
#define rc c[x][1]
using namespace std;
const int MAXN = 3e5 + 9;
int N, M, val[MAXN];
struct Link_Cut_Tree {
    int top, c[MAXN][2], fa[MAXN], xr[MAXN], q[MAXN], rev[MAXN];
    void pushup( R x ) {
        xr[x] = xr[lc] ^ xr[rc] ^ val[x];
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
    /*void cut(R x,R y) {//xy深度相差一定是1 。当access(y),splay(y)以后，x 一定是y 的左儿子，直接双向断开连接
        split(x,y);
        if( c[y][0]==x )
            fa[x]=c[y][0]=0;
        pushup(y);
    }*/
    void cut( R x, R y ) {
        makeroot(x);
        if( find( y ) != x || fa[x] != y || c[x][1] )
            return;
        fa[x] = c[y][0] = 0;
        pushup( y );
    }
} T;
inline int read()
{
    int f = 1, x = 0;
    char ch;
    do {
        ch = getchar();
        if( ch == '-' )f = -1;
    } while( ch < '0' || ch > '9' );
    do {
        x = x * 10 + ch - '0';
        ch = getchar();
    } while( ch >= '0' && ch <= '9' );
    return f * x;
}
//main
int main()
{
    N = read();
    M = read();
    for( int i = 1; i <= N; i++ )val[i] = read(), T.xr[i] = val[i];
    while( M-- ) {
        int opt = read();
        if( opt == 0 ) {
            int x = read(), y = read();
            T.split( x, y );
            printf( "%d\n", T.xr[y] );
        }
        if( opt == 1 ) {
            int x = read(), y = read(), xx = T.find( x ), yy = T.find( y );
            if( xx != yy )T.link( x, y );
        }
        if( opt == 2 ) {
            int x = read(), y = read(), xx = T.find( x ), yy = T.find( y );
            if( xx == yy )T.cut( x, y );
        }
        if( opt == 3 ) {
            int x = read(), y = read();
            T.access( x );
            T.splay( x );
            val[x] = y;
            T.pushup( x );
        }
    }
    return 0;
}