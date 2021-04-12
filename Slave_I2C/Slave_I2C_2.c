////////////////////////////////////////////////////////////////////////////////
//                    COMUNICACI�N I2C EN TRE DOS PIC                         //
//                                                                            //
//                      Aplicaci�n para PIC ESCLAVO                           //
//                                                                            //
//                                                                            //
//                          Desarrollo de JCesarMD                            //
//            Adaptado por Gustavo Trejo para integrar con myRio 1900         // 
////////////////////////////////////////////////////////////////////////////////

#include <16F887.h>
#FUSES XT, NOWDT, BROWNOUT, NOLVP, MCLR, PUT
#use delay(internal=4000000)
#use standard_io(c)
#use i2c(SLAVE, SLOW, SDA=PIN_C4, SCL=PIN_C3, force_hw, address=0x10,)
#byte PORTD=8 // identificador del puerto D


int incoming;
/*********** Interrupciones del modulo SSP de comunicaciones ******************/

#INT_SSP                 // Arquitectura de interrupci�n del modulo SSP
void SSP_isr()        
{
int state;

state = i2c_isr_state();    // Asignaci�n del estado del bus I2C

if(state < 0x80)     // El maestro est� enviando datos
  {
  
   incoming = i2c_read();   // El esclavo lee los datos recibidos
      
  }

}
/******************************************************************************/

/*************************** FUNCI�N PRINCIPAL ********************************/

void main() {

   enable_interrupts(INT_SSP);   // Activaci�n de los modulos de interrupci�n
   enable_interrupts(GLOBAL);
   set_tris_d(0);
   setup_oscillator(OSC_4MHZ);
  
   delay_ms(100);                 // Espera 100ms
   portd=0;  

  while (TRUE) {
   if(incoming==1){
      output_toggle(PIN_D0);
      incoming=0;
   } 
/******************************************************************************/      
   }
}

/******************************************************************************/
