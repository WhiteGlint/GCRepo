/*******************************************************************************
 *  Project:            GCRobtics Team
 *
 *  Original Creator:   Alan Hale
 *                          2013
 *  Modified by:        Quang Nguyen
 *                          2013
 *
 *  Function:           This code is code responsible for handling all the
 *                      PIC16F887s. These PICs will be used for motor control
 *                      and odometry feedback. Communication between the PICs
 *                      and the Arduino will be accomplish by using the
 *                      I2C communication protocol. The user will need to change
 *                      the name of the address to correspond to the correct PIC's
 *                      address
 *
 *  Pins used:
 *                      RB3 : Tells the motor which direction to operate
 *                      RB5 : Tells which direction the motor is currently running.
 *                              This is accomplished thorough the phase of the 2 encoders
 *                              and a D-flip flop
 *                      RC1 : This pin contains the PWM output that controls the motor's
 *                              speed
 *                      RC3 : Use for I2C
 *                      RC4 : Use for I2C
 *
 *  Peripherals used:
 *                      TIMER0:
 *                          This is used to determined how often the PID calculation
 *                          is performed. This timer is set up overflow every 10 ms
 *
 *                      TIMER1:
 *                          This is used to keep track of the encoder count of the motor
 *
 *                      CCP2:
 *                          This is used to generate the PWM signal needed to control the
 *                          motor. The output of the PWM signal will be on RC1
 *
 *                      PORTB Change:
 *                          This is used to detect direction change in the motor.
 *
 * Accomplished so far:
 *      - PID has been tuned and tested to work correctly and reliably
 *      - I2C is working properly and reliably
 *      - Encoder counts for odometry seem to be working pretty well so far
 *      - PWM hasn't failed yet so we can assume we are good in this also
 *
 * Future work:
 *      - Make use the PORTD LEDs.
 *          Right now, it is just there to indicate that the PIC is actually on.
 *          Can definitely be use for debugging purposes.
 *      - Make better use of I2C "type" byte.
 *          Right now, only 0x00 is being implemented. Could use "type" byte
 *          to pass different data if needed.
 *      - Maybe improve on PID somehow. Like I said before, it is working
 *          pretty  well so far.
 *      - Structure and comment the code more. The code was in a pretty terrible
 *          condition when I first got it. Hopefully I put enough comments on here
 *          that you guys can have a rough idea of what is happening
 *
 ********************************************************************************/



/*******************************************************************************
 *
 *                      Library includes
 *
 *******************************************************************************/

#include <pic16f887.h>                                  // 16F887 header file, for all
                                                        //  processor-specific declarations
#include <htc.h>                                        // htc.h necessary for PIC16F917 Configuration
                                                        //  Bit Settings
//#include <stdlib.h>

        #ifndef _XTAL_FREQ
	#define _XTAL_FREQ 	20000000
	#endif

#include "pwmlib887.h"                                  // allows for use of PWM module
                                                        //  (use double quotes for user-defined)
#include "enclib887.h"                                  // allows for use of Encoder module
#include "i2cSlave887.h"                                // allows for use of I2C module

/*******************************************************************************
 *
 *                       Configuration Bits
 *
 ******************************************************************************/

// Configuration bit settings
// Use 20MHz external oscillator --> FOSC_HS
// Turn on external oscillator --> FOSC_HS
// NOTE:  MCLRE must be set to ON because of this family of PIC (887.
//  Must be used in conjunction with the MCLR pin via weak pullup.
//  See section 14.2.2, page 211, of the 887 datasheet.

__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & MCLRE_ON &
        CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR40V & WRT_OFF);



/*******************************************************************************
 *
 *                      Constant Declarations
 *
 *******************************************************************************/

//  Pre-processor definitions that specify an individual PIC.  That is, all
//  the main code can be exactly the same, from PIC to PIC for the robot,
//  depending on the motor position (front left motor, for example), only
//  these definitions will need to change.
//
//  Direction:
//      -   Uncomment the block of code that corresponds to the side of the
//      motor.
//      -   Comment the block of code that corresponds to the side of the
//      motor that is not being used
//      -   Uncomment the proper "I2C_ADDRESS" that corresponds to the
//      proper PIC.
//      -   Make sure the address for unused PIC is commented.
//
//      This configuration allows for the same code to be used even though
//      motor direction and PIC's addresses are not the same

/************** Right side PICs **************/
/////////////// PIC's address for I2C //////////////////
 //#define I2C_ADDRESS 0x02        // FRONT RIGHT motor address
 #define I2C_ADDRESS 0x04        // BACK RIGHT motor addres

