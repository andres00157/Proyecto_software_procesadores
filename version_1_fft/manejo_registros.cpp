#include "manejo_registros.h"
#include <avr/io.h>

/*
 * 
 * 
 * Funciones
 * 
 * 
 */

///////////////////////////////////////////////////////////////////////////////
/*
 * 
 *  UART
 * 
 */

void conf_uart_tx(bool interrupt_flag_tx, bool interrupt_flag_empty, int Num_bauds){
  UCSR0A = (1 << Bit1); // Configurando U2Xn en 1 para doble velocidaden asinc
  UCSR0B = (1 << Bit3); // Habilitar trasmicion de datos
  UCSR0C = (1 << Bit1) | (1 << Bit2); // Trabajar con 8 bits


  UBRR0L = Num_bauds;
  
  if(interrupt_flag_tx)    UCSR0B |= (1 << Bit6); // Habilitar interrupcion para tx flag
  if(interrupt_flag_empty) UCSR0B |= (1 << Bit5); // Habilitar interrupcion para empty flag
}
/*
 * Cargar dato a trasmitir
 */
void cargar_dato(int dato){
  UDR0 = dato;
}
/*
 * Revision bandera tx
 */
bool revision_flag_tx(){
  bool flag = false;
  if((1<<Bit6) & UCSR0A){
    flag = true;
    UCSR0A |= (1<<Bit6); // Se borrara de una vez la bandera
  }
  return flag;
}
/*
 * Revision bandera empty
 */
bool revision_flag_empty(){
  bool flag = false;
  if((1<<Bit5) & UCSR0A){
    flag = true;
    UCSR0A |= (1<<Bit5); // Se borrara de una vez la bandera
  }
  return flag;
}

///////////////////////////////////////////////////////////////////////////////

/*
 * 
 * Configuracion timer 0
 * 
 */

/*
 * configuracion timer 0, con opcion de interrupcion
 */
void conf_timer0(bool interrupt_flag, int limite_timer){
  TCCR0A = (1 << Bit1); // Configurar el ctc mode, con el comA desconectado de los pines
    /* 
   *  Bit2 Bit1 Bit0    Preescaler
   *   0    0    1           1
   *   0    1    0           8
   *   0    1    1          64
   *   1    0    0         256
   *   1    0    1        1024
   *  
   *  Bit3=> WGM02 en 1 para modo ctc
   */

  TCCR0B|=  (1 << Bit2) | (0<< Bit1) | (1<<Bit0); 
  /*
   * Valor del comparador 8 bits
   *  f = 16MHz/(Preescaler*(1+ OCR1A))
   */
  OCR0A= limite_timer;

  /*
   * Activar interrupcion para comparador A
   */
   if(interrupt_flag) TIMSK0= (1 << Bit1);
 
  
}

/*
 * Revision bandera timer0, devolucion de estado, y clear
 * de la bandera
 */

bool revision_flag_time0(){
  bool flag = false;
  if((1<<Bit1) & TIFR0){
    flag = true;
    /*
     * Se borrara de una vez la bandera
     */
     TIFR0 |= (1<<Bit1);
  }
  return flag;
}

///////////////////////////////////////////////////////////////////////////////
/*
 * Configuracion adc con opcion de adc, voltage de referencia en vcc, y lectura 
 * de A0
 */

void conf_adc(bool interrupt_flag){

  ADMUX = (1<<Bit6); // Bit6 para referencia en AVCC y el mux en 0 para ADC0
  ADCSRB = (1 << Bit1) | (1 << Bit0); // Auto triger con comparador A
  ADCSRA = (1 << Bit5) | (1 << Bit2)| (1 << Bit1)| (1 << Bit0); // Bit5=> ADATE: autotriger enable 

  if(interrupt_flag) ADCSRA |=(1 << Bit3); // Activar interrupcion
}
/*
 * Habilitar el adc con el bit ADEN
 */
void habilitar_adc(){
  ADCSRA |= (1 << Bit7) ;// Habilitar adc con ADEN
}
/*
 * Lectura ADC
 */
int leer_adc(){
  int lect_adc;
  lect_adc =(ADCL) | (ADCH<<8) ;
  return lect_adc;
}


///////////////////////////////////////////////////////////////////////////////

bool revision_flag_adc(){
  bool flag = false;
  if((1<<Bit4) & ADCSRA){
    flag = true;

    ADCSRA |= (1 << Bit4) ; // Se borrara de una vez la bandera
  }
  return flag;
}

///////////////////////////////////////////////////////////////////////////////
void confi_timer1(bool interrupt_flag){
  TCCR1A=0;                             //Inicializar y Normal operation
  TCCR1B=0;                             // Inicializar Registro

  /* 
   *  Bit2 Bit1 Bit0    Preescaler
   *   0    0    1           1
   *   0    1    0           8
   *   0    1    1          64
   *   1    0    0         256
   *   1    0    1        1024
   *  
   *  Bit3=> WGM02 en 1 para modo ctc
   */

  TCCR1B|=  (1 << Bit3) | (1 << Bit2) | (0<< Bit1) | (1<<Bit0); 

  /*
   * Valor del comparador
   *  f = 16MHz/(Preescaler*(1+ OCR1A))
   */
  OCR1A=15624;
  
  if(interrupt_flag)TIMSK1= (1 << Bit1); // Activar interrupcion para comparador A
      
}
///////////////////////////////////////////////////////////////////////////////
int lectura_timer1(){
  int contador;

  contador = (TCNT1H<<8)|(TCNT1L); // Leyendo los registros en donde esta el conteo
  return contador;
}
///////////////////////////////////////////////////////////////////////////////
bool revision_flag_time1(){
  bool flag = false;
  if((1<<Bit1) & TIFR1){
    flag = true;

    TIFR1 |= (1<<Bit1); // Se borrara de una vez la bandera
  }
  return flag;
}
///////////////////////////////////////////////////////////////////////////////
