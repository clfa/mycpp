//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:34
//
// Filename:		Poly.cpp
//
// Description: 
//
//=============================================================================
#include "Poly.hpp"

Poly::Poly() {                  // 创建空多项式
        head = new PolyNode;
        head->prior = NULL;
        head->next = NULL;
}

Poly::~Poly() {                 // 析构函数，
        PolyNode* p;
        while( head ) {
                p = head->next;
                delete head;
                head = p;
        }
}

Poly::Poly( const Poly& P ) {   // 复制构造函数
        head = new PolyNode;
        head->next = NULL;
        head->prior = NULL;
        PolyNode* s = head;
        PolyNode* t = P.head->next;
        while( t ) {
                PolyNode* m = new PolyNode;
                m->coef = t->coef; m->exp = t->exp;
                m->next = s->next; s->next = m; m->prior = s;
                t = t->next; s = s->next;
        }
}

Poly& Poly::operator=( const Poly& P ) { // 赋值运算符重载函数
        Clear();
        PolyNode* s = head;
        PolyNode* t = P.head->next;
        while( t ) {
                PolyNode* m = new PolyNode;
                m->coef = t->coef; m->exp = t->exp;
                m->next = s->next; s->next = m; m->prior = s;
                t = t->next; s = s->next;
        }
        return *this;
}

void Poly::Create( PolyArray a, int n) { // 从多项式数组取值创建多项式多项式
        PolyNode* p = head;
        int i=0;
        while( i<n) {
                PolyNode* e = new PolyNode;
                e->coef = a[i].coef; e->exp = a[i].exp;
                e->prior = p; e->next = p->next;
                p->next = e; p = e;
                i++;
        }
}

void Poly::Display() {          // 显示多项式元素
        if( !head->next ) {     // 首先判断多项式是否为空
                cout<<"Empty poly list, nothing to show."<<endl;
                return;
        }
        PolyNode* wkID = head->next;
        int iPutTimes = 0;
        while( wkID ) {
                if( iPutTimes && wkID->coef>0 ) // 如果不是第一个多项式项则为正实数时加上‘+’号输出
                        cout<<" + ";
                cout<<wkID->coef<<" x^"<<wkID->exp<<" ";
                wkID = wkID->next;
                iPutTimes++;
        }
        cout<<endl;
}

void Poly::Sort() { // 对多项式按照指数大小升序排列，此方法很巧妙，为之点赞
        PolyNode* p, *q, *r;
        p = head->next;
        if( p ) {
                r = p->next;  r->prior=NULL; //r指向p的后继节点
                p->next = NULL; //构造只有一个节点的有序表
                p = r;
                while( p ) {
                        r = p->next;
                        q = head;
                        while( q->next && q->next->exp < p->exp )
                                q = q->next; //在有序表中插入*p的前驱节点*q
                        p->next = q->next;   if( r )  r->prior = NULL; //*p插入到*q之后
                        q->next = p; p->prior = q->next;
                        p = r;
                }
        }
}

void Poly::PolyNodeAdd( PolyNode elem ) { // 添加元素到多项式
        PolyNode* P, *Q;
        P = head;
        Q = P->next;
        while( Q ) {
                if( Q->exp < elem.exp ) { // 元素的指数大于当前项指数，继续往下遍历多项式
                        P = Q; Q = Q->next;
                }
                else if( Q->exp==elem.exp ) {
                        Q->coef += elem.coef;
                        if( fabs(Q->coef)<cfPre ) { // 对应元素相加系数和为0，从多项式中删除此元素
                                P->next = Q->next;
                                delete  Q;
                                if( P->next ) P->next->prior = P;
                        }
                        return;
                }
                else {          // 元素的指数比多项式当前项的小，拷贝元素，加入新节点
                        PolyNode* pnAdd = new PolyNode;
                        pnAdd->coef = elem.coef;
                        pnAdd->exp = elem.exp;
                        pnAdd->next =  Q;
                        P->next = pnAdd;
                        pnAdd->prior = P; Q->prior = pnAdd;
                        return;
                }
        }
        // 为找到同幂的项，将元素直接加入多项式最后
        PolyNode* pnAdd = new PolyNode;
        pnAdd->coef = elem.coef;
        pnAdd->exp = elem.exp;
        pnAdd->next = Q; pnAdd->prior = P;
        P->next = pnAdd;
}

void Poly::PolyNodeSubstract( PolyNode elem) { // 添加元素的取负系数项到多项式
        PolyNode temp;
        temp.coef = -elem.coef;
        temp.exp = elem.exp; // 多项式与元素减法，将元素系数取负值，再执行加法运算即可
        PolyNodeAdd( temp );
}

void Poly::PolyNodeMultiply( PolyNode elem ) {  //元素与多项式乘
        if( fabs( elem.coef )<cfPre ) return;
        PolyNode* p = head->next;
        while( p ) {
                p->coef = p->coef * elem.coef;
                p->exp = p->exp + elem.exp;
                p = p->next;
        }
}

