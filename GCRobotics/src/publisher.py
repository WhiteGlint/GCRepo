#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity
from nav_msgs.msg import Odometry

def talker():
	pub = rospy.Publisher('odom',Odometry)
	rospy.init_node('Talker')
	while not rospy.is_shutdown():
		msg = Odometry()
		
		msg.header.frame_id = "/map"
				
		msg.pose.pose.position.x = 0
		msg.pose.pose.position.y = 0
		msg.pose.pose.position.z = 0

		msg.twist.twist.linear.x = 0
		msg.twist.twist.linear.y = 0
		msg.twist.twist.linear.z = 0
		
		msg.twist.twist.angular.x = 0
		msg.twist.twist.angular.y = 0
		msg.twist.twist.angular.z = 0
					
		pub.publish(msg)
		rospy.sleep(10.0)

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
