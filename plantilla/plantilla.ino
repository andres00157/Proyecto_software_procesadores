#include "manejos_registros.h"

/*
 * 
 * Declaraciones funciones
 * 
 */


/*
 * 
 * Declaraciones variables
 * 
 */


int main(void){
/*
 * Configuraciones iniciales
 */
  SREG &= ~(1<<7); // Desactivar interrupciones

     
  SREG|=(1<<7); // Activar interrupciones


  while(1){

  }
}


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
  
}
ISR(USART0_TX_vect){
}
