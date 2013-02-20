#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from geometry_msgs import Twist
import curses

def talker():
	pub = rospy.Publisher('Velocity',Twist)
	rospy.init_node('talker')
	msg = Twist()
	flag = 0;
	while not rospy.is_shutdown():
	
		#curses.flushinp()

		i = stdscr.getch()
		if i == ord('w'):
			msg.linear.x = 5;
			msg.linear.y = 0;
			pub.publish(msg);	
		elif i == ord('a'):
			msg.linear.x = 0;
			msg.linear.y = -5;
			pub.publish(msg);	
		elif i == ord('s'):
			msg.linear.x = -5;
			msg.linear.y = 0;
			pub.publish(msg);	
		elif i == ord('d'):
			msg.linear.x = 0;
			msg.linear.y = 5;
			pub.publish(msg);	
		elif i == ord('f'):
			msg.linear.x = 0;
			msg.linear.y = 0;
			pub.publish(msg);	
					

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