/////////////// PIC specific depending on wheel orientation //////////
 #define MOTOR_DIRECTION i2cDirection
 #define FORWARD     1
 #define BACKWARD !FORWARD
**********************************************/

<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
/************** Left side PICs **************/
=======
/************** Left side PICs **************
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c
          /////////////// PIC's address for I2C //////////////////
//#define I2C_ADDRESS 0x06        // BACK LEFT motor address
#define I2C_ADDRESS 0x08        // FRONT LEFT motor address

          /////////////// PIC specific depending on wheel orientation //////////
 #define MOTOR_DIRECTION i2cDirection
 #define FORWARD     0
 #define BACKWARD !FORWARD
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
/**********************************************/

=======
**********************************************/
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c

#define PWM_OFFSET  80          // Motor won't spin until a certain amount of voltage
                                // is applied to it.
#define FLAG_ADDRESS 0xAA       // Address for user defined flag register
                                //  According sto datasheet, 0xAA is free

// Coefficients for PID
#define KP 3.5                  // PID P coefficient
#define KI 1.7                  // PID I coefficient
#define KD 1.7                  // PID D coefficient

<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
/*******************************************************************************
 *
 *                      Global Variable Declarations
 *
 *******************************************************************************/
//          Yes, I realized that I shouldn't use global variable...What can I
//          say...I'm lazy...
=======
// Function Prototypes
void Initialise();              // contains all initializing functions
void interrupt isr();           // general interrupt vector
void updateOdometry();
void updateEncoder();

void setDirection(int dir);     // Sets the direction bit (PORTB bit 3)

>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c

int Target              = 0;                // target speed passed down from CPU
int DirectionRead       = FORWARD;          // value read from encoder flip-flop used
                                            // to keep track of current direction
int TMR0OverflowCounter = 0;                // This will keep track of the number of times that
                                            // TMR0 has overflowed.
                                            // TMR0 is set to overflow at 10 ms so
                                            // 5 times of TMR0 overflow equal to 50 ms or 0.05 second.
                                            // This is how often our PID loop will run

  int OdometryCounts      = 0;              // TMR1 encoder counts --> passed to CPU
  int temp = 0, PreviousOdometryCounts = 0;

  int PID                 = 0;              // This will contain the result of PID algorithm
  int EncoderCounts       = 0;              // number of counts since last PID loop
  int PreviousEncoderCounts = 0;

  int Error               = 0;              // How far we from target speed
  int AccumulatedError    = 0;              // Sum of errors
  int DeltaError          = 0;              // Difference in current error and previous error
  int PreviousError       = 0;              // Well....self explained. haha
  int CurrentPwm          = 0;              // current pulse width pushed to PWM
                                                // can have a min of 0 and max of 255
  unsigned int LastPidCount        = 0;
  unsigned int LastOdomCount       = 0;

// Register that holds flags that are set in software upon determination of
//  the cause of an interrupt.  These flags are continuously checked in the
//  main program.  Some may be unimplemented.
unsigned char FLAG @ FLAG_ADDRESS;
bit I2C     @ ((unsigned)&FLAG*8)+0;    // I2C flag
bit T0      @ ((unsigned)&FLAG*8)+1;    // TMR0 flag
bit T1      @ ((unsigned)&FLAG*8)+2;    // TMR1 flag
bit DIR     @ ((unsigned)&FLAG*8)+3;    // Direction flag
bit ERR     @ ((unsigned)&FLAG*8)+4;    // H-Bridge Error flag
union {
    struct {
        unsigned    I2C     : 1;
        unsigned    T0      : 1;
        unsigned    T1      : 1;
        unsigned    DIR     : 1;
        unsigned    ERR     : 1;
        unsigned            : 3;
    };
}F @ FLAG_ADDRESS;

/*******************************************************************************
 *
 *                      Function Prototype
 *
 *******************************************************************************/
void Initialise();              // contains all initializing functions
void interrupt isr();           // general interrupt vector
void updateData(int c);         // takes in most recent count measurements and
                                // adds them to current total
void setDirection(int dir);     // Sets the direction bit (PORTB bit 3)

int updatePid();
void updateOdometry();

/*******************************************************************************
 *
 *                      Main Function
 *
 *******************************************************************************/
