/*
 * File:   newmain.c
 * Author: Josh
 *
 * Created on November 12, 2012, 6:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <htc.h>
#include <pic16f917.h>
//#include <i2c_test.cpp>



__CONFIG(FOSC_EXTRCCLK & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_ON & IESO_ON & FCMEN_ON);



void delay();
void i2c_init();
int i2cBuffer = 99;

int main(int argc, char** argv) {

    i2c_init();
    
    TRISD = 0b00000000;

   // for (int i = 0; i < 256; i++){
    while(1 == 1){
        PORTD = i2cBuffer;
       // delay();
    }
    //}

    return (EXIT_SUCCESS);
}

void delay(){

    for (int d = 0; d < 2000; d++){
        NOP();
        NOP();
        NOP();
    }
}

void i2c_init(){
        SSPCON = 0b00110110;
        SSPADD = 0x02;
        SSPSTAT = 0b00000000;
        SSPIE = 1;
        PEIE = 1;
        GIE = 1;

}



void interrupt isr(){

/*
;---------------------------------------------------------------------
SSP_Handler
;---------------------------------------------------------------------
; The I2C code below checks for 5 states:
;---------------------------------------------------------------------
; State 1: I2C write operation, last byte was an address byte.
; SSPSTAT bits: S = 1, D_A = 0, R_W = 0, BF = 1
;
; State 2: I2C write operation, last byte was a data byte.
; SSPSTAT bits: S = 1, D_A = 1, R_W = 0, BF = 1
;
; State 3: I2C read operation, last byte was an address byte.
; SSPSTAT bits: S = 1, D_A = 0, R_W = 1 (see Appendix C for more information)
;
; State 4: I2C read operation, last byte was a data byte.
; SSPSTAT bits: S = 1, D_A = 1, R_W = 1, BF = 0
;
; State 5: Slave I2C logic reset by NACK from master.
; SSPSTAT bits: S = 1, D_A = 1, BF = 0, CKP = 1 (see Appendix C for more information)
;
;----------------------------------------------------------------------
*/

 

    char ssptemp = SSPSTAT & 0b00101101;
   /*
    switch(ssptemp){
        case 0b00001001:
            // State 1, master write addr
            SSPBUF = 0; // clear buffer without a care in the world.
            break;
        case 0b00101001:
            // State 2, master write data byte
            i2cBuffer = SSPBUF;
            break;
        case 0b00001100:
            // State 3, master read addr
            SSPBUF = 131; // HARDCODED TEST VALUE TO RETURN TO MASTER
            break;
        case 0b00001101:
            // Also State 3
            SSPBUF = 131; // HARDCODED TEST VALUE TO RETURN TO MASTER
            break;
        case 0b00101100:
            // State 4, master read data
            SSPBUF = 141; // HARDCODED TEST VALUE TO RETURN TO MASTER
        case (0b00101000):

            if (CKP == 1){
            // State 5, master send NACK
            }
            break;
        case (0b00101100):

            if (CKP == 1){
            // Also State 5, master send NACK
            }
            break;
        
        default:
            // ERROR STATE
            while(1==1){
            PORTD = SSPBUF;

            }
            break;
    }
*/
  if (ssptemp == 0b00001001){ // State 1
    // State 1, master write addr
      i2cBuffer = SSPBUF;
   // SSPBUF = 0; // clear buffer without a care in the world.
  }
  else if (ssptemp == 0b00101001){
    // State 2, master write data byte
    i2cBuffer = SSPBUF;
  }
  else if (ssptemp == 0b00001100){
    // State 3, master read addr
    SSPBUF = 131; // HARDCODED TEST VALUE TO RETURN TO MASTER
  }
  else if (ssptemp == 0b00101100){
    // State 4, master read data
    SSPBUF = 141; // HARDCODED TEST VALUE TO RETURN TO MASTER
  }
  else if (ssptemp == 0b00101000){
    if (CKP == 1){
        // State 5, master send NACK
    }
  }
  else{
   //ERROR CASE
      NOP();

  }

  //SSPSTAT = 0;
}


