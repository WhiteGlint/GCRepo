all: HighLow_Test LedChase

HighLow_Test : HighLow_Test.o
	gcc -o HighLow_Test HighLow_Test.o -L /opt/roboio/Lib -lRBIO -lstdc++

HighLow_Test.o : HighLow_Test.cpp
	gcc -c HighLow_Test.cpp -I /opt/roboio/Include



LedChase : LedChase.o
	gcc -o LedChase LedChase.o -L /opt/roboio/Lib -lRBIO -lstdc++

LedChase.o : LedChase.cpp
	gcc -c LedChase.cpp -I /opt/roboio/Include
