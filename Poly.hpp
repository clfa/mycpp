//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:36
//
// Filename:		Poly.hpp
//
// Description: 
//
//=============================================================================
#ifndef _POLY_HPP
#define _POLY_HPP

#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

const float cfPre = 10E-6;

#define Max 20
typedef struct PolyArr{
        float coef;        // 系数
        int exp;           // 指数
} PolyArray[Max];          // 多项式数组，用于暂存多项式各项

struct PolyNode {               // 使用双链表来创建每个节点
        float coef;             // 系数
        int exp;                // 指数
        PolyNode* prior;        // 指向前一个多项式项
        PolyNode* next;         // 指向下一个多项式项
};

class Poly {
public:
        Poly();                 // 构造函数，建立空多项式
        ~Poly();                // 析构函数，释放内存
        Poly( const Poly& P );  // 复制构造函数
        Poly& operator=( const Poly& P ); // 重载赋值运算符
        void Create( PolyArray a, int n); // 键盘输入，创建多项式链表
        void Display();                    // 显示多项式
        void Sort();                       // 有序表排序
        void PolyNodeAdd( PolyNode elem ); // 多项式与单个元素加
        void PolyNodeSubstract( PolyNode elem ); // 多项式与单个元素减
        void PolyNodeMultiply( PolyNode elem );
        void Add( Poly& LB );           // 多项式加法
        void Substract( Poly& LB );     // 多项式减法
        void Multiply( Poly LB );       // 多项式乘法
        void Clear();                   // 清除多项式所有元素
private:
        PolyNode* head;         // 头指针
};

#endif  // end of _POLY_HPP





