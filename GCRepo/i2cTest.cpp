
#include <iostream>
#include </home/josh/GCRepo/roboio/Include/roboard.h>
//#include <unistd.h>

using namespace std;

int main(){

roboio_SetRBVer(RB_100RD);

unsigned char buf[3] = {0x01, 0x02, 0x03};

if (i2c_Init(I2CMODE_STANDARD,100000)){

	i2c_Send(0x11, buf, 3);

	i2c_Receive(0x11, buf, 3);

	i2c_Close();
}




rcservo_Close();
return 0;
}
