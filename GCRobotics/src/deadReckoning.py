#!/usr/bin/env python
import roslib; roslib.load_manifest('GCRobotics')
import rospy
from std_msgs.msg import String
from GCRobotics.msg import simpleVelocity
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose

class deadReckoning:
	
	vx1 = 0
	vy1 = 0
	pub = rospy.Publisher('DeadPose',Pose)
	msg = Pose()
	
	def init():
	
		msg.position.x = 0;
		msg.position.y = 0;
		
			
def callback(data):

#	if(vx1 == none): #first run protection
#		vx1 = data.linear.x
#		vy1 = data.linear.y
#		t1 = rospy.Time.now()
#		msg.position.x = 0
#		msg.position.y = 0
#		return
	print("HERE")
	if(vx1 != 0): # forward x velocity
		msg.position.x = msg.position.x + (vx1*(rospy.Time.now()-t1))
		msg.position.y = msg.position.y + 0
	if(vy1 != 0): # backward x velocity
		msg.position.x = msg.position.x +0
		msg.position.y = msg.position.y + (vy1*(rospy.Time.now()-t1))

	vx1 = data.linear.x
	vy1 = data.linear.y
	t1 = rospy.Time.now()
	msg.position.x = 0
	msg.position.y = 0	
	pub.publish(msg)

def listener():

	c.init
	
	rospy.init_node('DeadReckoningOdom', anonymous=True)
	rospy.Subscriber("Velocity", Twist, c.callback)
	rospy.spin()

if __name__ == '__main__':
	listener()

