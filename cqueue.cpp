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
    cout<<"ciq.GetHead(): "<<ciq.GetHead()<<endl;
    ciq.Tranverse();
    cout<<"ciq.GetLength(): "<<ciq.GetLength()<<endl;
}