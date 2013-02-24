/* 
 * File:   enclib.h
 * Author: Alan
 *
 * Created on February 6, 2013, 9:12 PM
 */

#ifndef ENCLIB_H
#define	ENCLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Function that reads TMR0 and keeps track of current
    //  number of counts (encoder cycles).  It is static so that
    //  the distance value is saved between calls.  Every time it
    //  is asked to read from TMR0, it resets it.
    static int GetDistance();

    // This function reads TMR1 and keeps track of the current
    //  time since the last call.  Resets TMR1 every time it
    //  is read from.
    static int GetTime();

    // Calculates the current speed based on the most recent
    //  distance and time measurements
    float CalcSpeed(int d, int t);

    // Calculates the current acceleration based on the difference
    //  between the current speed and the previous speed divided
    //  by the time in between speed readings
    float CalcAcceleration(float v2, float v1, int t);
        // where v2 is most recent velocity, v1 is next most, and
        //  t is the time in between those measurements

    // Measure direction.  Reads direction input pin [NEED PIN NAME]
    //  and determines if it is 0 for forward, 1 for reverse.
    int GetDirection();










#ifdef	__cplusplus
}
#endif

#endif	/* ENCLIB_H */

