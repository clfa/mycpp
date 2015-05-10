#ifndef _CSTACK_H_
#define _CSTACK_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

template <class numType>
struct stacknode {
    numType *base;
    numType *top;
    int size;
};

template <class numType>
class CStack {
public:
    CStack() {
        elem.base = (numType *) malloc( INIT_SIZE * sizeof(numType) );
        if( !elem.base ) throw "Allocate failed.";
        elem.top = elem.base;
        elem.size = INIT_SIZE;
    }

    ~CStack() {
        free( elem.base );
        elem.base = NULL;
        elem.top = NULL;
        elem.size = 0;
    }

    void Clear() {
        if( elem.top ) {
            while( elem.top != elem.base ) {
                *(elem.top) = (numType) 0;
                elem.top -= 1;
            }
        }
    }

    bool IsEmpty() {
        if( elem.top == elem.base ) return true;
        else return false;
    }

    int Length() {
        if( IsEmpty() ) return 0;
        numType* p = elem.top;
        int iLen = 0;
        while( p != elem.base ) {
            iLen++;
            p = p - 1;
        }
        return iLen;
    }

    numType GetTop() {
        if( elem.top == elem.base ) throw "Empty stack.";
        return *(elem.top - 1);
    }

    void Push( numType e ) {
        if( elem.top >= elem.base+elem.size ) {
            elem.base = (numType *) realloc(elem.base, (elem.size+INCREMENT)*sizeof(numType));
            if( !elem.base ) throw "Reallocate failed.";
            elem.top = elem.base + elem.size;
            elem.size += INCREMENT;
        }
        *elem.top = e;
        elem.top += 1;
    }

    numType Pop() {
        if( elem.top != elem.base ) {
            numType e = *(elem.top-1);
            elem.top -= 1;
            return e;
        }
        else throw "Empty stack.";
    }

    void Display() {
        if( IsEmpty() )
            cout<<"Empty stack."<<endl;
        numType* e = elem.top;
        int iCnt = 0;
        while( e != elem.base ) {
            cout<<*(e-1)<<"\t";
            iCnt++;
            if( 0 == iCnt%10 ) cout<<endl;
            e -= 1;
        }
        cout<<endl;
    }
private:
    stacknode<numType> elem;
    static const int INIT_SIZE = 10; //initial size 
    static const int INCREMENT = 10;  //increment size
};

#endif