void Poly::Add( Poly& LB ) {         // 执行多项式与多项式的加法
        if( !LB.head->next ) return; // 若LB为空多项式则退出
        float fSum;
        PolyNode* pa, * pb, * qa, * qb;
        pa = head;
        qa = pa->next;
        pb = LB.head;
        qb = pb->next;
        while( qa && qb ) {     // 两表都非空
                //cout<<"==A: "; Display(); cout<<"==B: "; LB.Display();
                if( qa->exp < qb->exp ) { // 多项式当前第一项指数比多项式LB的小，
                        pa = qa; qa = qa->next;
                }
                else if( qa->exp > qb->exp ) { // 多项式当前项比LB的大，将LB中的该项加入到多项式中来
                        pb->next = qb->next; // 将LB的当前项与多项式分隔开，
                        qb->next = qa;
                        pa->next = qb; // 将LB的当前项插入到多项式中
                        qb->prior = pa; qa->prior = qb; if( pb->next ) pb->next->prior = pb;
                        pa = qb; // 多项式的pa指向新加入的项，而qa位置未变
                        qb = pb->next; // qb位置重新设定未之前的下一个
                }
                else {          // 两多项式当前项指数相同
                        fSum = qa->coef + qb->coef; // 各自系数相加
                        if( fabs( fSum )<cfPre ) { // 系数之和为零
                                pa->next = qa->next; // 删除qa
                                delete qa;
                                qa = pa->next;
                                pb->next = qb->next; // 删除qb
                                delete qb;
                                qb = pb->next;
                                if( qa ) qa->prior=pa; if( qb ) qb->prior=pb;
                        }
                        else {  // 系数之和不为零
                                qa->coef = fSum;
                                pa = qa;
                                qa = qa->next;
                                pb->next = qb->next;
                                delete qb;
                                qb = pb->next;
                                if( qb ) qb->prior=pb;
                        }
                }
        } /* end of while*/
        if( qb ) { // qb非空，说明其起始指数比多项式的最大指数项的指数都大，直接到到多项式最后即可
                pa->next = qb;
                qb->prior = pa;
                pb->next = NULL;
        }
}

void Poly::Substract( Poly& LB ) {   // 多项式与多项式的减法
        if( !LB.head->next ) return; // 若LB为空多项式则退出
        float fDiff;
        PolyNode* pa, * pb, * qa, * qb;
        pa = head;
        qa = pa->next;
        pb = LB.head;
        qb = pb->next;
        while( qa && qb ) {     // 两表都非空
                if( qa->exp < qb->exp ) { // 多项式当前第一项指数比多项式LB的小，
                        pa = qa; qa = qa->next;
                }
                else if( qa->exp > qb->exp ) { // 多项式当前项比LB的大，将LB中的该项加入到多项式中来
                        pb->next = qb->next; // 将LB的当前项与多项式分隔开，
                        qb->next = qa;
                        pa->next = qb; // 将LB的当前项插入到多项式中
                        qb->prior = pa; qa->prior = qb; if( pb->next ) pb->next->prior = pb;
                        pa = qb; // 多项式的pa指向新加入的项，而qa位置未变
                        qb = pb->next; // qb位置重新设定未之前的下一个
                }
                else {          // 两多项式当前项指数相同
                        fDiff = qa->coef - qb->coef; // 各自系数相加
                        if( fabs( fDiff )<cfPre ) { // 系数之和为零
                                pa->next = qa->next; // 删除qa
                                delete qa;
                                qa = pa->next;
                                pb->next = qb->next; // 删除qb
                                delete qb;
                                qb = pb->next;
                                if( qa ) qa->prior=pa; if( qb ) qb->prior=pb;
                        }
                        else {  // 系数之和不为零
                                qa->coef = fDiff;
                                pa = qa;
                                qa = qa->next;
                                pb->next = qb->next;
                                delete qb;
                                qb = pb->next;
                                if( qb ) qb->prior=pb;
                        }
                }
        } /* end of while*/
        if( qb ) { // qb非空，说明其起始指数比多项式的最大指数项的指数都大，直接到到多项式最后即可
                pa->next = qb;
                qb->prior = pa;
                pb->next = NULL;
        }
}

void Poly::Multiply( Poly LB ) { // 多项式与多项式相乘
        if( !LB.head->next )
                return;         // LB为空，则退出

        Poly totRes ;             // 最后的各子多项式之和
        PolyNode* p = head->next; // 遍历LB的工作指针
        while( p ) {              // 遍历LB
                Poly lbTemp( LB );
                PolyNode e;
                e.coef = p->coef; e.exp = p->exp;
                lbTemp.PolyNodeMultiply( e ); //lbTemp.Display();
                totRes.Add( lbTemp ); // 再将temp每次都加到最后的总多项式中去
                p = p->next;
        }
        Clear();                // 清除当前多项式
        p = totRes.head->next;
        head->next = p;
        totRes.head->next = NULL;
        p->prior = head;
}

void Poly::Clear() {         // 清除多项式除头结点外的所有节点
        PolyNode* p = head;
        while( head->next )  {
                p = head->next->next;
                delete head->next;
                head->next = p;
        }
}
