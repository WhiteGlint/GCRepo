#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String


def callback(data):
	rospy.loginfo(rospy.get_name() + ": I head %s" % data.data)


def listener():
	rospy.init_node('i2cNode',anonymous=False)
	rospy.Subscriber("i2cSend",String, callback)
	rospy.spin()

if __name__ == '__main__':
	listener()
