#ifndef COMPLEJOS_H
#define COMPLEJOS_H "complejos.h"


/************************** Definition of Data Types **************************/

/* ---------------------------- Complex Numbers ----------------------------- */

typedef struct {
	double real; /* Real part of type complex number      */
	double imag; /* Imaginary part of type complex number */
} COMPLEX_T;


/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

int cplx_Swap( COMPLEX_T *, COMPLEX_T * );

COMPLEX_T cplx_Multiply( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Subtract( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Add     ( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Scale   ( COMPLEX_T, long );

double cplx_Magnitude( COMPLEX_T );
double cplx_Phase    ( COMPLEX_T );
double cplx_Ratio    ( COMPLEX_T, COMPLEX_T );

int cplx_Initiate_Vector( COMPLEX_T *, int );

int Find_Power( long );



#endif
