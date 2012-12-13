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


//Test Functions
void delay(int length);


void main()
{
    unsigned char dc;
    Initialise();


    while(1)                         // forever
    {
        /*
         * PWM resolution is 10 bits
         * don't use last 2 less significant bits CCPxCON,
         * so only CCPRxL have to be touched to change duty cycle
         */
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

 //   while(1)
   //     CalcPulse(10);



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
}


//Function that converts 0-10 to PWM percentage in increments of 10%
//  and then sets that PWM signal
void CalcPulse(int speed)
{
    int pulse = speed/10*255;
    SetPulse(pulse);
}