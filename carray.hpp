/*=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-18 06:33
//
// Filename: carray.hpp
//
// Description: 
//
=============================================================================*/
#ifndef _CARRAY_H_
#define _CARRAY_H_

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

using namespace std;

#define		MAX_ARRAY_DIM	        8
#define		CARRAY_ERROR			2
#define 	CARRAY_UNDERFLOW		1
#define 	CARRAY_OK				0
#define 	CARRAY_OVERFLOW	 	    -1

template<class numType>
struct Array {
        numType*	base;          // 数组元素基地址
        int			dim;           // 数组维数
        int*		bounds;        // 数组维界基址
        int*		constants;     // 数组映像函数常量基址
};

template<class numType>
class CArray {
private:
        Array<numType> arr;
        va_list ap;
public:
        CArray( int dim, ... ) {
                if( dim<1 || dim>MAX_ARRAY_DIM )
                        throw CARRAY_ERROR;
                
                arr.dim = dim;
                arr.bounds = (int*)malloc(dim * sizeof(int));
                if( !arr.bounds )
                        throw CARRAY_OVERFLOW;

                int elemtotal = 1;
                
                va_start( ap, dim );
                for(int i=0; i<dim; ++i) {
                        arr.bounds[i] = va_arg( ap, int );
                        if( arr.bounds[i]<0 )
                                throw CARRAY_UNDERFLOW;
                        elemtotal *= arr.bounds[i];
                }
                va_end( ap );
                
                arr.base = (numType*)malloc(elemtotal * sizeof(numType));
                if( !arr.base )
                        throw CARRAY_OVERFLOW;
                
                arr.constants = (int*)malloc(dim * sizeof(int));
                if( !arr.constants )
                        throw CARRAY_OVERFLOW;
                
                arr.constants[dim-1] = 1;
                for(int i=dim-2; i>=0; i--)
                        arr.constants[i] = arr.bounds[i+1] * arr.constants[i+1];
        }

        ~CArray() {
                if( !arr.base )
                        throw CARRAY_ERROR;
                free( arr.base );
                arr.base = NULL;
                
                if( !arr.bounds )
                        throw CARRAY_ERROR;
                free( arr.bounds );
                arr.bounds = NULL;
                
                if( !arr.constants )
                        throw CARRAY_ERROR;
                free( arr.constants );
                arr.constants = NULL;
        }

        void Locate( numType& e, ... )  {
                int off = 0;
                va_start( ap, e );
                for( int i=0; i<arr.dim; ++i ) {
                        int ind = va_arg( ap, int );
                        if( ind<0 || ind>=arr.bounds[i] ) {
                                va_end( ap );
                                return;
                        }
                        off += arr.constants[i] * ind;
                }
                va_end( ap );
                e = *( arr.base + off );
        }

        void Assign( numType e, ... ) {
                int off = 0;
                va_start( ap, e );
                for( int i=0; i<arr.dim; ++i ) {
                        int ind = va_arg( ap, int );
                        if( ind<0 || ind>=arr.bounds[i] ) {
                                va_end( ap );
                                return;
                        }
                        off += arr.constants[i] * ind;
                }
                va_end( ap );
                *( arr.base + off ) = e;
        }

        void Display() {
                switch( arr.dim ) {
                case 1:
                        for( int i=0; i<arr.bounds[0]; i++) {
                                numType e;
                                Locate( e, i );
                                cout<<e<<"\t";
                        }
                        cout<<endl;
                        break;
                case 2:
                        for( int i=0; i<arr.bounds[0]; i++ ) {
                                for( int j=0; j<arr.bounds[1]; j++ ) {
                                        numType e;
                                        Locate( e, i, j );
                                        cout<<e<<"\t";
                                }
                                cout<<endl;
                        }
                        break;
                case 3:
                        for( int i=0; i<arr.bounds[0]; i++ ) {
                                for( int j=0; j<arr.bounds[1]; j++ ) {
                                        for( int k=0; k<arr.bounds[2]; k++ ) {
                                                numType e;
                                                Locate( e, i, j, k );
                                                cout<<e<<", ";
                                        }
                                        cout<<"\t";
                                }
                                cout<<endl;
                        }
                        break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                        break;
                }
        }
};

#endif /* _CARRAY_H_ */
