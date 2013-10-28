#!/usr/bin/env python

#		NAME 	 - Logging Node 
#		DESIGN - Scott Caldwell
# 		PRIORITY - Utility - For diagnostic purposes

#		--------OVERVIEW--------
# TBD

import roslib; roslib.load_manifest('GCRobotics')
import rospy

if __name__ == '__main__':
	try:
		display_options_menu()
		curses.endwin()
	except rospy.ROSInterruptException:
		curses.nonl()
		curses.echo()
		curses.endwin()