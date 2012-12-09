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


void main()
{




}


void Initialise()
{
    BeginPWM();
}