//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:33
//
// Filename:		cslinklist.h
//
// Description: 
//
//=============================================================================
#ifndef _CSLINKLIST_H
#define _CSLINKLIST_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<class numType>
class CSLinklist {
public:
        CSLinklist(int len);    // constuctor
        ~CSLinklist();          // destructor
        void Init(int n);       // initial function to create list
        void Insert(int i, numType e); // insert e at position i
        numType Delete(int i);         // delete item at position i
        numType GetItem(int i);        // get value of item i
        int Locate(numType e);         // get position of value e
        bool IsEmpty();                // test list empty
        bool IsFull();                 // test list full
        int GetLength();               // get list length
        void Clear();                  // clear list all elements
        void Show();                   // show all elements of list
private:
        struct slnode {
                numType data;
                int next;
        };

        slnode* list;           // data array
        int maxlen;             // link list maxlen
        int sl;                 // static link list head
        int av;                 // backup use link list head
};

template<class numType>
CSLinklist<numType>::CSLinklist(int len):maxlen(len) { // construct object and allocate memory
        list = new slnode[maxlen];
        sl = -1;                // list head
        for(int i=0; i<maxlen; i++)
                list[i].next = i+1;
        list[maxlen-1].next = -1; // list tail next point to -1
        av = 0;                 // backup list head
}


template<class numType>
CSLinklist<numType>::~CSLinklist() { // destructor, free memory
        delete [] list;
}


template<class numType>
void CSLinklist<numType>::Init(int n) { // initial objector, import input elements
        int value;
        if( n>maxlen ) throw "Invalid argument.";
        cout<<"Insert "<<n<<" elements' value: "<<endl;
        for(int i=1; i<=n; i++) {
                cin>>value;
                Insert(i, value);
        }
}

template<class numType>
void CSLinklist<numType>::Insert(int i, numType e) { // insert element at position i
        int j, k, t;
        if( av == -1 ) throw "Backup link list empty.";
        j = av;                 // get first  position of backup list
        av = list[av].next;
        if( -1==sl ) {          // insert element into empty list
                list[j].data = e;
                list[j].next = -1;
                sl = j;
        }
        else if( 1==i ) {       // insert position is 1
                list[j].data = e;
                list[j].next = sl;
                sl = j;
        }
        else {
                k = 0;
                t = sl;
                while( k<i-1 && t!=-1 ) {
                        k++;
                        if( k<i-1 ) t = list[t].next;
                }
                if( k!=i-1 ) throw "Invalid position.";
                list[j].data = e;
                list[j].next = list[t].next;
                list[t].next = j;
        }
}

template<class numType>
numType CSLinklist<numType>::Delete(int i) {
        int j, k, t;
        if( -1==sl ) {
                throw "Empty link list.";
        }
        else if( 1==i ) {
                j = sl;
                sl = list[sl].next;
                list[j].next = av;
                av = j;
                return list[j].data;
        }
        else {
                k = 0;
                t = sl;
                while( k<i-1 && t!=-1 ) {
                        k++;
                        if( k<i-1 ) t = list[t].next;
                }
                if( k!=i-1 ) throw "Invalid position.";
                j = list[t].next;
                list[t].next = list[j].next;
                list[j].next = av;
                av = j;
                return list[j].data;
        }
}

template<class numType>
void CSLinklist<numType>::Show() {
        if( -1==sl ) throw "Empty link list. Nothing to show.";
        int iId = sl;           // index to locate element
        int iPutTimes = 0;      // to count current line output times
        int iPutCnt = 10;       // set every line max output times
        if( iId!=-1 ) cout<<"List all elements are:"<<endl;
        while( iId != -1 ) {
                cout<<list[iId].data<<"\t";
                iPutTimes++;
                if( iPutCnt == iPutTimes ) {
                        iPutTimes = 0;
                        cout<<endl;
                }
                iId = list[iId].next;
        }
        cout<<endl<<"===================================="<<endl;
}

template<class numType>
numType CSLinklist<numType>::GetItem(int i) {
        if( -1==sl ) throw "Empty link list.";
        int iPos;               // work index
        int iCnt = 0;           // count elements value
        iPos = sl;
        while( iCnt<i-1 && iPos!=-1 ) {
                iCnt++;
                if( iCnt<i-1 ) iPos = list[iPos].next;
        }
        if( iCnt==i-1 ) return list[iCnt].data;
        else throw "Invalid position";
}
template<class numType>
int CSLinklist<numType>::Locate(numType e) {
        if( -1==sl ) return -1; // empty list, return -1
        int iPos = sl;          // work index
        int iCnt = 0;
        while( iPos!=-1 && e!=list[iPos].data) {
                iCnt++;
                iPos = list[iPos].next;
        }
        if( -1==iPos ) return 0;               // can not find e on list
        else return iCnt+1; // find e on the list, and return its position
}

template<class numType>
bool CSLinklist<numType>::IsEmpty() { // test list whether it is empty
        if( -1==sl ) return true;
        else return false;
}

template<class numType>
bool CSLinklist<numType>::IsFull() { // test list whether it is full
        if( -1==av ) return true;
        else return false;
}

template<class numType>
int CSLinklist<numType>::GetLength() { // get list length
        int length=0;                  // to save list length value
        int iPos = sl;                 // work index
        while( -1!=iPos ) {
                length++;
                iPos = list[iPos].next;
        }
        return length;
}

template<class numType>
void CSLinklist<numType>::Clear() {
        for( int i=0; i<maxlen; i++) {
                if( i==maxlen-1 ) list[i].next = -1;
                list[i].next = i+1;
        }
        sl = -1;
        av = 0;
}

#endif /* _CSLINKLIST_H */
