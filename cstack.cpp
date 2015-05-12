//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-12 15:20
//
// Filename: cstack.cpp
//
// Description: 
//
//=============================================================================
#include "cstack.hpp"
#include <string>
using std::string;

string Conversion(int, int=8);

void Move(char x, int n, char z);

void Hanoi(int n, char x, char y, char z);

static int c = 0;

int main(void) {
        int iNum = 2196;
        int iD = 16;
        int iLen = 10;
        cout<<iNum<<"的"<<iD<<"进制数为： "<<Conversion(iNum, iD)<<endl;
        CStack<float> cfs;
        for(int i=0; i<iLen; i++)
                cfs.Push(i*3.02+2.08);
        cfs.Display();

        cout<<"=====================Hanoi move game======================"<<endl;
        Hanoi(5, 'x', 'y', 'z');

        CStack<float> cft( cfs );
        cout<<"复制构造："<<endl;
        cft.Display();
        cft.Clear();
        cft.Push( 3.9 );
        cft.Display();
        cfs.Display();
        cout<<"赋值运算符："<<endl;
        CStack<float> cfb = cfs;
        cfb.Display();
        cout<<"cfb pop: "<<cfb.Pop()<<endl;
        cfb.Display();
        cfb = cfs;
        cfb.Display();

        return 0;
}

/* 利用栈求解数制转换问题，这里求解10进制数p的d进制数。*/
string Conversion(int p, int d) {
        CStack<int> csiMem;
        int iN = p;
        while( iN ) {
                csiMem.Push( iN % d);
                iN /= d;
        }
        string sRes;
        while( !csiMem.IsEmpty() ) {
                int iCur = csiMem.Pop();
                char c = ' ';
                if( iCur >= 10)
                        c = 'A'+iCur-10;
                if( c == ' ') {
                        char cNum[5] = "";
                        sprintf( cNum, "%d", iCur );
                        sRes += cNum;
                }
                else sRes += c;
        }
        return sRes;
}

void Move(char x, int n, char z) {
        cout<<++c<<". Move disk "<<n<<" from "<<x<<" to "<<z<<endl;
}

void Hanoi(int n, char x, char y, char z) {
        if( n==1 ) Move(x, 1, z);
        else {
                Hanoi(n-1, x, z, y);
                Move(x, n, z);
                Hanoi(n-1, y, x, z);
        }
}
