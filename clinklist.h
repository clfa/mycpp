//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-06 16:00
//
// Filename: clinklist.h
//
// Description: 
//
//=============================================================================
#ifndef _CLINKLIST_H
#define _CLINKLIST_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*===========================================CLinkList===========================================*/
template<class Ty>
struct LNode {
        Ty data;
        struct LNode *next;
};

template<class Ty>
class CLinkList {
public:
        CLinkList() {
        }
        
        ~CLinkList() {
                LNode<Ty>* q;
                while( list ) {
                        q = list;
                        list = list->next;
                        delete q;
                }
                list = NULL;
        }
        
        bool Insert(int i, Ty e) { // insert e at i
                LNode<Ty>* q = list;
                int j = 0;
                while( q && j < i-1 ) {
                        q = q->next;
                        j++;
                }
                if( j>i-1 || !q ) return false;
                LNode<Ty>* elem = new LNode<Ty>;
                elem->next = q->next;
                q->next = elem;
                elem->data = e;
                length++;
                return true;
        }

        bool Delete(int i, Ty* e) { // get position i element and save into e and delete it
                LNode<Ty>* q = list;
                int j = 0;
                while( q->next && j<i-1 ) {
                        q = q->next;
                        j++;
                }
                if( j>i-1 || !q->next ) return false;
                LNode<Ty>* elem = q->next;
                q->next = elem->next;
                *e = elem->data;
                delete elem;
                length--;
                return true;
        }

        int Locate(Ty e) { // locate element e position of list
                LNode<Ty>* elem = list->next;
                int j = 0;
                while( elem && elem->data!=e ) {
                        elem = elem->next;
                        j++;
                }
                if( NULL==elem ) return 0; // can find element e in the list
                else return j;
        }

        void Show() {
                int iPutCnt = 0;
                int iPutTimes = 10;
                LNode<Ty>* q = list->next;
                while( q ) {
                        cout<<q->data<<"\t";
                        iPutCnt++;
                        if( iPutTimes == iPutCnt ) cout<<endl;
                        q = q->next;
                }
                cout<<endl;
        }

        int GetLength() {       // get list curren length
                return length;
        }

        void Init(Ty* v, int n) {
                p = v;
                length = n;
                list = new LNode<Ty>; // reverse create a link list which has a head node
                list->next = NULL;
                for(int i=length-1; i>=0; i--) {
                        LNode<Ty>* q = new LNode<Ty>; // create new node
                        q->data = *(p+i);       // insert new node value
                        q->next = list->next;   // insert node into list head
                        list->next = q;
                }
        }

private:
        Ty* p;
        int length;
        LNode<Ty>* list;
};

#endif /* _CLINKLIST_H */
