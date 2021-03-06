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

//User-defined libraries
#include "pwmlib.h"  //allows for use of PWM (use double quotes for user defined)
#include "i2cSlave.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_ON & FCMEN_OFF);

void Initialise();
void CalcPulse(int speed);
void directionInit();
int parseDirectionPWM();
void setDirection(int dir);

//Test Functions
void delay(int length);

void interrupt isr();       //for testing I2C interrupts

//Global Variables
//int i2cBuffer[10];          //buffer for holding incoming data
//int val = 0;                //refers to i2cBuffer index
int setSpeed = 0;              //register holding the currently desired speed
int dc;

int main()
{
   // unsigned char dc;
    int direction;
    Initialise();
    OPTION_REG = 0b10100000;
    TRISA = 0x0000;
    TRISD = 0;
    TMR0 = 0;
   // i2cInit(0x010);
    while(1)                         // forever
    {
        /*
         * PWM resolution is 10 bits
         * don't use last 2 less significant bits CCPxCON,
         * so only CCPRxL have to be touched to change duty cycle
         */
        PORTD = 0xFF;
        for(dc = 0 ; dc <= 10 ; dc++)
        {
            CalcPulse(dc);
            delay(6000) ;
        }
        PORTD = 0x00;
        for(dc = 10; dc >= 0 ; dc--)
        {
            CalcPulse(dc);
            delay(6000) ;
        }
        delay(6000);

        if (PORTBbits.RB3 == 0)
            PORTBbits.RB3 = 1;
        else
            PORTBbits.RB3 = 0;

    }//*/
    
 /*   while (1)
    {
        /*setDirection(i2cDirection);
        SetPulse(i2cSpeed);
        PORTD = i2cSpeed;/
        SetPulse(150);
        PORTD = TMR0;
    }//*/

    return 1;       // standard ending for an "int main"
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
    i2cInit(0x10);
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




//Interrupt Service Routine
//  Currently configured to handle only I2C operations
void interrupt isr(){
    i2cIsrHandler();
    
}



//Configures the bit that controls the direction of the
//  rotation of the motor; 0 is forward, 1 is reverse
void directionInit()
{
    TRISB3 = 0; //set as output
    PORTBbits.RB3 = 1; //default to forward
}



//Sets the direction bit equal to 0 or 1 and sets the
//  global variable "setSpeed" equal to proper speed
int parseDirectionPWM()
{
    setSpeed = i2cBuffer[1] & 0b01111111;

    if (i2cBuffer[1] > 0)
    {
        return 1;  //value negative, means go in reverse
    }
    else
        return 0;
}



//Sets the direction according to the direction value
//  0 is forward, 1 is reverse
void setDirection(int dir)
{
    if (dir == 0)
        PORTBbits.RB3 = 0;  //if 0, set to 0 so that motor is forward
    else if (dir == 1)
        PORTBbits.RB3 = 1;  //if 1, set to 1 so motor is reverse
    else
        PORTBbits.RB3 = 0;  //default to motor forward
}