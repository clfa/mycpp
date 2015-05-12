//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-12 16:11
//
// Filename: cqueue.hpp
//
// Description: 
//
//=============================================================================
#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <class numType>
struct QNode {
        numType data;
        QNode<numType>* next;
};

template <class numType>
struct LinkQueue {
        QNode<numType>* front; /* queue head pointer */
        QNode<numType>* rear;  /* queue tail pointer */
};

template <class numType>
class CQueue {
public:
        CQueue() {              /* create empty queue */
                linkq.front = linkq.rear = new QNode<numType>; /* point to head node */
                if( !linkq.front ) throw "The constructor failed to allocate memory.";
                linkq.front->next = NULL;
                linkq.rear->next = NULL;
        }

        ~CQueue() {             /* destroy queue */
                while( linkq.front ) {
                        linkq.rear = linkq.front->next;
                        delete linkq.front;
                        linkq.front = linkq.rear;
                }
        }

        CQueue( const CQueue& p ) { /*  copy constructor */
                linkq.front = linkq.rear = new QNode<numType>;
                if( !linkq.front ) throw "The constructor failed to allocate memory.";
                linkq.front->next = NULL; linkq.rear->next = NULL;
                QNode<numType>* q = p.linkq.front->next;
                while( q ) {
                        QNode<numType>* t = new QNode<numType>;
                        t->data = q->data;
                        t->next = linkq.rear->next;
                        linkq.rear->next = t;
                        linkq.rear = t;
                        q = q->next;
                }
        }

        CQueue& operator=( const CQueue& p ) { /* operator = function */
                Clear();
                QNode<numType>* q = p.linkq.front->next;
                while( q ) {
                        QNode<numType>* t = new QNode<numType>;
                        t->data = q->data;
                        t->next = linkq.rear->next;
                        linkq.rear->next = t;
                        linkq.rear = t;
                        q = q->next;
                }
                return *this;
        }
                        
        void Clear() {          /* delete queue's all items */
                while( linkq.front->next ) {
                        linkq.rear = linkq.front->next->next;
                        delete linkq.front->next;
                        linkq.front->next = linkq.rear;
                }
                linkq.rear = linkq.front;
                linkq.rear->next = NULL;
        }

        int GetLength() {       /* get queue's items number */
                QNode<numType>* p = linkq.front->next;
                int iLen = 0;
                while( p ) {
                        iLen++;
                        p = p->next;
                }
                return iLen;
        }

        bool IsEmpty() {        /* distiguish whether queue is empty */
                if( linkq.front == linkq.rear ) return true;
                else return false;
        }

        numType GetHead() {     /* get queue's head item value */
                if( linkq.front->next ) return linkq.front->next->data;
                else throw "Empty head.";
        }

        void Insert(numType e) {    /* insert item into queue */
                QNode<numType>* p = new QNode<numType>;
                if( !p ) throw "Insert failed.";
                p->data = e; p->next = linkq.rear->next;
                linkq.rear->next = p;
                linkq.rear = p;
                if( !linkq.front->next) linkq.front->next = p;
        }

        numType Delete() {          /* delete first item from queue */
                if( linkq.front == linkq.rear ) 
                        throw "The empty queue without deleting items.";
                QNode<numType>* p = linkq.front->next;
                numType e = p->data;
                linkq.front->next = p->next;
                if( linkq.rear == p ) linkq.rear = linkq.front;
                delete p;
                return e;
        }

        void Tranverse() {          /* list queue's all items */
                if( IsEmpty() ) {
                        cout<<"Empty queue has no one item to show."<<endl;
                        return;
                }
                QNode<numType>* p = linkq.front->next;
                int iCnt = 0;
                while( p ) {
                        cout<<p->data<<"\t";
                        iCnt++;
                        if( 0==iCnt%10 ) cout<<endl;
                        p = p->next;
                }
                cout<<endl;
        }

public:
        LinkQueue<numType> linkq;
};

#endif
