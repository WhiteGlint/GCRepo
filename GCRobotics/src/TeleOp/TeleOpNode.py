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
	stdscr.addstr("W: Forward, S: Backward, A: left, D: right, Q: rotate left, E: rotate right, F: stop");
	curses.noecho()
	
	while not rospy.is_shutdown():
	
		keyToDirection = {ord('w'):0, ord('a'):3, ord('s'):2, ord('d'):1, ord('q'):5, ord('e'):4, ord('f'):0}
		
		i = stdscr.getch()
		msg.direction = keyToDirection[i]
		msg.speed = 150;
		
		if (i == ord('f')):
			msg.speed = 0;
			
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
