#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from GCRobotics.msg import i2cData


def callback(data):
	rospy.loginfo(rospy.get_name() + ": I head %s" % data.address)


def listener():
	rospy.init_node('i2cNode',anonymous=False)
	rospy.Subscriber("i2cSend",i2cData, callback)
	rospy.spin()

if __name__ == '__main__':
	listener()
