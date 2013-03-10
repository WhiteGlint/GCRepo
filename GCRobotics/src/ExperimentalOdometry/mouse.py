import math

mouse1 = file('/dev/input/mouse0')
mouse2 = file('/dev/input/mouse1')


D = 1.0 # Distance between sensors
x1=0
y1=0
x2=0
y2=0

while True:
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
	
	x = (x1+x2)/2
	y = (y1+y2)/2
	heading = math.atan2((y2-y1),D)
		
	print "Current Position: %d %d %f" % (x, y, heading)
