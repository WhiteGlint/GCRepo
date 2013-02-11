#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity

def talker():
	pub = rospy.Publisher('Velocity',simpleVelocity)
	rospy.init_node('talker')
	while not rospy.is_shutdown():
		msg = simpleVelocity()
		msg.direction = 1;
		msg.speed = 5;
		pub.publish(msg)
		rospy.sleep(10.0)

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
