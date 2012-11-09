#include <iostream>
#include <roboard.h>
#include <unistd.h>

using namespace std;

int main(){

int val = 2;
roboio_SetRBVer(RB_100RD);
rcservo_Init(RCSERVO_USENOPIN);

while(true){

    rcservo_OutPin(val,1);
    sleep(1);
    rcservo_OutPin(val,0);
    val++;
    if (val == 10)
        val = 2;
}

rcservo_Close();
return 0;
}
