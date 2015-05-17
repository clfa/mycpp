/*=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-18 06:33
//
// Filename: dahua.cpp
//
// Description: 
//
=============================================================================*/
#include <iostream>
using namespace std;

int sec_max( int a[], int n );

bool is_incremental( int a[], int n );

long jcsum( );

const int MAX = 8;
struct DivNode {
        int id[MAX];
        int min;
};

class DivManage {
private:
        DivNode dn;
public:
        DivManage() {
                for( int i=0; i<MAX; i++ )
                        dn.id[i] = -1;
                dn.min = 0;
        }

        int Add() {
                if( dn.min < 0 )
                        throw "full";
                int id = dn.min;
                dn.id[dn.min] = 0;
                dn.min = -1;
                
                for( int i=0; i<MAX; i++ ) {
                        if( dn.id[i]<0 ) {
                                dn.min = i;
                                break;
                        }
                        else continue;
                }
                return id+1;
        }

        void Delete( int n ) {
                if( n>MAX || n<0 )
                        throw "error index";
                dn.id[n-1] = -1;
                dn.min = n-1;
                for( int i=0; i<MAX; i++ ) {
                        if( dn.id[i]<0 && i<dn.min )
                                dn.min = i;
                }
        }
};

int main(void) {
        int iA[] = { -1, 0, 2, -3, 5, 1, 8 };
        cout<<"iA second max element: "<<sec_max( iA, sizeof(iA)/sizeof(iA[0]))<<endl;
        int iB[] = { 0, 1, 2, 3, 4, 5 };
        cout<<"iA is increasing array? "<<is_incremental( iA, sizeof(iA)/sizeof(iA[0]) )<<endl;
        cout<<"iB is increasing array? "<<is_incremental( iB, sizeof(iB)/sizeof(iB[0]) )<<endl;
        cout<<"1!+2!+3!+...+10! = "<<jcsum()<<endl;
        DivManage dm;
        for( int i=0; i<MAX; i++ ) {
                int id = dm.Add();
                cout<<id<<endl;
        }
        dm.Delete( 3 ); dm.Delete( 5 );
        int id = dm.Add();
        cout<<id<<endl;
        id = dm.Add();
        cout<<id<<endl;
        dm.Delete( 2 );
        id = dm.Add();
        cout<<id<<endl;
        return 0;
}

int sec_max( int a[], int n ) {
        if( n<1 ) return -1;
        int iMf = a[0];
        int iMs = a[0];
        for( int i=1; i<n; i++ ) {
                if( a[i] > iMf ) {
                        iMs = iMf;
                        iMf = a[i];
                }
                else if( a[i] > iMs ) iMs = a[i];
        }
        return iMs;
}

bool is_incremental( int a[], int n ) {
        if( n<2 ) return true;
        if( *(a+1) > *a )
                is_incremental( a+1, n-1 );
        else
                return false;
}

long jc( int n ) {
        int i = n;
        long l = 1;
        while( i>1 ) {
                l *= i;
                i--;
        }
        return l;
}

long jcsum( ) {
        long ls = 0;
        for( int i=1; i<=10; i++ )
                ls += jc(i);
        return ls;
}





















