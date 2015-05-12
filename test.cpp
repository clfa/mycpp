//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:35
//
// Filename:		test.cpp
//
// Description: 
//
//=============================================================================
#include "clinearlist.h"
#include "clinklist.h"
#include "cslinklist.h"
#include "cclinklist.h"

#define _TEST_CLINELIST_	0
#define _TEST_CLINKLIST_	0
#define _TEST_CSLINKLIST_   0
#define _TEST_CCLINKLIST_	0

typedef int ElemType ;           // Define elemtype

void  Help() {                  // to show help message
        cout<<"=========================================================="<<endl
            <<"Usage info : "<<endl
            <<"		c : compare two element"<<endl
            <<"		d : delete element from list"<<endl
            <<"		h : show this help infomation"<<endl
            <<"		i : insert element to list"<<endl
            <<"		l : locate element position"<<endl
            <<"		q : quit the program"<<endl
            <<"		s : show list elements"<<endl
            <<"=========================================================="<<endl;
}

int main(void) {

#if _TEST_CLINELIST_

        CLineList<ElemType> cl;  // create a list object
        char c;        // to get char from user input screen
        ElemType a, b, e;
        int iPos;
        Help();
        cout<<"Please input your choice: ";
        try {
                cin>>c;
                if( !cin ) throw;
        }
        catch(...) {
                cout<<"Ilegal input. Program exit."<<endl;
                return 1;
        }
        cout<<endl;
        while( c != 'q' ) {
                switch(c) {
                case 'c':       // compare two element
                        cout<<"Input two element: ";
                        cin>>a>>b;
                        if( cl.Compare(a, b) )
                                cout<<endl<<a<<" == "<<b<<endl;
                        else cout<<endl<<a<<" != "<<b<<endl;
                        Help();
                        break;
                case 'd':       // delete intem from list
                        if( !cl.GetLength() ) cout<<"Empty list!"<<endl;
                        else {
                                cout<<"Input index you want to delete (1-"<< cl.GetLength() <<"): ";
                                cin>>iPos;
                                cout<<endl;
                                if( !cl.Delete(iPos, &e) ) cout<<"Invalid position!"<<endl;
                                else cout<<"Delete item value of position "<<iPos<<" is "<<e<<endl;
                        }
                        Help();
                        break;
                case 'h':       // show help info
                        Help();
                        break;
                case 'i':       // insert item into list
                        if( !cl.GetLength() ) {
                                cout<<"Empty list. You must insert item at position 1."<<endl;
                                iPos = 1;
                        }
                        else {
                                cout<<"Input index you want to insert (1-"<<1+cl.GetLength()<<"): ";
                        		cin>>iPos;
                                cout<<endl;
                        }
                        cout<<"Input value you want to insert: ";
                        cin>>e;
                        cout<<endl;
                        if( !cl.Insert(iPos, e) ) cout<<"Invalid position."<<endl;
                        Help();
                        break;
                case 'l':       // locate input element position
                        cout<<"Please input element value to locate: ";
                        cin>>e;
                        cout<<endl;
                        iPos = cl.Locate(e);
                        if( -1 == iPos ) ;
                        else if( 0 == iPos )
                                cout<<"Can not find element "<<e<<endl;
                        else
                                cout<<"Position of element "<<e<<" is "<<iPos<<endl;
                        Help();
                        break;
                case 'q':       // quit the program
                        return 0;
                case 's':       // show all list members
                        cl.Show();
                        Help();
                        break;
                default:
                        cout<<"Invalid input char."<<endl;
                        Help();
                        break;
                }
                cout<<"Please input your choice: ";
                try {
                        cin>>c;
                        if( !cin ) throw;
                }
                catch(...) {
                        cout<<"Ilegal input. Program exit."<<endl;
                        return 1;
                }
                cout<<endl;
        }
#endif

#if _TEST_CLINKLIST_
        ElemType N[5] = {3, 9, 8, 10, 2};
        CLinkList<ElemType> cLiklst;
        cLiklst.Init(N, 5);
        cLiklst.Show();
#endif

#if _TEST_CSLINKLIST_
        //to test cslinklist class
        CSLinklist<ElemType> cSLiklst(100);
        cSLiklst.Init(5);
        cSLiklst.Show();
        cout<<"After delete element: "<<cSLiklst.Delete(3)<<endl;
        cSLiklst.Show();
        cout<<"After insert 15 at position 4: "<<endl;
        cSLiklst.Insert(4, 15);
        cSLiklst.Show();
        cout<<"Locate element 10 position: "<<cSLiklst.Locate(10)<<endl;
        cout<<"Get length of list: "<<cSLiklst.GetLength()<<endl;
        cout<<"List is full? "<<( (cSLiklst.IsFull() ) ? ( "Yes" ) : ( "No" ) )<<endl;
        cout<<"Get item 2: "<<cSLiklst.GetItem(2)<<endl;
        cout<<"Clear list..."<<endl; cSLiklst.Clear();

#endif

#if _TEST_CCLINKLIST_
        CCLinklist<ElemType> ccl;
        int iNum = 10;
        cout<<"Input "<<iNum<<" value to create list."<<endl;
        ccl.Create(iNum);
        ccl.Display();
        cout<<"Delete element of position 2: "<<ccl.Delete(2)<<endl;
        ccl.Display();
        cout<<"Insert element 88 at position 6. "<<endl;
        ccl.Insert(6, 88);
        ccl.Display();
        cout<<"Locate element 5 position: "<<ccl.Locate(5)<<endl;
        cout<<"Display prior of element 88: "<<ccl.Prior(88)<<endl;
        cout<<"Length of list: "<<ccl.GetLength()<<endl;
        cout<<"Empty of list: "<<( (ccl.IsEmpty())?("Yes"):("No") )<<endl;
#endif
        return 0;
}
