#!/usr/bin/env python
import math
import roslib; roslib.load_manifest('GCRobotics')
import rospy
import tf
from std_msgs.msg import String
from GCRobotics.msg import Pose_msg

mouse1 = file('/dev/input/mouse0')
mouse2 = file('/dev/input/mouse1')

D = 1.0 # Distance between sensors

def talker():
	x1=0
	y1=0
	x2=0
	y2=0
	br = tf.TransformBroadcaster()
	pub = rospy.Publisher('XOdometry',Pose_msg)
	rospy.init_node('XOdometry')
	msg = Pose_msg()
	
	while not rospy.is_shutdown():
		status1, dx1, dy1 = tuple(ord(c) for c in mouse1.read(3))
		status2, dx2, dy2 = tuple(ord(d) for d in mouse2.read(3))
	
		def to_signed(n):
			return n -((0x80 & n) << 1)
		
		dx1 = to_signed(dx1)
		dy1 = to_signed(dy1)
		dx2 = to_signed(dx2)
		dy2 = to_signed(dy2)
		x1 +=dx1
		y1 +=dy1
		x2 +=dx2
		y2 +=dy2
	
		msg.x = (x1+x2)/2
		msg.y = (y1+y2)/2
		msg.heading = math.atan2((y2-y1),D)
	
		pub.publish(msg)
		br.sendTransform((msg.x, msg.y, 0), tf.transformations.quaternion_from_euler(0, 0, msg.heading), rospy.Time.now(),"Odom","world")

	
if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
