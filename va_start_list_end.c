/*=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified: 2015-05-16 18:09
//
// Filename: va_start_list_end.c
//
// Description:加深对函数参数传递原理的理解 
//
=============================================================================*/

#include <stdio.h>
#include <stdarg.h>

int fun( int a, ... ) {
        int i;
        va_list p;
        va_start( p, a );
        i = 0;
        while( i++ < a ) 
                printf( "%d\t", va_arg( p, int ) );
        printf("\n");
        va_end( p );
        return 0;
}

int main(void) {
        fun( 4, 12, 8, 5, 6 );

        return 0;
}
