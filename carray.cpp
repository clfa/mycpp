/*=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-18 06:33
//
// Filename: carray.cpp
//
// Description: 
//
=============================================================================*/
#include "carray.hpp"

int main(void) {
        CArray<int> ci( 3, 3, 6, 3 );
        for(int i=0; i<3; i++) {
                for(int j=0; j<6; j++) {
                        for(int k=0; k<3; k++) {
                                ci.Assign( i*3+8-j+k, i, j, k );
                        }
                }
        }

        ci.Display();
        
        return 0;
}
