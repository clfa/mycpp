#ifndef		_CLFUN_HPP_
#define 	_CLFUN_HPP_

//格式输出一维数组，比如如下格式：
//（A B C D E F G）
//（H I J K L M N）
//（O P Q R S T）
//（U V W X Y Z）
#define FORMAT_PRINT_ARRAY_1D(ARRAY, N, FS)     \
        int iPT=0;                              \
        int iPC=10;                                \
        for(int i=0; i<N; i++) {                \
                iPT++;                            \
                if( 1==iPT ) cout<<"( ";        \
                cout<<ARRAY[i];                    \
                if( iPT<iPC && i!=N-1 ) cout<<FS;\
                if( iPT==iPC ) {                \
                        cout<<" )"<<endl;        \
                        iPT = 0;                \
                }                                \
                if( 0!=N%iPC && i==N-1 ) cout<<" )"<<endl;  \
        }                                                   \

#define FORMAT_PRINT_ARRAY_2D(ARRAY, N1, N2, FS)                        \
        int iPutTimes = 0;                                              \
        int iPutCnt = 10;                                               \
        for(int i=0; i<N1; i++) {                                       \
                for(int j=0; j<N2; j++) {                               \
                        iPutTimes++;                                    \
                        if( 1==iPutTimes ) cout<<"( ";                  \
                        cout<<ARRAY[i][j];                              \
                        if( iPutTimes<iPutCnt && i*N2+j!=N1*N2-1 ) cout<<FS; \
                        if( iPutTimes==iPutCnt ) {                      \
                                cout<<" )"<<endl;                       \
                                iPutTimes = 0;                          \
                        }if( 0!=N1*N2%iPutCnt && i*N2+j==N1*N2-1 ) cout<<" )"<<endl; \
                }                                                       \
        }                                                               \

#endif /*  _CLFUN_HPP_ */
