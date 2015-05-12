//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-12 16:13
//
// Filename: cqueue.cpp
//
// Description: 
//
//=============================================================================
#include "cqueue.hpp"

int main(void) {
        CQueue<int> ciq;
        for(int i=0; i<10; i++)
                ciq.Insert( i*5-i%3 );
        ciq.Tranverse();
        cout<<"ciq.Delete(): "<<ciq.Delete()<<endl;
        ciq.Clear(); ciq.Tranverse();
        ciq.Insert(50); ciq.Insert(208); ciq.Insert(35);
        ciq.Tranverse(); ciq.Delete();
        cout<<"After ciq.Delete(), ciq.GetHead(): "<<ciq.GetHead()<<endl;
        ciq.Tranverse();
        cout<<"ciq.GetLength(): "<<ciq.GetLength()<<endl;
        CQueue<int> ct( ciq );
        cout<<"ct( ciq ) :"<<endl;
        ct.Tranverse();
        ct.Clear();
        cout<<"After ct.Clear(), ciq.Tranverse():"<<endl;
        ciq.Tranverse();
        ct = ciq;
        cout<<"ct.clear() and ct=ciq:"<<endl;
        ct.Tranverse();

        return 0;
}
