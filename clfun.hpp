//=============================================================================
//
// Author: safesky - safesky@163.com
//
// Copyright: safesky
//
// Last modified:	2015-05-12 13:36
//
// Filename:		clfun.hpp
//
// Description: 
//
//=============================================================================
#ifndef		_CLFUN_HPP_
#define 	_CLFUN_HPP_

//格式输出一维数组，比如如下格式：
//（A B C D E F G）
//（H I J K L M N）
//（O P Q R S T）
//（U V W X Y Z）
#define FORMAT_PRINT_ARRAY_1D(ARRAY, N, FS)                 \
        int iPT=0;                                          \
        int iPC=10;                                         \
        for(int i=0; i<N; i++) {                            \
                iPT++;                                      \
                if( 1==iPT ) cout<<"( ";                    \
                cout<<ARRAY[i];                             \
                if( iPT<iPC && i!=N-1 ) cout<<FS;           \
                if( iPT==iPC ) {                            \
                        cout<<" )"<<endl;                   \
                        iPT = 0;                            \
                }                                           \
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

/* 样本标准差 */
double stdev_cpp (vector <float > vfData)           {
        double dSum = accumulate(vfData.begin (),vfData .end (),0.0);
        double dMean =  dSum /vfData .size ();
        double accum = 0.0;
        for_each( std:: begin(vfData ), std ::end (vfData ), [&]( const double dEveryOne ) {
                        accum += (dEveryOne - dMean ) * (dEveryOne - dMean);
                });
        return sqrt( accum/(vfData .size ()-1));
}

/* 判断任意位置长方形内是否存在某一点 */
{
        
        typedef struct Point2D32f {
                float x;                /* x coordinate */
                float y;                /* y coordinate */
        } Point2D32f;

        typedef struct Point3D32f {
                float x;               /* x coordinate */
                float y;               /* y coordinate */
                float z;               /* z coordinate */
        } Point3D32f;

        float W (Point2D32f cpPXY, Point2D32f cpQXY) {
                return ( cpPXY.x *cpQXY.y -cpPXY.y * cpQXY.x );
        }

        bool IsInRect(Point3D32f cpFir, Point3D32f cpSec, Point3D32f cpThr , Point3D32f cpFor , Point3D32f cpPnt) {
                Point2D32f cpV = cvPoint2D32f( cpPnt.x - cpFir.x, cpPnt.y - cpFir.y );
                Point2D32f cpA = cvPoint2D32f( cpSec.x - cpFir.x, cpSec.y - cpFir.y );
                Point2D32f cpB = cvPoint2D32f( cpFor.x - cpFir.x, cpFor.y - cpFir.y );
                float fH = W( cpV, cpB) / W ( cpA, cpB);
                float fK = W( cpA, cpV) / W ( cpA, cpB);
                if(0 < fH && fH <1.0 && 0 < fK && fK<1.0)
                        return true ;
                return false;
        }

}

/* 获取最大最小值 */
{
        void MinMax(int* iArray, int iNum, int* iMiMaArr)	{
                int i=0;
                int* iMin = (int*)malloc(sizeof(int)*(iNum/2));	
                int* iMax = (int*)malloc(sizeof(int)*(iNum-(iNum/2)));
                int iId = 0;

                for(; i<=(iNum-1); i=i+2)	{
                        if(iArray[i] < iArray[i+1])	{
                                iMin[iId] = iArray[i];
                                iMax[iId++] = iArray[i+1];
                        }
                        else	{
                                iMin[iId] = iArray[i+1];
                                iMax[iId++] = iArray[i];
                        }
                }
                if(iNum%2)
                        iMax[iNum-iNum/2-1] = iArray[iNum-1];
	
                iMiMaArr[0] = iMin[0];
                for(i=1; i<(iNum/2); i++)
                        if(iMin[i] < iMiMaArr[0])
                                iMiMaArr[0] = iMin[i];
                iMiMaArr[1] = iMax[0];
                for(i=1; i<(iNum-iNum/2); i++)
                        if(iMax[i] > iMiMaArr[1])
                                iMiMaArr[1] = iMax[i];
                if(iMiMaArr[0] > iMax[iNum-iNum/2-1])
                        iMiMaArr[0] = iMax[iNum-iNum/2-1];
                free(iMin);
                free(iMax);
        }

        void MinMaxII(int* arr, int N, int* myMin, int* myMax)  {
                int iter;
                int cnt = 0;
                for(iter = 0; iter < N-1; iter += 2)    {
                        if(++cnt && arr[iter] > arr[iter + 1] )   {
                                int temp = arr[iter];
                                arr[iter] = arr[iter + 1];
                                arr[iter + 1] = temp;
                        }
                }
                *myMin = arr[0];
                for(iter = 2; iter < N; iter += 2)   {
                        if(++cnt && arr[iter] < *myMin)  {
                                *myMin = arr[iter];
                        }
                }
                *myMax = arr[1];
                for(iter = 3; iter < N; iter += 2)  {
                        if(++cnt && arr[iter] > *myMax)  {
                                *myMax = arr[iter];
                        }
                }
                if(N % 2 != 0 && ++cnt && *myMax < arr[N - 1]) 
                        *myMax = arr[N - 1];
        }
}


#endif /*  _CLFUN_HPP_ */
