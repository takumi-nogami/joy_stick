import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Point
from std_msgs.msg import Int32

class JoyTwist(object):
    def __init__(self):
           self._joy_sub = rospy.Subscriber('joy', Joy, self.joy_callback, queue_size=1)
           self._stepper = rospy.Publisher('cmd_stepper', Twist, queue_size=1)
           self._hand = rospy.Publisher('cmd_hand', Int32, queue_size=1)

    def joy_callback(self, joy_msg):
	if joy_msg.buttons[4] == 1:
            move = Twist()
            move.linear.x = joy_msg.axes[1]
            self._stepper.publish(move)
	if joy_msg.buttons[5] == 1:
            move = Twist()
            move.angular.z = joy_msg.axes[2]
            self._stepper.publish(move)
	if joy_msg.buttons[3] == 1:
            hand = Int32()
            hand.data = 3
            self._hand.publish(hand)
	if joy_msg.buttons[2] == 1:
            hand = Int32()
            hand.data = 2
            self._hand.publish(hand)
	if joy_msg.buttons[1] == 1:
            hand = Int32()
            hand.data = 1
            self._hand.publish(hand)
	if joy_msg.buttons[0] == 1:
            hand = Int32()
            hand.data = 0
            self._hand.publish(hand)

if __name__ == '__main__':
    rospy.init_node('joy_twist')
    joy_twist = JoyTwist()
    rospy.spin()

