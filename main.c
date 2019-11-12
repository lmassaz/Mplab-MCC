
/*
                         Main application
 */

#include "mcc_generated_files/mcc.h"
uint8_t sec, min, hora;
uint8_t dia, mes, anio;

char Hora[] = "105845";
char Fecha[] = "200319";

void convertirHora(void){
    
    for(uint8_t i=0; i<7; i++){
        Hora[i] &= 0x0F;
    }
    
    hora = ((Hora[0]<<4)+ Hora[1]);
    min = ((Hora[2]<<4)+ Hora[3]);
    sec = ((Hora[4]<<4)+ Hora[5]);
}

void convertirFecha(void){
    
    for(uint8_t i=0; i<7; i++){
        Fecha[i] &= 0x0F;
    }
    
    dia = ((Fecha[0]<<4)+ Fecha[1]);
    mes = ((Fecha[2]<<4)+ Fecha[3]);
    anio = ((Fecha[4]<<4)+ Fecha[5]);
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    i2c1_driver_open(); //abrimos el puerto i2c
         
    //--------------------------------------------------------------------------
    //HORA: SEGUNDOS-MINUTOS-HORAS-----------------------------------------------
    printf("comunicación serial");
    convertirHora();
//    i2c1_driver_setAddr(0xD0);
    
//ESCRIBIR
    //        I2C_start();            //Incia comunicaión I2C
//    I2C_write(0xD0);        //Escoje dirección del reloj
//    I2C_write(0x00);        //Posición de los segundos
//    I2C_write(sec);         //Posición donde va leer
//    I2C_write(min);         //Posición donde va leer
//    I2C_write(hora);        //Posición donde va leer
//    I2C_stop();             //Detiene la comunicaión I2C
//    
    
    i2c1_driver_start(); //inicia la comunicación i2c
    i2c1_driver_TXData(0xD0);
    i2c1_driver_TXData(0x00);
    i2c1_driver_TXData(sec);
    
 //LEER  
//       I2C_start();            //Incia comunicaión I2C
//    I2C_write(0xD0);        //Escoje dirección del reloj
//    I2C_write(0x00);        //Posición donde va leer
//    I2C_restart();          //Reinicia la comuniación I2C
//    I2C_write(0xD1);        //Leer posición
//    sec = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    min = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    hora = I2C_read();      //lee posicion de reloj
//    I2C_nack();
//    I2C_stop();             //Termina comunicaion I2C
    
    
    while (1)
    {
        i2c1_driver_start(); //inicia la comunicación i2c
        i2c1_driver_TXData(0xD0);
        i2c1_driver_TXData(0x00);
        i2c1_driver_restart(); //Reiniciala comunicación I2C
        i2c1_driver_TXData(0xD1);
        i2c1_driver_startRX();
        sec= i2c1_driver_getRXData();
        
//        (dia>>4)+0x30;
//        (dia & 0x0F)+0x3;
        
        
        
    }
}
/**
 End of File
*/