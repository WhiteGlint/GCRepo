/* 
 * File:   encodermain.c
 * Author: Alan
 *
 * Created on February 14, 2013, 5:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f917.h>  //Include 16F917 header file, for all processor-specific declarations
#include <htc.h>  // htc.h necessary for PIC16F917 Configuration Bit Settings

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_ON & FCMEN_OFF);

// Function Prototypes
void Initialise();



/*
 * 
 */
int main()
{
    // Configure TMR1
    INTCON = 0;         // interrupts disabled
    CMCON1 = 0x02;      // related to gating for TMR1; shouldn't matter
    T1CON = 0b00000110; // no gating, prescale 1:1, external clock, tmr off
                        //  no sychronization

    TRISD = 0;          // PORTD LEDs as outputs

    // Clear timer
    TMR1H = 0;
    TMR1L = 0;

    while (1)
    {
        T1CONbits.TMR1ON = 1;       // turn timre on
        PORTD = TMR1L;              // set LEDs to lower 8 bits of timer
    }






    return 1;
}

