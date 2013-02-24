/* 
 * File:   primarymain.c
 * Author: Alan
 *
 * Created on February 20, 2013, 7:40 PM
 *
 * GCRobotics Primary PIC main function
 * Controls the aspects of the PICs that are in charge of
 *  controlling the motors and sending feedback to the CPU,
 *  namely the PWM, I2C, and Encoder functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f917.h>  //Include 16F917 header file, for all processor-specific declarations
#include <htc.h>  // htc.h necessary for PIC16F917 Configuration Bit Settings
#include "pwmlib.h"  //allows for use of PWM (use double quotes for user defined)

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_ON & FCMEN_OFF);


void Initialise();
void CalcPulse(int speed);
void setDirection(int dir);

//Test Functions
void delay(int length);

void interrupt isr();       //for testing I2C interrupts

//Global Variables
int setSpeed = 0;              //register holding the currently desired speed



int main()
{
    Initialise();
    // Configure TMR1
    INTCON = 0;         // interrupts disabled
    CMCON1 = 0x02;      // related to gating for TMR1; shouldn't matter
    T1CON = 0b00000110; // no gating, prescale 1:1, external clock, tmr off
                        //  no sychronization

    TRISD = 0;          // PORTD LEDs as outputs

    // Clear timer
    TMR1H = 0;
    TMR1L = 0;
    T1CONbits.TMR1ON = 1;       // turn timer on

    while (1)
    {
        CalcPulse(1);
        PORTD = TMR1;
    }

    return 1;       // standard ending for an "int main"
}


// Test function that allows for a certain amount of delay
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

    TRISB3 = 0; //set as output
    PORTBbits.RB3 = 0; //default to forward

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


