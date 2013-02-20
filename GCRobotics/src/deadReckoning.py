#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity
from geometry_msgs.msg import Pose





def callback(data):

	v2 = data.speed
	t2 = rospy.Time.now()
	
	if(v1 == None) #first run protection
		return
	
	msg.position.x = (data.x
	
	v1 = data.speed
	t1 = rospy.Time.now()
	

def listener():
    rospy.init_node('DeadReckoningOdom', anonymous=True)
    rospy.Subscriber("Velocity", simpleVelocity, callback)
    rospy.spin()


if __name__ == '__main__':
    listener()


