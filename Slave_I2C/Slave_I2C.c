////////////////////////////////////////////////////////////////////////////////
//                    COMUNICACIÓN I2C EN TRE DOS PIC                         //
//                                                                            //
//                      Aplicación para PIC ESCLAVO                           //
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

//definicion de salidas para driver A4988
#DEFINE enable PORTD,0
#DEFINE dir    PORTD,1
#DEFINE step   PORTD,2
int incoming;
/*********** Interrupciones del modulo SSP de comunicaciones ******************/

#INT_SSP                 // Arquitectura de interrupción del modulo SSP
void SSP_isr()        
{
int state;

state = i2c_isr_state();    // Asignación del estado del bus I2C

if(state < 0x80)     // El maestro está enviando datos
  {
  
   incoming = i2c_read();   // El esclavo lee los datos recibidos
      
  }

}
/******************************************************************************/

/*************************** FUNCIÓN PRINCIPAL ********************************/

void main() {

   enable_interrupts(INT_SSP);   // Activación de los modulos de interrupción
   enable_interrupts(GLOBAL);
   set_tris_d(0);
   setup_oscillator(OSC_4MHZ);
  
   delay_ms(100);                 // Espera 100ms
   portd=0;  

  while (TRUE) {
 
   bit_set(enable);
   if(incoming==1){
      for(int16 i=0; i<=200;i++){
         bit_clear(enable);
         bit_set(dir);
         bit_set(step);
         delay_ms(3);
         bit_clear(step);
         delay_ms(3);
      }
      incoming=0;
   } 
/******************************************************************************/      
   }
}

/******************************************************************************/
