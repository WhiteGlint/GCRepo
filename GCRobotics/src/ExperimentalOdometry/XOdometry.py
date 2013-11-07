#!/usr/bin/env python
import math
import roslib; roslib.load_manifest('GCRobotics')
import rospy
import tf
from std_msgs.msg import String
from geometry_msgs.msg import Twist

mouse1 = file('/dev/input/mouse1')
mouse2 = file('/dev/input/mouse2')

D = 0.56 # 0.0056 Distance between sensors

def talker():
	x1=0
	y1=0
	x2=0
	y2=0
	br = tf.TransformBroadcaster()
	pub = rospy.Publisher('XOdometry', Twist)
	rospy.init_node('XOdometry')
	msg = Twist()
	
	while not rospy.is_shutdown():
		status1, dx1, dy1 = tuple(ord(c) for c in mouse1.read(3))
		status2, dx2, dy2 = tuple(ord(d) for d in mouse2.read(3))
		
		def to_signed(n):
			return n -((0x80 & n) << 1)
		
		dx1 = to_signed(dx1)  # count/m conversion factors
		dy1 = to_signed(dy1)
		dx2 = to_signed(dx2) 
		dy2 = to_signed(dy2) 
		x1 +=dx1
		y1 +=dy1
		x2 +=dx2
		y2 +=dy2
		
		msg.angular.z = math.atan2((y1/1650.0-y2/1650.0),D)
		msg.linear.x = (((x1+x2)/2))/1650.0 #165000.0
		msg.linear.y = (((y1+y2)/2))/1650.0 #165000.0
		print "mouse 1: %f %f %f" % (msg.linear.x, msg.linear.y, msg.angular.z*180/3.14159)

		pub.publish(msg)
		br.sendTransform((msg.linear.x*math.cos(msg.angular.z)-msg.linear.y*math.sin(msg.angular.z), msg.linear.x*math.sin(msg.angular.z)+msg.linear.y*math.cos(msg.angular.z), 0), tf.transformations.quaternion_from_euler(0, 0, msg.angular.z), rospy.Time.now(),"Odom","base_link")
if __name__ == '__main__':

	try:
		talker()
	except rospy.ROSInterruptException:
		pass
