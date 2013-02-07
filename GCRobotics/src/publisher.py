#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String

def talker():
	pub = rospy.Publisher('i2cSend',String)
	rospy.init_node('talker')
	while not rospy.is_shutdown():
		str = "hello World"
		pub.publish(String(str))
		rospy.sleep(1.0)

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
