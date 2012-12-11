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


int val = 0;
void delay();
void i2c_init();
int i2cBuffer[10];


int main(int argc, char** argv) {
    TRISD = 0;
    i2c_init();
    PORTD = 0;
    loop:
       PORTD = i2cBuffer[0];
    delay();
    goto loop;


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
    TRISC6 = 1;
    TRISC7 = 1;
    SSPEN = 1;
    CKE = 0;
    SMP = 0;
    CKP = 1;

    SSPM0 = 0;
    SSPM1 = 1;
    SSPM2 = 1;
    SSPM3 = 1;

    SSPIE =1;

    SSPADD = 0b10100100;
    PEIE = 1;
    GIE = 1;
    INTE = 1;
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

 

    char ssptemp = SSPSTAT & 0b00100000;
    if (val == 10)
        val = 0;

    if ((SSPSTAT & 0b00100000) == 0b00100000){ // D_A bit high, data in buffer
        //if (SSPBUF == SSPADD)
        //    SSPBUF =0;
       // else
            i2cBuffer[val] = SSPBUF;
            val++;
    }
    else{ // D_A bit clear, addr in buffer
        SSPBUF = 0;
    }

    
   SSPIF = 0;
   //val++;
   //PORTD = i2cBuffer[val];
}


