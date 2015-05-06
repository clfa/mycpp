//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-06 15:54
//
// Filename: clinearlist.h
//
// Description: 
//
//=============================================================================
#ifndef _CLINEARLIST_H
#define _CLINEARLIST_H

#include <stdlib.h>             // malloc define head file
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<class numType>
struct List {        // define list type
        numType* elem;          // storage memory address
        int length;              // current list length
        int size;                // current list storage size
};

const int LIST_INIT_SIZE = 100;  // List init size
const int LISTINCREMENT = 10;    // List default increment

template<class numType>
class CLineList {
public:
        CLineList() {
                Init();
        }

        ~CLineList() {
                Destroy();
        }

private:
        void Init() {           // do initial work
                L.elem = (numType*) malloc(LIST_INIT_SIZE * sizeof(numType));
                if( !L.elem ) cout<<"Allocate overflow!"<<endl;
                else {
                        L.length = 0;
                        L.size = LIST_INIT_SIZE;
                }
        }

        void Destroy() {        // destructor
                if( L.elem )
                        free(L.elem);
                L.length = L.size = 0;
        }

public:
        bool Insert(int i, numType e) { // insert e at i
                if( i<1 || i>L.length+1 ) // error insert position
                        return false;
                if( L.length >= L.size ) { // check list size
                        numType* p = (numType*) realloc( L.elem, (L.size+LISTINCREMENT)*sizeof(numType) );
                        if( !p ) return false;
                        L.elem = p;
                        L.size += LISTINCREMENT;
                }
                numType* q = &L.elem[i-1]; // insert position, backup data
                for(numType* p=&L.elem[L.length-1]; p>=q; --p)
                        *(p+1) = *p;
                *q = e;         // insert e
                ++L.length;    // list length add 1
                return true;
        }

        bool Delete(int i, numType* e) { // get element
                                         // value of
                                         // position i and
                                         // save into e and
                                         // delete element
                if( !GetLength() ) {
                        cout<<"Empty list has no elements to delete."<<endl;
                        return false;
                }
                if( i<1 || i>L.length )  // distiguish position i reality
                        return false;
                numType* p = &L.elem[i-1];
                *e = *p;
                numType* q = L.elem+L.length-1;
                for(++p; p<=q; ++p)
                        *(p-1) = *p;
                --L.length;
                return true;
        }

        bool Compare(numType a, numType b) { // compare two elements
                if( a==b ) return true;
                else return false;
        }

        int Locate(numType e) { // locate element e position of list
                if( !GetLength() ) {
                        cout<<"Empty list has no elements to locate."<<endl;
                        return -1;
                }
                int i = 0;
                numType* p = L.elem;
                for( ; i<L.length; i++ )
                        if( Compare( *(p+i), e ) ) break;
                if( i<L.length ) return i+1; // get e position and return
                else return 0;                // otherwise return 0, means failed to
                                              // find e
        }

        void Show() {
                if( !L.length ) cout<<"List has no one element to show."<<endl;
                else {
                        cout<<"All the contents of the list are as follows."<<endl;
                        int iPutNum = 0;
                        const int iPutCnt = 10;
                        int i = 0;
                        for(; i<L.length; i++) {
                                iPutNum++;
                                if( 1==iPutNum ) cout<<"( ";
                                cout<<L.elem[i];
                                if( iPutNum<iPutCnt && i!=L.length-1 )
                                        cout<<"\t";
                                if( 0!=L.length%iPutCnt && i==L.length-1 ) cout<<" )";
                                if( iPutNum==iPutCnt ) {
                                        iPutNum=0;
                                        cout<<" )"<<endl;
                                }
                        }
                        cout<<endl;
                }
        }

        int GetLength() {
                return L.length;
        }

        int GetSize() {
                return L.size;
        }

        void Merger() ;

private:

        List<numType> L;
};


#endif  // _CLINEARLIST_H
