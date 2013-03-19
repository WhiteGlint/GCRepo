#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity
import curses

def talker():
	pub = rospy.Publisher('Velocity',simpleVelocity)
	rospy.init_node('talker')
	msg = simpleVelocity()
	flag = 0;
	while not rospy.is_shutdown():
	
		#curses.flushinp()

		i = stdscr.getch()
		if i == ord('w'):
			msg.speed = 5;
			msg.direction = 0;
			#pub.publish(msg);	
		elif i == ord('a'):
			msg.speed = 5;
			msg.direction = 1;
			#pub.publish(msg);	
		elif i == ord('s'):
			msg.speed = 5;
			msg.direction = 2;
			#pub.publish(msg);	
		elif i == ord('d'):
			msg.speed = 5;
			msg.direction = 3;
			#pub.publish(msg);	
		elif i == ord('f'):
			msg.speed = 0;
			msg.direction = 0;
			#pub.publish(msg);	
			
		pub.publish(msg);
		rospy.sleep(.001);

if __name__ == '__main__':

	try:
		stdscr = curses.initscr();
		stdscr.nodelay(1);
		curses.noecho()
		curses.cbreak()
		talker()
	except rospy.ROSInterruptException:
		curses.nocbreak(); stdscr.keypad(0); curses.echo()
		curses.endwin()
		pass
