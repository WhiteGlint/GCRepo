#define LiftBusy    12    // Busy flag.      0 = ready , 1 = busy
#define LiftData    11    // Data flag.      0 = do nothing, 1 = move to next state
#define LiftLevel   10    // Tells which level the plate is located on
// 0 = bottom shelf
// 1 = top shelf




// Initialize functions for the master
void liftMasterInitialize();

void liftMasterSetLevel(int Shelf);

// This function is called to indicate that we want to request the slave to change state
void liftMasterRequestStateChange();

// This function is the heart of the library. It handles the communication between the master and the slave
void liftMasterSpinOnce();

// Initialize functions for the master
void liftSlaveInitialize();

// The slave will pull the Busy line HIGH to indicate that it is busy
void liftSlaveSetBusy();

// The slave will pull the Busy line LOW to indicate that it is not busy
void liftSlaveSetReady();

// The slave will read the Level line and return the result
int  liftSlaveGetLevel();

// The Slave will read the Data line and return whether or not the master is telling it to change state
int  liftSlaveStateChangeCheck();



int Change;            // 0 = don't need to change state, 1 = need to change state
int SetFlag;           // Just set flag


/*******************************************************************
*
*				Functions for the master
*
*******************************************************************/
void liftMasterInitialize()
{
	// initialize all the variables
	Change = 0;
	SetFlag = 0;

	// Set all the pins to the proper mode
	pinMode(LiftBusy, INPUT);           // Busy pin = input
	pinMode(LiftData, OUTPUT);          // Data pin = output
	pinMode(LiftLevel, OUTPUT);         // Level pin = output

	// Make sure that Data and Level line are LOW to begin with
	digitalWrite(LiftData, 0);
	digitalWrite(LiftLevel, 0);
}

void liftMasterSetLevel(int Shelf)
{
	// Write to the Level line the value of shelf
	// 0 = lower shelf, 1 = higher shelf
    digitalWrite(LiftLevel, Shelf);
}

// This function doesn't look very intuitive to begin with but the function of it is to 
// let the master decide whether it needs to request a statechange for the slave or not.
// Look at the conditional statement of liftMasterSpinOnce() to better understand the function
// of the variable Change.
void liftMasterRequestStateChange()
{
    Change = 1;
}

void liftMasterSpinOnce()
{
    // If the slave is not busy and it need to progress to the next state of the lift
    if ((digitalRead(LiftBusy) == 0) && (Change == 1) && (SetFlag == 0))
    {
        digitalWrite(LiftData, 1);
		// Set flag to indicate that we just set the data line
        SetFlag = 1;
    }
	
    // If the slave became busy because it register our request for a change in state
    else if ((digitalRead(LiftBusy) == 1) && (SetFlag == 1)){
        digitalWrite(LiftData, 0);
		// Clear all the flags since we've just successfully requested a statechange for the slave
        SetFlag = 0;
        Change = 0;

    }
}

/***********************************************
 *
 *      Functions for Slave
 *
 ***********************************************/

void liftSlaveInitialize()
{
    // Set all the pins to the proper mode
    pinMode(LiftBusy, OUTPUT);
    pinMode(LiftData, INPUT);
    pinMode(LiftLevel, INPUT);

	//Make sure the Busy line is initially set to ready
    digitalWrite(LiftBusy, 0);
}


void liftSlaveSetBusy()
{
	// Slave set the Busy line to busy
	digitalWrite(LiftBusy, HIGH);
}

void liftSlaveSetReady()
{
	// Slave set the busy line to Ready
	digitalWrite(LiftBusy, LOW);
}

int  liftSlaveGetLevel()
{
	// Return the value of the Level line
	return digitalRead(LiftLevel);
}

int  liftSlaveStateChangeCheck()
{
	// Return the value of the Data line
	return digitalRead(LiftData);
}

