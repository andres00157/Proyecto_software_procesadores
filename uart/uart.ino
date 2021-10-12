
#define Bit7 7
#define Bit6 6
#define Bit5 5
#define Bit4 4
#define Bit3 3
#define Bit2 2
#define Bit1 1
#define Bit0 0

/*
 * Declaraciones funciones
 */

void conf_uart_tx(bool interrupt_flag_tx, bool interrupt_flag_empty, int Num_bauds);
void cargar_dato(int dato);
bool revision_flag_tx();
bool revision_flag_empty();


 /*
 * variables
 */
volatile bool flag = true;




 int main(void){
/*
 * Configuraciones iniciales
 */
  SREG &= ~(1<<7); // Desactivar interrupciones

  conf_uart_tx( false, true ,  1);
  
  SREG|=(1<<7); // Activar interrupciones
  int cont = 1;
  while(1){
    if(flag){
      flag = false;
      cargar_dato(cont);
      cont++;
      if(cont>=256){
        cont = 0;
      }
    }    
  }
}



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



ISR(USART0_UDRE_vect){
  flag = true;
  
}
ISR(USART0_TX_vect){
}
