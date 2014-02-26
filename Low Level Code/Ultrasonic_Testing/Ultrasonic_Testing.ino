/*****************************************************************************************
*
*                    Includes
*
******************************************************************************************/
#include <NewPing.h>
#include <ArduinoHardware.h>
#include <Wire.h>

/*****************************************************************************************
*
*                    Constant Declarations
*
******************************************************************************************/
/********************************************************
*          Constants for I2C
*********************************************************/
#define Front_Left   0x08
#define Front_Right  0x02
#define Back_Right   0x04
#define Back_Left    0x06


#define Forward      0x00
#define Backward     0x01

#define SlowSpeed    30
#define MediumSpeed  50
#define FastSpeed    70
#define Stop         00

/********************************************************
*          Constants for Ultrasonic Sensors
*********************************************************/
#define SENSOR_RIGHT_1 0
#define SENSOR_RIGHT_2 1
#define SENSOR_BACK_1  2
#define SENSOR_TOLERANCE 2
#define MAX_DISTANCE 200

/*****************************************************************************************
*
*                    Global Variable Declarations
*
******************************************************************************************/
NewPing sonar1 (12, 11, MAX_DISTANCE);
NewPing sonar2 (10, 9, MAX_DISTANCE);
NewPing sonar3 (7, 6, MAX_DISTANCE);

signed int SensorData[3];         // Where the ping distances are stored.
                                  // The index of the array follows the pattern described in the figure below

                    /*****************************
                    *          Front             *
                    *                        ~~~~*
                    *                        ~ 0 *
                    *                        ~~~~*
                    *                            *
                    *                        ~~~~*
                    *                        ~ 1 *
                    *           ~~~~~~~      ~~~~*
                    *           ~  2  ~          *
                    ******************************/
                    
int StateMachine = 0;        // This is a State Machine that tells the robot what it should do 
                             // with the ultrasonic data
                                   // 0 -> The robot is trying to make it self parallel to the wall by rotating CW/CCW
                                   // 1 -> The robot is trying to reach the x-axis target by strafing
                                   // 2 -> The robot is trying to reach the y-axis target by moving forward or backward


// Target Variables
int SensorTargetRight = 30, SensorTargetBack = 40;

/*****************************************************************************************
*
*                    Setup function
*
******************************************************************************************/
void setup() {
  Wire.begin(); // join i2c bus
  Serial.begin(9600);
  delay(1000);
}

