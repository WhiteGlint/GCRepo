/* Encoder Library
 *
 * Dave Mine
 * Alan Hale III
 * 
 * 2013/2/20
 *
 * GCRobotics
 *
 */



#include <pic16f917.h>

//Varibles
int	x1, t1, v1,
	x2, t2, v2, // t2 equals time @ measurement of x2
	xerr, xerravg, verr, verravg, // we don't need an xerr or xerravg (the comp worries about that stuff)
	vgoal, // passed down to us
	time = 0,
	a;

// SET UP HIGH LEVEL LANGUAGE TO STOP BEFORE CHANGING DIRECTIONS!!

void TMR0_ISR()
{
    time += 256;
    T0IF = 0;
}



void TMR1_ISR()
{
    x1 = x2;
    t1 = t2;
    v1 = v2;

    x2 = 65525;
    t2 = time + TMR0; // time from previous overflows + non-measured time
    v2 = ((x2-x1)/(t2-t1));

    a = ((v2-v1)/(t2-t1));

    x2 = 0;
    time = 0;
}



void ManualMeasure() // basicly the TMR1 ISR, but on command
{
    x1 = x2;
    t1 = t2;
    v1 = v2;

    x2 = TMR1;
    t2 = time + TMR0;
    v2 = ((x2-x1)/(t2-t1));

    a = ((v2-v1)/(t2-t1));

    //resetting everything to keep from an untimely ISR
    x2 = 0;
    time = 0;
    TMR0 = 0;
    TMR1 = 0;
}
