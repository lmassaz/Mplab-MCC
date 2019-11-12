
#include "mcc_generated_files/mcc.h"
uint8_t sec, min, hora;
uint8_t dia, mes, anio;

char Hora[] = "105845";
char Fecha[] = "200319";

//
//char Dec2BCD (char val)
//{
//  char res;
//  res = (val/10) << 4;
//  res = res | (val % 10);
//  return res;
//}


//void convertirHora(void){
//    
//    for(uint8_t i=0; i<7; i++){
//        Hora[i] &= 0x0F;
//    }
//    hora = ((Hora[0]<<4)+ Hora[1]);
//    min = ((Hora[2]<<4)+ Hora[3]);
//    sec = ((Hora[4]<<4)+ Hora[5]);
//}
//
//void convertirFecha(void){
//    
//    for(uint8_t i=0; i<7; i++){
//        Fecha[i] &= 0x0F;
//    }
//    
//    dia = ((Fecha[0]<<4)+ Fecha[1]);
//    mes = ((Fecha[2]<<4)+ Fecha[3]);
//    anio = ((Fecha[4]<<4)+ Fecha[5]);
//}
//
//primer valor
unsigned char MSB(unsigned char x)
{
return ((x >> 4) + 0x30);
 }
//segundo valor
unsigned char LSB(unsigned char x)
 {
 return ((x & 0x0F) + 0x30);
}
//
////void BCDtoDecimal (char val)
////{
////  char res;
////  res = (val & 0x0F) + ((val & 0xF0)>>4)*10;
////  return res;
////}
//
//int BCD_2_DEC (int to_convert) 
//{ 
//   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
//}


//void enviar_hora(void)
//{
//   i2c1_driver_start(); //inicia la comunicación i2c
//    i2c1_driver_TXData(0xD0);
//    i2c1_driver_TXData(0x00);
//    i2c1_driver_TXData(sec);
//    i2c1_driver_TXData(min);
//    i2c1_driver_TXData(hora);
//    i2c1_driver_stop(); 
//}
//
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
    
    i2c1_driver_TXData(0xD1);  //Dirección i2c lectura
    i2c1_driver_startRX();  
    
    sec= i2c1_driver_getRXData(); //resultado en BCD
    unsigned int vHora = MSB(sec);
    unsigned int vvHora= LSB(sec);
//     Hora[2]= MSB(min);
//     Hora[3]= LSB(min);
//     Hora[4]= MSB(hora);
//     Hora[5]= LSB(hora);
    printf(" %c ",vHora);
    printf(" %c ",vvHora);
    printf(" : ");
    
//    i2c1_driver_sendACK; //envío condición de ACK para decirle al esclavo que envie el siguiente dato (es decir  la posición 01)
    
//    min= i2c1_driver_getRXData();        
//    i2c1_driver_sendACK;
//    
//    hora= i2c1_driver_getRXData();
    i2c1_driver_sendNACK();  //condición de no ACK para que no siga mandando
    i2c1_driver_stop();
        
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
         
    printf("comunicación serial \r\n");
      
//    i2c1_driver_setAddr(0xD0);

//    convertirHora(); 
    //enviar_hora();
    
//    convertirFecha();
    //enviar_fecha();
    
  // printf("escritura exitosa  \r\n");
     
    while (1)
    {
     leer_hora();
 //    printf("Segundos : ", Hora);
////    printf(Hora);
   
    printf("\r\n");
    
     
     __delay_ms(1000);
     
    }
}
/**
 End of File
*/