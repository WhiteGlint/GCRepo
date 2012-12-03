all: RB_i2cTest HighLow_Test

HighLow_Test : HighLow_Test.o
	gcc -o HighLow_Test HighLow_Test.o -L ../roboio/Lib -lRBIO -lstdc++
HighLow_Test.o : HighLow_Test.cpp
	gcc -c HighLow_Test.cpp -I ../roboio/Include

RB_i2cTest : RB_i2cTest.o
	gcc -o RB_i2cTest RB_i2cTest.o -L ../roboio/Lib -lRBIO -lstdc++
RB_i2cTest.o : RB_i2cTest.cpp
	gcc -c RB_i2cTest.cpp -I ../robotio/Include

