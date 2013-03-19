/* Alan Hale III
 * GCRobotics
 * 
 * Created on February 20, 2013, 7:40 PM
 *
 * GCRobotics Primary PIC main function
 * Controls the aspects of the PICs that are in charge of
 *  controlling the motors and sending feedback to the CPU,
 *  namely the PWM, I2C, and Encoder functions.
 */

#include <pic16f917.h>          // 16F917 header file, for all
                                //  processor-specific declarations
#include <htc.h>                // htc.h necessary for PIC16F917 Configuration
                                //  Bit Settings
#include "pwmlib.h"             // allows for use of PWM module
                                //  (use double quotes for user-defined)
#include "enclib.h"             // allows for use of Encoder module
#include "i2cSlave.h"             // allows for use of I2C module

// Configuration bit settings
// Use 20MHz external oscillator --> FOSC_HS
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF &
        BOREN_OFF & IESO_ON & FCMEN_OFF);



// Pre-processor definitions that specify an individual PIC.  That is, all
//  the main code can be exactly the same, from PIC to PIC for the robot,
//  depending on the motor position (front left motor, for example), only
//  these definitions will need to change
#define I2C_ADDRESS 0x10        // I2C address; unique to specific PIC
#define FORWARD 0               // PIC specific depending on wheel orientation
#define BACKWARD !FORWARD       // ^
#define CYCLES_PER_REV 650      // Should be nearly the same for all PICs,
                                //  but again could vary across motors
#define PWM_FOR_RPS 125         // The PWM pulse width that is the closest
                                //  for achieving 1 revolution per second
#define FLAG_ADDRESS 0xAA       // Address for user defined flag register
                                //  According to datasheet, 0xAA is free
#define KP 1.0      // PID P coefficient
#define KI 1.0      // PID I coefficient
#define KD 1.0      // PID D coefficient
#define KPID 1.0    // PID cycle/s to PWM dampening factor



// Function Prototypes
void Initialise();              // contains all initializing functions
void interrupt isr();           // general interrupt vector
void UpdateData(int t, int c);  // takes in most recent time and count
                                //  measurements and adds them to current total
void setDirection(int dir);     // Sets the direction bit (PORTB bit 3)
int abs(int a, int b);          // Returns the absolute value of the difference
                                //  between two numbers

//Test Functions
void delay(int length);
void CalcPulse(int speed);
void delay1sec();



//Global Variables
int TARGET = 0;                 // target speed passed down from CPU
int DIRECTION = FORWARD;        // target derection passed down from CPU
int DIR_READ = FORWARD;         // value read from encoder flip-flop used
                                //  to keep track of current direction

//long TIME = 0;                  // time counted from TMR0 --> **don't need**
int COUNTS = 0;                // TMR1 encoder counts

/*int TIME_HIGH = 0;              // upper 16 bits of time counted from TMR0
int TIME_LOW = 0;               // lower 16 bits of time counted from TMR0
int COUNTS_HIGH = 0;            // upper 16 bits of TMR1 encoder counts
int COUNTS_LOW = 0;             // lower 16 bits of TMR1 encoder counts*/

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


//-----------------------------------------------------------------------------
// MAIN STARTS HERE -----------------------------------------------------------
int main()
{
    // Variables    
    int time = 0, counts = 0;       // These variables store the most recent
                                    //  reads of time and counts and assume
                                    //  that they are never > 65635
    int *t, *c;     // Pointers to the variables temps
    *t = time;
    *c = counts;
    int currentPWM = 0;             // Stores current pulse width pushed to PWM
    int v;                          // Stores currently measured cycles/s
    //!! may need to convert these from int to float in order to get accuracy
    int P, I, D, P_old = 0, PID;    // PID specific variables



    // BEGIN
    Initialise();

    TARGET = 30;
    SetPulse(0);

    while(1)
    {
        /*/ Some test code
        TMR1 = 0;
        SetPulse(75);
        for (P = 0; P < 10; P++)
            delay1sec();
        SetPulse(0);
        asm("nop");     //*/

        
        PORTD = TMR1;
        SetPulse(i2cSpeed);
        DIRECTION = i2cDirection;
        setDirection(DIRECTION);




        if (F.I2C == 1)
        {
            // Perform some I2C operation


            // If read, reset Data and PID information
//            TIME = 0;
            COUNTS = 0;
            I = 0;
            D = 0;
            P_old = 0;

            // Clear Flag
            F.I2C = 0;
        }

        if (F.DIR == 1)
        {
            // Update time and counts before updating direction
            EncUpdate(*t, *c);
            UpdateData(time, counts);

            // Update direction
            DIR_READ = RB5;

            // Clear Flag
            F.DIR = 0;
        }


        /*/ PID Loop (again assuming counts does not overflow)
        while (FLAG == 0)
        {
            // Update to most recent encoder time/counts
            EncUpdate(&time, &counts);
            UpdateData(time, counts);

//            PORTD = COUNTS;

            // Perform PID
            v = counts / time;          // calculate current speed
            P = abs(TARGET, v);         // calculate error
            I = I + (P / TIME);         // calculate integral error
            D = abs(P, P_old) / time;   // calculate differential error
            PID = (P * KP) + (I * KI) + (D * KD);   // calculate new output
            P_old = P;                  // save error for next time

            // Calculate new PWM by using ration to convert from cycles/s into
            //  PWM count.  Error check to make sure neither currentPWM or
            //  v (especially) is equal to 0.
            if (currentPWM == 0)
                currentPWM = 1;
            if (v == 0)
                v = 1;
            currentPWM = (KPID * PID * currentPWM) / v;    // CALCULATE NEW PWM

            PORTD = counts;
 //           SetPulse(currentPWM);       // set new PWM
            SetPulse(0);               // Test PWM value

            delay(50);
        } // end PID Loop               */

    } // end while(1)

    return 1;                   // standard ending for an "int main"
}   // END MAIN ---------------------------------------------------------------
//-----------------------------------------------------------------------------


