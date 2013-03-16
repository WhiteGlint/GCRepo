/* Alan Hale III
 * GCRobotics
 * 2013/3/5
 *
 * I2C Library Header File
 * Functions necessary for proper I2C communication and interrupt handling
 */

#ifndef I2CLIB_H
#define	I2CLIB_H

#ifdef	__cplusplus
extern "C" {
#endif


    // Initialises all the necessary registers for proper I2C communication
    void BeginI2C(char address);


    // This function, upon a read interrupt, takes velocity and turns it
    //  into direction and speed.  Converts speed from revolutions per
    //  second into cycles per second.  Returns target speed and direction.
    void SetVelocity(int *direction, int *speed, int cycles_per_rev_ratio);


    // This function, upon write interrupt, writes the time and counts out
    //  to I2C
    void ReturnData(int *t_h, int *t_l, int *c_h, int *c_l);


    // Upon detection of an interrupt, this function determines what command
    //  the PIC has been given, whether a read or a write.  It sets flags
    //  according to what it finds.
    void I2C_ISR_Handler(int *flag);





#ifdef	__cplusplus
}
#endif

#endif	/* I2CLIB_H */

