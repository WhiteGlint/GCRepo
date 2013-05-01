#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity
import curses

def talker():

	pub = rospy.Publisher('Velocity',simpleVelocity)
	rospy.init_node('TeleOp')
	msg = simpleVelocity()
	flag = 0;
	stdscr = curses.initscr();
	stdscr.addstr("W: Forward, S: Backward, A: left, D: right, Q: rotate left, E: rotate right, F: stop\n");
	stdscr.addstr("j: Speed Up, k: Slow Down\n");
	curses.noecho()
	
	while not rospy.is_shutdown():
	
		keyToDirection = {ord('w'):0, ord('a'):3, ord('s'):2, ord('d'):1, ord('q'):5, ord('e'):4, ord('f'):0}
		
		i = stdscr.getch()
		try:
			msg.direction = keyToDirection[i]
		except:
			pass
		msg.speed = 130;
		
		if (i == ord('f')):
			msg.speed = 0;
			
		if (i == ord('j')):
			msg.speed += 20;
		
		if (i == ord('k')):
			msg.speed -= 20;
			
		pub.publish(msg);
		rospy.sleep(.001);
		
	curses.endwin()
	
if __name__ == '__main__':

	try:
		talker()
	except rospy.ROSInterruptException:
		curses.nonl()
		#stdscr.keypad(0);
		curses.echo()
		curses.endwin()
		pass
