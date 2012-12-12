motor_control_test: main.o motor_control_lib.o
	gcc -o motor_control_test main.o motor_control_lib.o -L /home/gcr/GCRepo/roboio/Lib -lRBIO -lstdc++

main.o : main.cpp control_lib.h
	gcc -c main.cpp
motor_control_lib.o : control_lib.cpp control_lib.h
 	gcc -c control_lib.cpp -I /home/gcr/GCRepo/roboio/Include

