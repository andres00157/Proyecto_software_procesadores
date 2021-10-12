#ifndef MANEJO_REGISTROS_H
#define MANEJO_REGISTROS_H "manejo_registros.h"


/*
 * 
 * Declaraciones variables fijas
 * 
 */
#define Bit7 7
#define Bit6 6
#define Bit5 5
#define Bit4 4
#define Bit3 3
#define Bit2 2
#define Bit1 1
#define Bit0 0



/*
 * 
 * Declaracion funciones
 * 
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
void conf_uart_tx(bool interrupt_flag_tx, bool interrupt_flag_empty, int Num_bauds);
void cargar_dato(int dato);
bool revision_flag_tx();
bool revision_flag_empty();


#endif
