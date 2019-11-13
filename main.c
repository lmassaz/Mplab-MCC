
//"HOLA"
#include "mcc_generated_files/mcc.h"
uint8_t sec, min, hour, date, month, year;

char Hora[] = "000000";
char Fecha[] = "DATE:  /  /20 ";

void convertirHora(void){
    
    for(uint8_t i=0; i<7; i++){
        Hora[i] &= 0x0F;
    }
    hour = ((Hora[0]<<4)+ Hora[1]);
    min = ((Hora[2]<<4)+ Hora[3]);
    sec = ((Hora[4]<<4)+ Hora[5]);
}

unsigned char MSB(unsigned char x)
{
return ((x >> 4));
 }

unsigned char LSB(unsigned char x)
 {
 return (x & 0x0F);
}

void enviar_hora(void)
{
 
   i2c1_driver_start();       //inicia la comunicación i2c
   i2c1_driver_TXData(0xD0);  //Dirección i2c del DS3231, escritura.
   i2c1_driver_TXData(0x00);  //Dirección de donde quiero empezar a escribir (segundos)
   i2c1_driver_TXData(sec);   //
   i2c1_driver_TXData(min);
   i2c1_driver_TXData(hour);
   i2c1_driver_stop(); 
}

//void enviar_fecha(void)
//{
//    i2c1_driver_start(); //inicia la comunicación i2c
//    i2c1_driver_TXData(0xD0);  //Dirección i2c RTC escritura
//    i2c1_driver_TXData(0x04);  //Dirección de los días.
//    i2c1_driver_TXData(dia);   //escribir día
//    i2c1_driver_TXData(mes);   //escribir mes
//    i2c1_driver_TXData(anio);  //escribir anio
//    i2c1_driver_stop(); 
//    
//}

void leer_hora(void)
{
    i2c1_driver_start(); //inicia la comunicación i2c
    i2c1_driver_TXData(0xD0); //Dirección i2c RTC escritura
    i2c1_driver_TXData(0x00);  //Dirección de los segundos.
    i2c1_driver_restart(); //Reiniciala comunicación I2C
//        
   
    i2c1_driver_startRX();  
//    mssp1_waitForEvent(0);   
//    mssp1_clearIRQ();  //espera para recibir o trasmitir 
    i2c1_driver_TXData(0xD1);  //Dirección i2c ds3231, lectura
//    mssp1_waitForEvent(0);
//    mssp1_clearIRQ();
//    

           
    i2c1_driver_startRX();  
//    mssp1_waitForEvent(0);   
//    mssp1_clearIRQ();  //espera para recibir o trasmitir
    sec= i2c1_driver_getRXData(); //resultado en BCD
    i2c1_driver_sendACK; //envío condición de ACK para decirle al esclavo que envie el siguiente dato (es decir  la posición 01)
//    mssp1_waitForEvent(0);
//    mssp1_clearIRQ();
    

      
    i2c1_driver_startRX();  
//    mssp1_waitForEvent(0);   
//    mssp1_clearIRQ();  //espera para recibir o trasmitir
    min= i2c1_driver_getRXData();        
    i2c1_driver_sendACK;
//    mssp1_waitForEvent(0);
//   mssp1_clearIRQ();   
    

    
    i2c1_driver_startRX();  
//    mssp1_waitForEvent(0);   
//    mssp1_clearIRQ();  //espera para recibir o trasmitir 
    hour= i2c1_driver_getRXData();
    i2c1_driver_sendACK;
    i2c1_driver_sendNACK();  //condición de no ACK para que no siga mandando
//    mssp1_waitForEvent(0);
//    mssp1_clearIRQ();
    
    i2c1_driver_stop();
        
   
//    printf(" %u ",MSB(sec));
    printf(" %u ",sec);
    printf(" %u ",LSB(sec));
    printf(" : ");
    printf(" %u ",MSB(min));
    printf(" %u ",LSB(min));
    printf(" : "); 
    printf(" %u ",MSB(hour));
    printf(" %u ",LSB(hour));
    
    printf(" \r\n ",LSB(hour));
    
//    Hora[0]= MSB(sec);
//    Hora[1]= LSB(sec);
//    Hora[2]= MSB(min);
//    Hora[3]= LSB(min);
//    Hora[4]= MSB(hora);
//    Hora[5]= LSB(hora);
   
//    printf("Hora :");
//    printf(Hora);
//    printf("\r\n");
//    
}

//void leer_fecha(void)
//{
//    
//    i2c1_driver_start(); //inicia la comunicación i2c
//    i2c1_driver_TXData(0xD0); //Dirección i2c RTC escritura
//    i2c1_driver_TXData(0x04);  //Dirección de los segundos.
//    i2c1_driver_restart(); //Reiniciala comunicación I2C
//    i2c1_driver_TXData(0xD1);  //Dirección i2c lectura
//    i2c1_driver_startRX();  
////    dia= i2c1_driver_getRXData; 
//    i2c1_driver_sendACK;
////    mes= BCD_2_DEC(i2c1_driver_getRXData);        
//    i2c1_driver_sendACK;
////    anio= BCD_2_DEC(i2c1_driver_getRXData);
//    
//    i2c1_driver_sendNACK();
//    i2c1_driver_stop();
//    
//}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    i2c1_driver_open(); //abrimos el puerto i2c
         
    printf("DS3231 \r\n");
      
//    i2c1_driver_setAddr(0xD0);

    convertirHora(); 
    enviar_hora();
    
    printf("lectura \r\n");
    
    while (1)
    { 
        leer_hora();     
     __delay_ms(1000);
    
    }
}
