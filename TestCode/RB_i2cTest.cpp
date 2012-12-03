
#include <iostream>
#include </home/gcr/GCRepo/roboio/Include/roboard.h>
#include <unistd.h>

using namespace std;

int main(){

roboio_SetRBVer(RB_100RD);

unsigned char buf[3] = {0x03, 0x04, 0x05};

if (i2c_Init(I2CMODE_STANDARD,1000) == false){
	cout << "Error: " << roboio_GetErrMsg();
}
	cout << endl<< "BUFFER: " << buf[1] << endl;

	i2c_Send(0x02, buf, 3);
//	i2c_Receive(0x02, buf, 1);
	sleep(1);
	cout << endl<< "BUFFER: " << buf[0] << endl;
//	i2c_Receive(0x11, buf, 3);

	i2c_Close();





//rcservo_Close();
return 0;
}
