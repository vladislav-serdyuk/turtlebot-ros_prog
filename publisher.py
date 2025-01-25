#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Int32
from geometry_msgs.msg import Twist

def in_range(x, min_, max_):
    return max(min(x, max_), min_)

def move(twist: Twist):
    print(twist)
    left_speed.publish(in_range(int((twist.linear.x*2 - twist.angular.z)*speed), -100, 100))
    right_speed.publish(in_range(-int((twist.linear.x*2 + twist.angular.z)*speed), -100, 100))

rospy.init_node('pc')
left_speed = rospy.Publisher('speed_L', Int32, queue_size=10)
right_speed = rospy.Publisher('speed_R', Int32, queue_size=10)
keyboard_input = rospy.Subscriber('cmd_vel', Twist, move)

speed = 20
while not rospy.is_shutdown():
    pass
