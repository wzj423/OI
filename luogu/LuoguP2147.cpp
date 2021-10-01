#include <bits/stdc++.h>

using namespace std;
//def========================================
#define MAXN 30010
#define lc c[x][0]
#define rc c[x][1]
#define I int
//var=======================================
I N, M;
char opt[30];
//lct========================================
struct LinkCutTree {
    int q[MAXN], qcnt;
    int rev[MAXN], c[MAXN][2], fa[MAXN];
    void pushup( I x ) {

    }
    void pushdown( I x ) {
        if( rev[x] ) {
            rev[lc] ^= 1, rev[rc] ^= 1, rev[x] ^= 1;
            swap( lc, rc );
        }
    }
    bool isroot( I x ) {
        return c[ fa[x] ][0] != x && c[ fa[x] ][1] != x;
    }
    void rotate( I x ) {
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
    void splay( I x ) {
        qcnt = 1;
        q[qcnt] = x;
        for( int i = x; !isroot( i ); i = fa[i] ) q[++qcnt] = fa[i];
        for( int i = qcnt; i; --i )   pushdown( q[i] );
        while( !isroot( x ) ) {
            int y = fa[x], z = fa[y];
            if( !isroot( y ) ) {
                if( ( c[y][1] == x ) == ( c[z][1] == y ) ) rotate( y );
                else rotate( x );
            }
            rotate( x );
        }
    }
    void access( I x ) {
        for( int t = 0; x; t = x, x = fa[x] ) splay( x ), c[x][1] = t, pushup( x );
    }
    void makeroot( I x ) {
        access( x );
        splay( x );
        rev[x] ^= 1;
    }
    int findroot( I x ) {
        access( x );
        splay( x );
        while( lc )   x = lc;
        return x;
    }
    void link( I x, I y ) {
        makeroot( x );
        fa[x] = y;
    }
    void split( I x, I y ) {
        makeroot( x );
        access( y );
        splay( y );
    }
    void cut( I x, I y ) {
        makeroot( x );
        if( findroot( y ) != x || fa[x] != y || c[x][1] ) return;
        fa[x] = c[y][0] = 0;
        pushup( y );
    }
} T;
//main=======================================
int main()
{
    scanf( "%d%d", &N, &M );
    while( M-- ) {
        int x, y;
        scanf( "%s", opt );
        scanf( "%d%d", &x, &y );
        if( opt[0] == 'Q' ) {
            if( T.findroot( x ) == T.findroot( y ) )    puts( "Yes" );
            else    puts( "No" );
        } else if( opt[0] == 'C' ) {
            T.link( x, y );
        } else {
            T.cut( x, y );
        }
    }
    return 0;
}