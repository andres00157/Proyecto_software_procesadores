#include "complejos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*****************************  Public Functions  *****************************/

/* ---------------------------- Complex Numbers ----------------------------- */

/*FN****************************************************************************
*
*   void
*   cplx_Swap( COMPLEX_T *a, COMPLEX_T *b );
*
*   Return:          Nothing (result is passed by reference)
*
*   Purpose:         Exchange complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 04/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
cplx_Swap( COMPLEX_T *a, COMPLEX_T *b )
{
COMPLEX_T t;

t  = *a;
*a = *b;
*b =  t;

return 1;

} /* cplx_Swap */



/*FN****************************************************************************
*
*   COMPLEX_T
*   cplx_Multiply( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the product of two complex numbers
*
*   Note:            Temporal vble t is required in order to avoid changing
*                    result when computing result
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 04/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Multiply( COMPLEX_T a, COMPLEX_T b )
{
COMPLEX_T t;

t.real = a.real * b.real - a.imag * b.imag;
t.imag = a.real * b.imag + a.imag * b.real;

return t;

} /* cplx_Multiply */



/*FN****************************************************************************
*
*   COMPLEX_T
*   cplx_Subtract( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the subtraction of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 04/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Subtract( COMPLEX_T a, COMPLEX_T b )
{
a.real -= b.real;
a.imag -= b.imag;

return a;

} /* cplx_Subtract */



/*FN****************************************************************************
*
*   COMPLEX_T
*   cplx_Add( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the summation of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 04/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Add( COMPLEX_T a, COMPLEX_T b )
{
a.real += b.real;
a.imag += b.imag;

return a;

} /* cplx_Add */



/*FN****************************************************************************
*
*   COMPLEX_T
*   cplx_Scale( COMPLEX_T a, long n );
*
*   Purpose:         Return each component scalized to n
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 04/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Scale( COMPLEX_T a, long n )
{
a.real /= (double)n, a.imag /= (double)n;

return a;

} /* cplx_Scale */



/*FN****************************************************************************
*
*   double
*   cplx_Magnitude( COMPLEX_T a );
*
*   Purpose:         Return the magnitude of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 05/13  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

double
cplx_Magnitude( COMPLEX_T a )
{
return sqrt( a.real * a.real + a.imag * a.imag );

} /* cplx_Magnitude */



/*FN****************************************************************************
*
*   double
*   cplx_Phase( COMPLEX_T a );
*
*   Purpose:         Return the phase of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Nov 07/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

double
cplx_Phase( COMPLEX_T a )
{
return atan2( a.imag, a.real );

} /* cplx_Phase */



/*FN****************************************************************************
*
*   double
*   cplx_Ratio( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the ratio of magnitudes of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Nov 07/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

double
cplx_Ratio( COMPLEX_T a, COMPLEX_T b )
{
return fabs( a.real / b.real );

} /* cplx_Ratio */



/*FN****************************************************************************
*
*   int cplx_Initiate_Vector( COMPLEX_T *a, int size );
*
*   Purpose: Fill a complex vector with zeros
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Nov 07/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
cplx_Initiate_Vector( COMPLEX_T *a, int size )
{
int ii;
for(  ii = 0; ii < size; ii++ )
    a[ii].real = 0.0, a[ii].imag = 0.0;

return 1;

} /* cplx_Initiate_Vector */





/*FN****************************************************************************
*
*   int
*   Find_Power( int number );
*
*   Purpose:         Return the (integer) logarithm in base 2 of a number
*
*   Note:            Number must be an integer equal to zero or greater
*                    Another option is shifting and truncation
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 03/13  J.C.Giraldo  Readable identifiers
*   --- --/--  P. Bourkes   Initial implementation
*
*******************************************************************************/

int
Find_Power( long number )
{
int power = 0;

while( number != 1 ) {
    number = (long)( number/2 );
    power++;
}

return( power );

} /* Find_Power */