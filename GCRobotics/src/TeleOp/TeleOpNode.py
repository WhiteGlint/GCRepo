#!/usr/bin/env python

#		NAME 	 - Tele Op Node 
#		DESIGN - Josh Galicic, Scott Caldwell
# 		PRIORITY - Utility - Likely required for testing purposes
	
#		--------OVERVIEW--------
# This node takes in keyboard input and generates velocity messages at a set speed.
# WASD are used to specify direction, pressing them once will continue that motion
# until 'f' is pressed. Since our motor controllers are not designed to require constant
# messages to continue, this node will send 1 velocity message, and stop until you input
# a different one. Closing this node while the bot is running will not stop it, it will
# just keep going until it runs into a wall and you make an impressive, daring dive after it.
#
#		--------CURRENT WORK--------
# Currently in the process of converting this node from being purely a teleop node to being
# a testing/diagnostic/teleop node.

import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity, Encoder_msg
import curses

teleop_set = {'w', 'a', 's', 'd', 'q', 'e', 'f', 'g', 'h', 'j', 'k'}
directional_set = {'w', 'a', 's', 'd', 'q', 'e'}
diagnostic_set = {'c', 'i', 'v'}

MAX_VELOCITY = 120
MED_VELOCITY = 90
MIN_VELOCITY = 0
VELOCITY_INCR = 20

rospy.init_node('TeleOp')
stdscr = curses.initscr()
curses.noecho()
velocity_pub = rospy.Publisher('Velocity', simpleVelocity)
velocity_msg = simpleVelocity()
velocity_msg.speed = 0
global sub
global current_subscriber
sub = None
current_subscriber = None

def encoder_callback(data):
	stdscr.erase()
	stdscr.addstr('Encoder 1: ')
	stdscr.addstr(str(data.encoder1))
	stdscr.addstr('\nEncoder 2: ')
	stdscr.addstr(str(data.encoder2))
	stdscr.addstr('\nEncoder 3: ')
	stdscr.addstr(str(data.encoder3))
	stdscr.addstr('\nEncoder 4: ')
	stdscr.addstr(str(data.encoder4))

def velocity_callback(data):
	stdscr.erase()
	stdscr.addstr('Velocity: ')
	stdscr.addstr(str(data.speed))

def display_startup_info():
	try:
		stdscr.clear()
		stdscr.addstr('Motion commands')
		stdscr.addstr('\n-----------------------------------------\n')
		stdscr.addstr('W: Forward, S: Backward, A: Left, D: Right, Q: Rotate left, E: Rotate right\n')
		stdscr.addstr('F: Stop, G: Middle Speed, H: Max Speed, J: Speed Up, K: Slow Down\n')
		stdscr.addstr('\nDiagnostic commands (mutually exclusive)')
		stdscr.addstr('\n-----------------------------------------\n')
		stdscr.addstr('C: Display encoder counts, V: Toggle velocity display\n\n')
		#stdscr.addstr('I: Display key commands\n\n')
	except curses.error:
		pass

def loop():
	while not rospy.is_shutdown():

		i =  stdscr.getch()

		try:
			i = chr(i)
		except ValueError:
			continue

		if i in teleop_set:
			teleop(i)
		elif i in diagnostic_set:
			diagnostics(i)

def teleop(i):
	
	keyToDirection = {'w':0, 'a':3, 's':2, 'd':1, 'q':5, 'e':4, 'f':0}

	try:
		velocity_msg.direction = keyToDirection[i]
	except:
		pass

	if velocity_msg.speed == MIN_VELOCITY and i in directional_set: # directional
		velocity_msg.speed = MED_VELOCITY
		
	if i == 'f':
		velocity_msg.speed = MIN_VELOCITY

	if i == 'g':
		velocity_msg.speed = MED_VELOCITY

	if i == 'h':
		velocity_msg.speed = MAX_VELOCITY
			
	if i == 'j':
		if velocity_msg.speed + VELOCITY_INCR <= MAX_VELOCITY:
			velocity_msg.speed += VELOCITY_INCR
		else:
			velocity_msg.speed = MAX_VELOCITY
		
	if i == 'k':
		if velocity_msg.speed - VELOCITY_INCR >= MIN_VELOCITY:
			velocity_msg.speed -= VELOCITY_INCR
		else:
			velocity_msg.speed = MIN_VELOCITY
			
	velocity_pub.publish(velocity_msg)
	rospy.sleep(.001)

def diagnostics(i):
	global sub
	global current_subscriber
	stdscr.clear()
	if i == 'i':
		display_startup_info()
	elif i == 'c':
		if sub == None:
			sub = rospy.Subscriber('EncoderData', Encoder_msg, encoder_callback)
			current_subscriber = 'c'
		elif current_subscriber != 'c':
			sub.unregister()
			sub = rospy.Subscriber('EncoderData', Encoder_msg, encoder_callback)
			current_subscriber = 'c'
		else:
			sub.unregister()
			sub = None
	elif i == 'v':
		if sub == None:
			sub = rospy.Subscriber('Velocity', simpleVelocity, velocity_callback)
			current_subscriber = 'v'
		elif current_subscriber != 'v':
			sub.unregister()
			sub = rospy.Subscriber('Velocity', simpleVelocity, velocity_callback)
			current_subscriber = 'v'
		else:
			sub.unregister()
			sub = None


if __name__ == '__main__':
	try:
		display_startup_info()
		loop()
		curses.endwin()
	except rospy.ROSInterruptException:
		curses.nonl()
		#stdscr.keypad(0)
		curses.echo()
		curses.endwin()
