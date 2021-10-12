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

void confi_timer1(bool interrupt_flag);
void conf_timer0(bool interrupt_flag);
void conf_adc(bool interrupt_flag);
void habilitar_adc();
void leer_adc();
int lectura_timer1();
bool revision_flag_time1();
bool revision_flag_time0();
bool revision_flag_adc();
int leer_adc(bool);

/*
 * variables
 */
volatile int conteo= 0;
volatile int segundos= 0;

int main(void){
/*
 * Configuraciones iniciales
 */
  SREG &= ~(1<<7); // Desactivar interrupciones
  conf_timer0(true);
  confi_timer1(true);
  conf_adc(true);
  
  habilitar_adc();

  
  Serial.begin(1000000); //velocidad maxima para que no interfiera con otros procesos/
     while (!Serial) {
      ; // Esperar a que el puerto inicie
     }

     
     
  SREG|=(1<<7); // Activar interrupciones

  int dato;
  while(1){

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
 * Configuracion timer 1
 * 
 */

/*
 * configuracion timer 1, con opcion de interrupcion
 */
void conf_timer0(bool interrupt_flag){
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
  OCR0A=20;

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

  if(interrupt_flag) ADCSRA |=(1 << Bit3) // Activar interrupcion

  
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
/*
 * Funciones interrupciones
 */

ISR(TIMER1_COMPA_vect){
}
ISR(TIMER0_COMPA_vect){

}
ISR(ADC_vect){
  int dato;
  dato = leer_adc();
  Serial.println(dato); 
}
