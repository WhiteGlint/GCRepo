#Welcome to the home of GCRobotics

We are a team of 6 engineers from Geneva College working to create an autonomous robot from scratch. This platform will eventually be entered in the Trinity College RoboWaiter competition. See below for more information on our goals, as well as an overview of our repository organization.

##Goals

The goal of the 2013 GCRobotics team is to start the process of building a fully autonomous robotics platform that can be used primarily in the Trinity College Robowaiter competition, but also to design with the ability to take the platform to other new and exciting competitions.

##Code Overview

Low level motor control is currently being done on 4 seperate PIC16F917 microcontrollers. These controller are responsible for PID control of the motors and use I2C to pass messages to a central computer. This central computer is the RB100, an X86 single board computer. All code on the RB100 is integrated with ROS, allowing us to easily add/remove/manipulate pieces as we see fit. 

All code pertaining to the PIC microcontrollers can be found in the "PIC Code" folder. All code here was written with MPLab X, using the HiTech C compiler. All code pertaining to the RB100 is in the GCRobotics folder. This is the root of our ROS package, from there all code is organized in keeping with normal ROS standards (src for source code, msg for custom messages...)

The roboio folder in the root directory is code provided by Roboard for controlling RB100 hardware, such as GPIO and I2C busses. 
