#include "complejos.h"
#include "manejo_registros.h"
#include <math.h>



/* ---------------------- Analysis in Frequency Domain ---------------------- */

#define FORWARD              1    /* Forward direction for FFT computation    */
#define REVERSE              0    /* Reverse direction for FFT computation    */

/* -------- Default Values for Iteration in Time & Frequency Domain --------- */

#define MAX_TIME_SAMPLES     128   /* Testing default value for time_samples */
#define PADDING_POWER        2                /* Default padding power factor */
#define MAX_FREQ_SAMPLES     MAX_TIME_SAMPLES<<PADDING_POWER  /* freq_samples */


/** * Declaraciones funciones * */

int Compute_FFT( int, int, COMPLEX_T *, int* );

/******************************* Complex Vector *******************************/
static COMPLEX_T datos[MAX_FREQ_SAMPLES];

int flag = 0;

int main(void){
/*
 * Configuraciones iniciales
 */
  SREG &= ~(1<<7); // Desactivar interrupciones
  conf_uart_tx(false, true, 1);
     
  SREG|=(1<<7); // Activar interrupciones


/****************  Declaraciones variables locales   *******************/
  int dir = FORWARD;
  int time_samples = MAX_TIME_SAMPLES;
  int freq_samples = MAX_FREQ_SAMPLES;
  int power = Find_Power( freq_samples);
  int    samples_per_period = 20;
  double frequency  = 60;
  double period     = 1.0 / frequency;
  double delta_time = period / samples_per_period;
  double delta_freq = 1.0 / (delta_time * freq_samples);

  double omegadt    = 2 * M_PI * frequency * delta_time;
  int salida = 1;
  int i = 0;
  int cont=0;
  int cont_tiempo = 0;
  int state = 0;
  int flag_2 = 0;
  while(1){

    if(flag && state==0){
      cont_tiempo++;
      flag = false;
      cargar_dato(salida);
      datos[cont_tiempo].real= salida;
      cont++;
      if(cont>=10){
        if(salida==1)salida=0;
        else salida = 1;
        cont = 0;
      }
      if(cont_tiempo>=time_samples){
        state = 1;
      }
    }else if(state==1){
       while(flag_2){
        Compute_FFT( dir, power, datos, &flag_2);  
      }
      flag = true;
      state = 2;
      cont_tiempo = 0;
    }else if(flag && state==2){
      flag = false;
      cont_tiempo++;
      cargar_dato((int)cplx_Magnitude(datos[cont_tiempo]));
      if(cont_tiempo>=128){
        state = 0;
        flag= 1;
      }
    }
/*

     
      while(flag){
        Compute_FFT( dir, power, datos, &flag);  
      }
      
      for( i = 0; i < freq_samples/2; i++ ){
         cplx_Magnitude( datos[i] );
      }
*/


  }
}




/* ---------------------- Analysis in Frequency Domain ---------------------- */

/*FN****************************************************************************
*
*   int
*   Compute_FFT( int dir, int pow, COMPLEX_T *x );
*
*   Return:          Transformation in values passed by reference
*
*   Purpose:         Compute an in-place complex-to-complex FFT
*
*   Note:            This function computes an in-place complex-to-complex FFT
*                    x.real and y.imag are the real and imaginary arrays of
*                    2^pow points.
*                    dir = 1 or FORWARD gives forward transform
*                    dir = 0 or REVERSE gives reverse transform
*
*                    There is a modification by Peter Cusak to utilize the
*                    Microsoft complex type.
*
*   Plan:
*           Part 1: Calculate the number of points
*           Part 2: Do the bit reversal
*           Part 3: Compute the FFT
*           Part 4: Scale for forward transformation
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   -------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Incorporation of functions with complex numbers
*   May 03/2013  J.C.Giraldo  Readable identifiers
*   Jun --/1993  P. Bourkes   Initial implementation
*
*******************************************************************************/

int
Compute_FFT( int dir, int powe, COMPLEX_T *x, int *flag)
{
static long    points, i, j, k, l, i1, i2, l1, l2;
static COMPLEX_T c, temp, u;
static int state=0;
switch(state){
  case 0:
    if(*flag==1){
      /* Part 1: Calculate the number of points */
      points = 1;
      i = 0;
      state = 7;  
    
    }
    break;
  case 1:
    if(i < points-1){
      if( i < j ) cplx_Swap( &x[i], &x[j] );
        k = i2;
        state = 2;
    }else{
      /* Part 3: Compute the FFT */
      c.real = -1.0;
      c.imag =  0.0;
      
      l2 =  1;
      l = 0;
      state = 3;
    }
    break;
    
  case 2:
    if(k<=j){
      j -= k;
      k >>= 1; 
      state = 2;
    }else{
      j+=k;
      i++;
      state = 1;
    }
    break;
  case 3:
    if(l < powe){
      l1 = l2;
        l2 <<= 1;
        u.real = 1.0;
        u.imag = 0.0;
        j = 0;
        state = 4;
    }else{
      /* Part 4: Scale for forward transformation */
      if( dir == FORWARD ){
        i = 0;
        state = 6;  
      }else{
        *flag = 0;
        state = 0;
      }
    }
    break;  
  case 4:
    if(j < l1){
        i = j;
        state = 5;
    }else{
      c.imag = sqrt( ( 1.0 - c.real ) / 2.0 );
        if( dir == FORWARD ) c.imag = -c.imag;
        c.real = sqrt( ( 1.0 + c.real ) / 2.0 );
        l++;
        state =3;
    } 
    break;
  case 5:
    if(i < points){
        i1    = i + l1;
            temp  = cplx_Multiply( u, x[i1] );
            x[i1] = cplx_Subtract( x[i], temp );
            x[i]  = cplx_Add( x[i], temp );
            i += l2;
            state = 5;
    }else{
      u = cplx_Multiply( u, c );
      j++;
      state = 4;
    }
    break;
  case 6:
    if(i < points){
      x[i] = cplx_Scale( x[i], points );
      i++;
      state = 6; 
    }else{
      *flag = 0;
      state = 0;
    }
    break;
  case 7:
    if(i < powe){
      points <<= 1;
      i++;
      state = 7;
    }else{
      /* Part 2: Do the bit reversal */
      i2 = points >> 1;
      j = 0;
      i = 0;
      state = 1;
    }
    break;
}


} /* Compute_FFT */



///////////////////////////////////////////////////////////////////////////////
/*
 * Funciones interrupciones
 */

ISR(TIMER1_COMPA_vect){
}
ISR(TIMER0_COMPA_vect){

}
ISR(ADC_vect){

}
ISR(USART0_UDRE_vect){
  flag = 1;
}
ISR(USART0_TX_vect){
}
