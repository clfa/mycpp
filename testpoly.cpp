//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:35
//
// Filename:		testpoly.cpp
//
// Description: 
//
//=============================================================================
#include "Poly.hpp"

int main(void) {
        Poly LA, LB, LC;
        PolyArray a = { {7.0, 0}, {3.0, -1}, {9.0, 6}, {15.8, 3}, {-1.9, 2} };
        PolyArray b = { {-3.2, -3}, {7.5, 4}, {10.8, 10}, {12.08, 2}, {3.33, 7} };
        PolyArray c = { {3.8, -2}, {7.2, -5}, {-1.5, 3}, {6.2, 4} };
        LA.Create( a, 5 );
        LB.Create( b, 5 );

        cout<<"原多项式A为： "<<endl;
        LA.Display();
        cout<<"原多项式B为： "<<endl;
        LB.Display();

        LA.Sort();
        LB.Sort();
        cout<<"有序多项式A为： "<<endl;
        LA.Display();
        cout<<"有序多项式B为： "<<endl;
        LB.Display();

        PolyNode e1 = { 19.24, 5, NULL, NULL };
        PolyNode e2 = { -7.8, 9, NULL, NULL };
        PolyNode e3 = { 5.0, 2, NULL, NULL };

        LA.PolyNodeAdd( e1 );
        cout<<"多项式A加上e1( "<<e1.coef<<", "<<e1.exp<<" )后为： "<<endl;
        LA.Display();
        LA.PolyNodeSubstract( e2 );

        cout<<"多项式A减去e2( "<<e2.coef<<", "<<e2.exp<<" )后为： "<<endl;
        LA.Display();

        LA.Add( LB );
        cout<<"LA+LB之后："<<endl;
        cout<<"多项式A为： "<<endl;
        LA.Display();
        // cout<<"多项式B为： "<<endl;
        // LB.Display();

        LC.Create( c, 4 );
        LC.Sort();
        cout<<"多项式C为： "<<endl;
        LC.Display();
        cout<<"多项式C乘以e1后结果为："<<endl;
        LC.PolyNodeMultiply( e1);
        LC.Display();
        //LC.Clear();
        LA.Multiply( LC );
        cout<<"LA*LC之后:"<<endl;
        cout<<"多项式A为： "<<endl;
        LA.Display();
        // cout<<"多项式C为： "<<endl;
        // LC.Display();
        cout<<"多项式A乘以e3结果为："<<endl;
        LA.PolyNodeMultiply( e3 );
        LA.Display();

        Poly LD = LA;
        cout<<"将LA赋值给LD："<<endl;
        LD.Display();
        cout<<"清除LD内容"<<endl;
        LD.Clear();
        cout<<"LA内容为："<<endl;
        LA.Display();
        
        return 0;
}
