/* 
 * File:   i2cSlave.h
 * Author: josh
 *
 * Created on December 27, 2012, 8:55 PM
 */

#ifndef I2CSLAVE_H
#define	I2CSLAVE_H


int val = 0;
char i2cBuffer[2];
char i2cRequest;
void i2cInit(char address);
void i2cIsrHandler();
void i2cSend(char msg);



#endif	/* I2CSLAVE_H */

