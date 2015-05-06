//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-06 15:53
//
// Filename: cclinklist.h
//
// Description: 
//
//=============================================================================
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template<class Numtype>
struct Node {
        Numtype data;
        Node* next;
};

template<class Numtype>
class CCLinklist {
public:
        CCLinklist();
        ~CCLinklist();
        void Create(int n);     // create circle link list
        void Insert(int i, Numtype e); // insert element at position i
        Numtype Delete(int i);         // delete element at position i
        Numtype GetElem(int i);        // get value of element of position i
        int Locate(Numtype e);         // locate element position of e
        Numtype Prior(Numtype e);      // return the prior element value of element e
        bool IsEmpty();                // test list whether it is empty
        int GetLength();               // test list length
        void Display();                // display list all elements' value
private:
        Node<Numtype>* Head;    // define list head
};

template<class Numtype>
CCLinklist<Numtype>::CCLinklist() {
        Head = new Node<Numtype>;
        Head->next = Head;
}

template<class Numtype>
CCLinklist<Numtype>::~CCLinklist() {
        Node<Numtype>* tail;
        tail = Head;
        while( tail->next != Head ) tail = tail->next; // to get tail element
        Node<Numtype>* delID;                   // delete list from head
        while( Head != Head->next ) {
                delID = Head;
                Head = Head->next;
                tail->next = Head;
                delete delID;
        }
        if( Head ) delete Head;
        Head = NULL;            // head node point to null
}

template<class Numtype>
void CCLinklist<Numtype>::Create(int n) {
        Node<Numtype>* wkID;    // work index
        Node<Numtype>* tail;    // tail node
        cout<<"Please input "<<n<<" elements:"<<endl;
        tail = Head;
        for( int i=1; i<=n; i++) { // input every element from tail of list
                wkID = new Node<Numtype>;
                cin>>wkID->data;
                wkID->next = tail->next; // new node insert into list tail
                tail->next = wkID;
                tail = wkID;
        }
}

template<class Numtype>
void CCLinklist<Numtype>::Insert(int i, Numtype e) { // insert element at position i of list
        Node<Numtype>* wkID;
        int iCnt = 0;
        wkID = Head;
        while( iCnt<i-1 && Head!=wkID->next ) {
                iCnt++;
                wkID = wkID->next;
        }
        if( wkID->next==Head || iCnt>i-1 ) throw "Invalid position.";
        else {
                Node<Numtype>* ele = new Node<Numtype>;
                ele->data = e;
                ele->next = wkID->next;
                wkID->next = ele;
        }
}

template<class Numtype>
Numtype CCLinklist<Numtype>::Delete(int i) {         // delete element of position i
        Node<Numtype>* wkID;
        int j=0;
        wkID = Head;
        Numtype ntData;
        while( wkID->next != Head && j<i-1 ) {
                j++;
                wkID = wkID->next;
        }
        if( wkID->next==Head || j>i-1 ) throw "Invalid position.";
        else {
                Node<Numtype>* elem = wkID->next;
                wkID->next = elem->next;
                ntData = elem->data;
                delete elem;
                return ntData;
        }
}

template<class Numtype>        
Numtype CCLinklist<Numtype>::GetElem(int i) {        // get element of position i
        Node<Numtype>* wkID;
        int j=0;
        wkID = Head;
        while( wkID->next != Head && j<i-1 ) {
                j++;
                wkID = wkID->next;
        }
        if( wkID->next==Head || j>i-1 ) throw "Invalid position.";
        else {
                return wkID->next->data;
        }
}

template<class Numtype>        
int CCLinklist<Numtype>::Locate(Numtype e) {         // get position of e
        Node<Numtype>* wkID = Head->next;
        int iPos = 1;
        while( Head!=wkID && wkID->data!=e) {
                wkID = wkID->next;
                iPos++;
        }
        if( wkID==Head ) return 0;
        else return iPos;
}

template<class Numtype>        
Numtype CCLinklist<Numtype>::Prior(Numtype e) {      // get prior element of e
        Node<Numtype>* wkID = Head->next;
        Node<Numtype>* pri;
        while( Head!=wkID && wkID->data!=e ) {
                pri = wkID;
                wkID = wkID->next;
        }
        if( wkID==Head ) return (Numtype)0;
        return pri->data;        
}

template<class Numtype>        
bool CCLinklist<Numtype>::IsEmpty() {
        if( Head == Head->next ) return true;
        else return false;
}

template<class Numtype>        
int CCLinklist<Numtype>::GetLength() {
        Node<Numtype>* wkID = Head->next;
        int len = 0;
        while( Head != wkID ) {
                wkID = wkID->next;
                len++;
        }
        return len;
}

template<class Numtype>        
void CCLinklist<Numtype>::Display() {
        Node<Numtype>* wkID = Head->next;
        int iPutTimes = 0;
        int iPutMaxN = 10;
        while( Head!= wkID ) {
                cout<<wkID->data<<"\t";
                wkID = wkID->next;
                iPutTimes++;
                if( iPutMaxN==iPutTimes ) {
                        iPutTimes = 0;
                        cout<<endl;
                }
        }
        cout<<endl;
}













