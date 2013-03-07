
#include <iostream>
#include </home/gcr/GCRepo/roboio/Include/roboard.h>
#include <unistd.h>

using namespace std;


void wait_ms(long);

int main(){
	char addr;
	unsigned char data[2];
	data[0] = 0;
	data[1] = 10;
	roboio_SetRBVer(RB_100RD);
	
	while(1){
	
	
		if (i2c_Init(I2CMODE_AUTO,1000) == false)
		{
			cout << "Error: " << roboio_GetErrMsg();
			return 0;
		}

//		cout << "Enter destination address: ";
//		cin >> addr;
//		cout <<"\nEnter message byte: ";
//		cin >> data[0];
		
		data[1]++;
		if (i2c_Send(0x10>>1, data, 2) == false) cout << roboio_GetErrMsg();
		
		i2c_Close();
		cout << "Sent!\n";	
//		cin.get();	
		wait_ms(10);
	}
	return 0;
}



void wait_ms(long t) {
    // This's a function for t-millisecond delay; implement this according to your platform!
    // The following is just a stupid (but simple) cross-platform implementation for the purpose of sample codes.

    volatile long i, j;
    for (i=0L; i<t; i++)
    for (j=0L; j<66666L; j++);
}