int main() {
   // BEGIN
    Initialise();                       // Function to do initial setup
    while(1)                            // Infinite loop
    {
        PORTD = 0xff;                   // This is just to indicate that PIC is running
                                            // this can be change for better use of debugging
        if (F.I2C == 1)                 // I2C message was received
        {
            // Perform some I2C operation
            // If read, reset Data and PID information
            // Perform operation for Target

            Target = i2cTarget;             // Receive velocity from CPU
            setDirection(MOTOR_DIRECTION);  // Set direction of the motor to the direction
                                                // sent from CPU
//            OdometryCounts = 0;             // Reset the variables for PID and odometry
            if (i2cTarget == 0)             // This to ensure a sharp stop
            {
                AccumulatedError = 0;
                setPWM(0);
            }
            // Clear Flag
            F.I2C = 0;
        }
        if (F.DIR == 1)
        {
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
//            // Update counts before updating direction
//            encUpdate(&EncoderCounts);                  //This will put the value of TMR1 into counts and then clear TMR0
//            updateData(EncoderCounts);			// This will add counts to OdometryCounts (which is the total distanced traveled so far.)

             updateOdometry();
=======
            // Update counts before updating direction
            updateOdometry();
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c

            // Update direction
            DirectionRead = PORTBbits.RB5;

            // Clear Flag
            F.DIR = 0;
        }

        //  PID Loop occurs at regular time intervals
        if (F.T0 == 1)
        {
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
//            // Update to most recent encoder counts
//            encUpdate(&EncoderCounts);
//            updateData(EncoderCounts);

            EncoderCounts = updatePid();

/****** I'm keeping this in here just incase I change my mind and want to implement ***
*        it later on. PID is perfectly function right now
//            if ((DirectionRead != MOTOR_DIRECTION)&& (Target != 0))
//            {
//                intSecondComplement(&EncoderCounts);
//                PORTBbits.RB3 = DirectionRead;
//            }
/**************************************************************************************/
=======
            // Update to most recent encoder counts
            updateEncoder();
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c

/*************** Calculate stuff for PID **********************************************/
            Error               = Target - EncoderCounts;
            AccumulatedError    = AccumulatedError + Error;
            DeltaError          = Error - PreviousError;
            PreviousError       = Error;

            // Set bounds for the accumulated error ///
            if (AccumulatedError > 10000)
                AccumulatedError = 10000;
            else if (AccumulatedError < -10000)
                AccumulatedError = -10000;
            // Performing the actual PID
            PID = (Error * KP) + (AccumulatedError * KI) + (DeltaError * KD );     // Performing PID calculation
                                  //Note: Even through the variable types are
                                  // different, the result should be the correct
                                  // value of with the type of int
            if (Error != 0)         // If no error
            {
                CurrentPwm = PID + PWM_OFFSET;
                if (CurrentPwm >= 255)      // PWM should be between 0 - 255
                    CurrentPwm = 255;
                else if (CurrentPwm < 0)
                    CurrentPwm = 0;
                setPWM(CurrentPwm);     // set new PWM
            }
            F.T0 = 0;                   // reset TMR0 flag
        } // end PID Loop

    } // end while(1)

    return 1;                   // standard ending for an "int main"
}

/*******************************************************************************
 *
 *                      Initialize Function
 *
 *******************************************************************************/

void Initialise()
{
    FLAG    = 0;            // Clear everything first
    beginPWM();             // initialize PWM associated registers
    setPWM(0);              // Set PWM to 0 until Arduino say otherwise
    i2cInit(I2C_ADDRESS);   // initialize I2C
    PEIE    = 1;            // generic peripheral interrupts enabled
    PIE1    = 0b00001000;   // I2C interrupts enabled
    SSPIF   = 0;            // Clear I2C flag
    GIE     = 1;            // Enable all interrupts

    beginEncoder();         // initialize encoder registers (TMR0 & TMR1)
    PIE2    = 0;            // other peripherals disabled

// Clear and Initate TIMER registers
    TMR1    = 0;
    TMR0    = 61;           // Preset TMR0 so that it will overflow every 10 ms
// Configure interrupts
    RBIE    = 1;            // PORTB interrupts enabled
    T0IE    = 1;            // TMR0 interrupts enabled
    TMR1IE  = 1;            // TMR1 interrupts enabled
    // Clear flags
    RBIF    = 0;
    T0IF    = 0;
    TMR1IF  = 0;
// Turn on I/Os
    TRISB   = 0b11110111;
    PORTBbits.RB3 = FORWARD;    // default to forward
    TRISD   = 0;
    PORTCbits.RC1 = 0;
}

/*******************************************************************************
 *
 *                      Interrupt Service Routine
 *
 *******************************************************************************/

