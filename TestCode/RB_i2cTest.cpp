
#include <iostream>
#include </home/gcr/GCRepo/roboio/Include/roboard.h>
#include <unistd.h>

using namespace std;


void wait_ms(long);

int main(){

roboio_SetRBVer(RB_100RD);

unsigned char buf[3];
int test = 8;


buf[0] =0x04 ;
buf[1] = 0x05;
buf[2] = 0x06;


if (i2c_Init(I2CMODE_AUTO,10000) == false){
	cout << "Error: " << roboio_GetErrMsg();
}

	if (i2c_Send(0x2<<1, buf, 3) == false) cout << roboio_GetErrMsg();
	i2c_Close();
return 0;
}



void wait_ms(long t) {
    // This's a function for t-millisecond delay; implement this according to your platform!
    // The following is just a stupid (but simple) cross-platform implementation for the purpose of sample codes.

    volatile long i, j;
    for (i=0L; i<t; i++)
    for (j=0L; j<66666L; j++);
}