// Any PIC initialization that is necessary goes here
void Initialise()
{
    FLAG = 0;
    BeginPWM();             // initialize PWM associated registers
    BeginEncoder();         // initialize encoder registers (TMR0 & TMR1)
    i2cInit(I2C_ADDRESS);   // initialize I2C

    // Configure interrupts
    PEIE = 1;               // generic peripheral interrupts enabled
    RBIE = 1;               // PORTB interrupts enabled
    T0IE = 0;               // TMR0 interrupts enabled      **DISABLED CURRENTLY**
    PIE1 = 0b00001001;      // I2C and TMR1 interrupts enabled
    PIE2 = 0;               // other peripherals disabled
    // Clear flags
    SSPIF = 0;
    RBIF = 0;
    T0IF = 0;
    TMR1IF = 0;
    // Enable all interrupts
    GIE = 1;

    TRISB = 0b11110111;
    PORTBbits.RB3 = FORWARD;    // default to forward

    TRISD = 0;
}


// Primary Interrupt vector
void interrupt isr()
{
    if (SSPIF == 1)             // interrupt is I2C related
    {
//        F.I2C = 1;              // set i2c flag bit
//        SSPIF = 0;
        i2cIsrHandler();
    } else if (T0IF == 1)       // overflow of time
    {
//        TIME += 256;
        T0IF = 0;
    } else if (TMR1IF == 1)     // overflow of counts; probably never happens
    {
        COUNTS += 65536;
        TMR1IF = 0;
    } else if (RBIF == 1)       // PORTB change
    {
        if (RB5 != DIR_READ)    // verify that it was a direction change
        {
            F.DIR = 1;          // set direction flag bit
        } else                  // Error, probably H-Bridge related
        {
            TRISD = 0;
            PORTD = 0xE0;
        }
        RBIF = 0;
    } else                      // Any other interrupt error
    {
        TRISD = 0;
        PORTD = 0xF0;
    }
}


// Takes in variables holding the most recent time read and count read and adds
//  (or subtracsts, depending on the direction) those to the current totals
void UpdateData(int t, int c)
{
    // Assuming no overflow occurs in longs

    // Add counts if going forward, subtract if going backwards
    if (DIR_READ == FORWARD)
    {
//        TIME += t;
        COUNTS += c;
    } else
    {
//        TIME += t;
        COUNTS -= c;
    }
}


// Sets the direction according to the direction value
void setDirection(int dir)
{
    if (dir == 0)
        PORTBbits.RB3 = FORWARD;        // forward
    else if (dir == 1)
        PORTBbits.RB3 = BACKWARD;       // reverse
    else
        PORTBbits.RB3 = FORWARD;        // default to motor forward
}


// Returns the absolute value of the difference between two numbers
int abs(int a, int b)
{
    int temp;
    temp = a - b;
    if (temp < 0)
        temp = temp * -1;
    return temp;
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

//Function that converts 0-10 to PWM percentage in increments of 10%
//  and then sets that PWM signal
void CalcPulse(int speed)
{
    int pulse = speed*255/10;
    SetPulse(pulse);
}



void delay1sec()
{
    int i = 0;

    // Loop 76 times for 1 second delay (20MHz, 256 prescale)
    for(i; i <= 76; i++)
    {
        while (T0IF == 0)
            asm("nop");
        T0IF = 0;
    }

}