void interrupt isr()
{
    if (SSPIF == 1)             // interrupt is I2C related
    {
        // Update counts before updating direction
        encUpdate(&EncoderCounts);                  //This will put the value of TMR1 into counts and then clear TMR0
        updateData(EncoderCounts);			// This will add counts to OdometryCounts (which is the total distanced traveled so far.)

        F.I2C = 1;              // set i2c flag bit
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
        // Update to the newest odometry incase the master request the odometry data
        updateOdometry();

=======
        //Update OdometryCounts
        updateOdometry();
        //Go to the i2cisrhandler
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c
        i2cIsrHandler();	// interrupt flag was cleared in this function
    } else if (T0IF == 1)       // overflow of timer 0
    {                           // TMR0 overflows every 10 ms
        TMR0OverflowCounter++;
        if (TMR0OverflowCounter == 5){   // 5 times of TMR0 overflow = 50 ms or 0.05 second
            F.T0 = 1;				// set T0 flag bit
            TMR0OverflowCounter = 0;
        }
        T0IF = 0;
    } else if (TMR1IF == 1)     // overflow of counts; probably never happens
    {		// Only 2 bytes of data are being sent through I2C so therefore, the
			// overflown is not taken into account right now
        TMR1IF = 0;
    } else if (RBIF == 1)       // PORTB change
    {
        if (RB5 != DirectionRead)    // verify that it was a direction change
        {
            F.DIR = 1;          // set direction flag bit
        } else                  // Error, probably H-Bridge related
        {
;                               // Not sure if we need to do anything right now
        }
        RBIF = 0;
    } else                      // Any other interrupt error
    {
;                               // Not sure if we need to do anything right now
    }
}       // end interrupt function
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
/*******************************************************************************
 *
 *                      Other Functions
 *
 *******************************************************************************/
// Takes in variables holding the most recent time read and count read and adds
//  (or subtracsts, depending on the direction) those to the current totals
void updateData(int c)
=======


void updateEncoder()
>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c
{
    // if TMR1 hasn't overflown yet
    if (PreviousEncoderCounts <= TMR1)
         EncoderCounts = TMR1 - PreviousEncoderCounts;
    // if TMR1 has overflown
    else EncoderCounts = ( 65535 - PreviousEncoderCounts)+ 1 + TMR1;
    // Update PreviousOdomertryCounts
    PreviousEncoderCounts = TMR1;
}

void updateOdometry()
{
    int Temp;
    // if TMR1 hasn't overflown yet
    if (PreviousOdometryCounts <= TMR1)
         Temp = TMR1 - PreviousOdometryCounts;
    // if TMR1 has overflown
    else Temp = ( 65535 - PreviousOdometryCounts)+ 1 + TMR1;
    // Update PreviousOdomertryCounts
    PreviousOdometryCounts = TMR1;

    //Update Odometry
    if (DirectionRead == FORWARD)
    {
        OdometryCounts += Temp;
    } else
    {
        OdometryCounts -= Temp;
    }
}

int updatePid()
{
    unsigned int CurrentPidCount = TMR1;
    int Result = 0;
    // TMR1 overflowed so we have to compensate for it
    if ( CurrentPidCount < LastPidCount )
    {
        CurrentPidCount += (65535 - LastPidCount);
        LastPidCount = 0;
    }
    Result = CurrentPidCount - LastPidCount;
    return Result;
}

void updateOdometry()
{
    unsigned int CurrentOdomCount = TMR1;

    // TMR1 overflowed so we have to compensate for it
    if ( CurrentOdomCount < LastOdomCount )
    {
        CurrentOdomCount += (65535 - LastOdomCount);
        LastOdomCount = 0;
    }
    // Now updata the total odometry count
    if (DirectionRead == FORWARD)
    {
        OdometryCounts += (CurrentOdomCount - LastOdomCount);
    } else
    {
        OdometryCounts -= (CurrentOdomCount - LastOdomCount);
    }
}

// Sets the direction according to the direction value
void setDirection(int dir)
{
    if (dir == 0)          // if I2C passes down direction of 0, it is forward
        PORTBbits.RB3 = FORWARD;        // forward
    else if (dir == 1)
        PORTBbits.RB3 = BACKWARD;       // reverse
    else
        PORTBbits.RB3 = FORWARD;        // default to motor forward
}
<<<<<<< HEAD:Low Level Code/GCR - Primary PIC Program v887.X/MainProgram.c
=======

>>>>>>> origin/Odometry-fix:Low Level Code/GCR - Primary PIC Program v887.X/primary887main.c
