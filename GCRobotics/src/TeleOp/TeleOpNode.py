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
from time import sleep
import curses

teleop_set = {'w', 'a', 's', 'd', 'q', 'e', 'f', 't', 'g', 'h', 'j', 'k'}
directional_set = {'w', 'a', 's', 'd', 'q', 'e'}
isolated_set = {'1', '2', '3', '4', '!', '@', '#', '$'}
command_set = {'z','Z'}
diagnostic_set = {'c', 'i', 'v'}

MAX_VELOCITY = 65
MED_VELOCITY = 30
MIN_VELOCITY = 1
STOP_VELOCITY = 0
VELOCITY_INCR = 5

rospy.init_node('TeleOp')
stdscr = curses.initscr()
curses.noecho()
stdscr.nodelay(1)
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
		stdscr.addstr('w: Forward, s: Backward, a: Left, d: Right, q: Rotate left, e: Rotate right\n')
		stdscr.addstr('f: Stop, t: Min Speed, g: Middle Speed, h: Max Speed, j: Speed Up, k: Slow Down\n')
		stdscr.addstr('z: Run script file, Z: Enter commands\n')

		stdscr.addstr('\nIsolated motor control (Shift + Number goes backwards)')
		stdscr.addstr('\n-----------------------------------------\n')
		stdscr.addstr('1: Motor 1, 2: Motor 2, 3: Motor 3, 4: Motor 4\n')
		stdscr.addstr('!: Motor 1, @: Motor 2, #: Motor 3, $: Motor 4\n')

		stdscr.addstr('\nDiagnostic commands (mutually exclusive)')
		stdscr.addstr('\n-----------------------------------------\n')
		stdscr.addstr('c: Display encoder counts, v: Toggle velocity display\n\n')
		#stdscr.addstr('i: Display key commands\n\n')
	except curses.error:
		pass

def read_script_file(fn):
	try:
		file = open(fn)
	except IOError:
		try:
			stdscr.addstr('\nERROR: Bad filename.\n\n')
		except curses.error:
			pass
		return ''
	s = file.read()
	file.close()
	return s

def run_commands(s):
	s = s.lower()
	s = s.split(',')

	for instruction in s:
		speed = ''
		direction = ''
		duration = ''

		for char in instruction:
			if char.isdigit() or char == '.':
				if direction == '':
					speed += char
				else:
					duration += char
			else:
				direction = char

		velocity_msg.speed = int(speed)
		velocity_msg.direction = direction
		sleep(float(duration))
		velocity_pub.publish(velocity_msg)
		rospy.sleep(.001)

	velocity_msg.speed = STOP_VELOCITY
	velocity_msg.direction = 0
	velocity_pub.publish(velocity_msg)
	rospy.sleep(.001)



def loop():
	while not rospy.is_shutdown():

		i =  stdscr.getch()

		try:
			i = chr(i)
		except ValueError:
			continue

		if i in teleop_set:
			teleop(i)
		elif i in isolated_set:
			isolated(i)
		elif i in command_set:
			command(i)
		elif i in diagnostic_set:
			diagnostics(i)

def teleop(i):
	
	keyToDirection = {'w':0, 'a':3, 's':2, 'd':1, 'q':5, 'e':4, 'f':0}

	try:
		velocity_msg.direction = keyToDirection[i]
	except:
		pass

	if velocity_msg.speed == STOP_VELOCITY and i in directional_set:
		velocity_msg.speed = MED_VELOCITY
		
	if i == 'f':
		velocity_msg.speed = STOP_VELOCITY

	if i == 't':
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
		if velocity_msg.speed - VELOCITY_INCR >= STOP_VELOCITY:
			velocity_msg.speed -= VELOCITY_INCR
		else:
			velocity_msg.speed = STOP_VELOCITY
			
	velocity_pub.publish(velocity_msg)
	rospy.sleep(.001)

def isolated(i):
	keyToDirection = {'1':11, '2':12, '3':13, '4':14, '!': 15, '@':16, '#':17, '$':18}

	try:
		velocity_msg.direction = keyToDirection[i]
	except:
		pass

	velocity_msg.speed = MED_VELOCITY

	velocity_pub.publish(velocity_msg)
	rospy.sleep(.001)

def command(i):
	stdscr.nodelay(0)
	curses.echo()
	if i == 'z':
		stdscr.clear()
		s = ''
		while s == '':
			stdscr.addstr('Enter filename: ')
			fn = stdscr.getstr()
			s = read_script_file(fn)
		run_commands(s)
	elif i == 'Z':
		stdscr.clear()
		stdscr.addstr('Syntax: [SPEED][DIRECTION][DURATION],[SPEED][DIRECTION][DURATION],...\n')
		stdscr.addstr('Ex: 30w1,65e1.5,0f0\n\n')
		s = stdscr.getstr()
		run_commands(s)
	curses.noecho()
	stdscr.nodelay(1)
	display_startup_info()

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
		stdscr.nodelay(0)
		curses.endwin()
	except rospy.ROSInterruptException:
		curses.nonl()
		curses.echo()
		curses.endwin()