/*****************************************************************************************
*
*                    Loop Function
*
******************************************************************************************/
void loop() {
  
/********************************************************
*          Read values from Ultrasonic Sensors
*********************************************************/
  SensorData[SENSOR_RIGHT_1] = sonar1.ping()/US_ROUNDTRIP_CM;
  delay(30);
  SensorData[SENSOR_RIGHT_2] = sonar2.ping()/US_ROUNDTRIP_CM;
  delay(30);
  SensorData[SENSOR_BACK_1] = sonar3.ping()/US_ROUNDTRIP_CM;
  delay(30);
  
  Serial.print(SensorData[SENSOR_RIGHT_1]); Serial.print(" , ");
  Serial.print(SensorData[SENSOR_RIGHT_2]); Serial.print(" , ");
  Serial.print(SensorData[SENSOR_BACK_1]); Serial.println(" ");


/********************************************************
*          Decision making stuff goes here
*********************************************************/
  
  // Making sure both sides are parallel
  if (StateMachine == 0)
  {  
    // If the difference of the 2 right sensors are greater than the tolerance  
    if ( ((SensorData[SENSOR_RIGHT_1] - SensorData[SENSOR_RIGHT_2]) > SENSOR_TOLERANCE) 
                                     || 
       ((SensorData[SENSOR_RIGHT_1] - SensorData[SENSOR_RIGHT_2]) < -SENSOR_TOLERANCE) )
    {
      // Determining if robot needs to rotate CW or CCW
      if (SensorData[SENSOR_RIGHT_1] > SensorData[SENSOR_RIGHT_2])
      {
        robotCW(MediumSpeed);
      }
      else 
      {
        robotCCW(MediumSpeed);
      }
    }
    // Stop the robot and move to the next state if the robot parallel
    else {
      robotStop();
      StateMachine++;
      Serial.println("              I'm stopping!!");
    }  
  }
  
  // Making sure the robot reaches the x-axis target
  if (StateMachine == 1)
  {
    // If the Front right sensor is greater than the X-Target
    // We are only using one of the sensor to check for distance
    if ((SensorData[SENSOR_RIGHT_1] < (SensorTargetRight - SENSOR_TOLERANCE)) 
                                    || 
       (SensorData[SENSOR_RIGHT_1] > (SensorTargetRight + SENSOR_TOLERANCE)))
    {
      // Determining if the robot needs to strafe left or right
      if (SensorData[SENSOR_RIGHT_1] < (SensorTargetRight - SENSOR_TOLERANCE))
      {
        robotLeft(MediumSpeed);
      }
      else 
      {
        robotRight(MediumSpeed);
      }
    }
    // The robot is at the x-axis target
    else 
    {
      // Determine if the robot is at the x-axis target && is parallel to the wall
      if ((SensorData[SENSOR_RIGHT_1] >= (SensorTargetRight - SENSOR_TOLERANCE)) && (SensorData[SENSOR_RIGHT_1] <= (SensorTargetRight + SENSOR_TOLERANCE))
                                                                         &&
          (SensorData[SENSOR_RIGHT_2] >= (SensorTargetRight - SENSOR_TOLERANCE)) && (SensorData[SENSOR_RIGHT_2] <= (SensorTargetRight + SENSOR_TOLERANCE)))
      {
        //stop the robot and go to the next state
        robotStop();
        StateMachine++;
      }
      // else the robot needs to go back to state 0 and try to get it self parallel to the wall
      else
      {
        StateMachine--;
      }
    }
  }
  
  // Making sure the robot reaches the y-axis
  if (StateMachine == 2)
  {
    // Making sure the back sensor is outside the target value
    if ((SensorData[SENSOR_BACK_1] < (SensorTargetBack - SENSOR_TOLERANCE)) 
                                   || 
       (SensorData[SENSOR_BACK_1] > (SensorTargetBack + SENSOR_TOLERANCE)))
    {
      // Deciding if the robot needs to move forward or backward
      if (SensorData[SENSOR_BACK_1] < (SensorTargetBack - SENSOR_TOLERANCE))
      {
        robotForward(MediumSpeed);
      }
      else 
      {
        robotBackward(MediumSpeed);
      }
    }
    // The robot is at the y-axis target
    else 
    {
      // Determining if the robot is (parallel to the wall) && (at the x-axis target) && (at the y-axis target)
      if (
      (SensorData[SENSOR_RIGHT_1] >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
      (SensorData[SENSOR_RIGHT_1] <= (SensorTargetRight + SENSOR_TOLERANCE)) &&
      (SensorData[SENSOR_RIGHT_2] >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
      (SensorData[SENSOR_RIGHT_2] <= (SensorTargetRight + SENSOR_TOLERANCE)) &&
      (SensorData[SENSOR_BACK_1] >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
      (SensorData[SENSOR_BACK_1] <= (SensorTargetRight + SENSOR_TOLERANCE))   )
      {
        //stop the robot and go to the next state
        robotStop();
        StateMachine++;
      }
      // else the robot needs to go back to state 0 and try to get it self parallel to the wall
      else
      {
        StateMachine = 0;
      }
    }
  }
    
  
}


void robotForward(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Forward  );
  i2cWrite(Front_Right,  RobotSpeed,   Forward  );
  i2cWrite(Back_Left,    RobotSpeed,   Forward  );
  i2cWrite(Back_Right,   RobotSpeed,   Forward  );
}

void robotBackward(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Backward  );
  i2cWrite(Front_Right,  RobotSpeed,   Backward  );
  i2cWrite(Back_Left,    RobotSpeed,   Backward  );
  i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void robotLeft(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Backward  );
  i2cWrite(Front_Right,  RobotSpeed,   Forward   );
  i2cWrite(Back_Left,    RobotSpeed,   Forward   );
  i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void robotRight(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Forward   );
  i2cWrite(Front_Right,  RobotSpeed,   Backward  );
  i2cWrite(Back_Left,    RobotSpeed,   Backward  );
  i2cWrite(Back_Right,   RobotSpeed,   Forward   );
}

void robotCW(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Forward   );
  i2cWrite(Front_Right,  RobotSpeed,   Backward  );
  i2cWrite(Back_Left,    RobotSpeed,   Forward   );
  i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void robotCCW(int RobotSpeed)
{
  i2cWrite(Front_Left,   RobotSpeed,   Backward   );
  i2cWrite(Front_Right,  RobotSpeed,   Forward    );
  i2cWrite(Back_Left,    RobotSpeed,   Backward   );
  i2cWrite(Back_Right,   RobotSpeed,   Forward    );
}

void robotStop()
{
  i2cWrite(Front_Left,   Stop,   Forward   );
  i2cWrite(Front_Right,  Stop,   Forward  );
  i2cWrite(Back_Left,    Stop,   Forward  );
  i2cWrite(Back_Right,   Stop,   Forward   );
}

void i2cWrite ( char Address, char Speed , char Direction)
{
    Wire.beginTransmission(Address >> 1 );
    Wire.write((byte)0);
    Wire.write((byte)Speed);
    Wire.write((byte)Direction);
    Wire.endTransmission();
}


