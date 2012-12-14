/*2012/12/08
 *
 *Geneva College Robotics
 *
 *Pulse Width Modulation:  Module for testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f917.h>  //Include 16F917 header file, for all processor-specific declarations
#include <htc.h>  // htc.h necessary for PIC16F917 Configuration Bit Settings
__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_ON & FCMEN_OFF);

//User-defined libraries
#include "pwmlib.h"  //allows for use of PWM (use double quotes for user defined)

/**********/
void Initialise();
void CalcPulse(int speed);
void directionInit();
unsigned char parseDirectionPWM();

//Test Functions
void delay(int length);
void i2c_init();            //for testing I2C
void interrupt isr();       //for testing I2C interrupts

//Global Variables
int i2cBuffer[10];          //buffer for holding incoming data
int val = 0;                //refers to i2cBuffer index
int setSpeed = 0;              //register holding the currently desired speed


void main()
{
   // unsigned char dc;
    unsigned char direction;
    Initialise();

/*    while(1)                         // forever
    {
        /*
         * PWM resolution is 10 bits
         * don't use last 2 less significant bits CCPxCON,
         * so only CCPRxL have to be touched to change duty cycle
         /
        for(dc = 8 ; dc <= 10 ; dc++)
        {
            CalcPulse(dc);
            delay(2000) ;
        }
        for(dc = 10; dc >= 8 ; dc--)
        {
            CalcPulse(dc);
            delay(2000) ;
        }
    }//*/

    while (1)
    {
        direction = parseDirectionPWM();
        CalcPulse(setSpeed);
        PORTD = setSpeed;
    }


}



void delay(int length)
{
    for (int x=0; x < length; x++)
    {
        x++;
        x--;
    }
}


//Any PIC initialization that is necessary goes here
void Initialise()
{
    BeginPWM();
    i2c_init();
    directionInit();

    TRISD = 0;  //set up onboard LEDs as
    PORTD = 0;  //  output for testing
}


//Function that converts 0-10 to PWM percentage in increments of 10%
//  and then sets that PWM signal
void CalcPulse(int speed)
{
    int pulse = speed*255/10;
    SetPulse(pulse);
}


//Configures SSP registers for I2C operation
// written by Josh G.
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
    SSPM3 = 0;

    SSPIE =1;

    SSPADD = 0b00001110;
    PEIE = 1;
    GIE = 1;
    INTE = 1;
    i2cBuffer[1] = 0;
}



//Interrupt Service Routine
//  Currently configured to handle only I2C operations
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
    if (val == 2)  //FOR TESTING:  want to use only every other data bit
       val = 0;    //  since we are not concerned with read/write at this point

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



//Configures the bit that controls the direction of the
//  rotation of the motor; 0 is forward, 1 is reverse
void directionInit()
{
    TRISB3 = 0; //set as output
    PORTBbits.RB3 = 0; //default to forward
}



//Sets the direction bit equal to 0 or 1 and sets the
//  global variable "setSpeed" equal to proper speed
unsigned char parseDirectionPWM()
{
    setSpeed = i2cBuffer[1]&01111111;

    if (i2cBuffer[1] > 0)
    {
        return 1;  //value negative, means go in reverse
    }
    else
        return 0;


}