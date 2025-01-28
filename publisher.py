#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Int8, String
from geometry_msgs.msg import Twist

def in_range(x, min_, max_):
    return max(min(x, max_), min_)

def move(twist: Twist):
    print(twist)
    left_speed.publish(in_range(int((twist.linear.x*2 - twist.angular.z)*speed), -100, 100))
    right_speed.publish(in_range(-int((twist.linear.x*2 + twist.angular.z)*speed), -100, 100))

def move_from_rc100(rc100_key: String):
    rc100_key_str = rc100_key.data
    # print(rc100_key_str)
    if rc100_key_str == 'U':
        left_speed_ = speed
        right_speed_ = speed
    elif rc100_key_str == 'D':
        left_speed_ = -speed
        right_speed_ = -speed
    elif rc100_key_str == 'L':
        left_speed_ = -speed
        right_speed_ = speed
    elif rc100_key_str == 'R':
        left_speed_ = speed
        right_speed_ = -speed
    elif rc100_key_str == '1':
        left_speed_ = speed
        right_speed_ = speed
    elif rc100_key_str == '2':
        left_speed_ = -speed
        right_speed_ = speed
    elif rc100_key_str == '3':
        left_speed_ = -speed
        right_speed_ = -speed
    elif rc100_key_str == '4':
        left_speed_ = speed
        right_speed_ = -speed
    elif rc100_key_str == '5':
        left_speed_ = speed
        right_speed_ = 0
    elif rc100_key_str == '6':
        left_speed_ = 0
        right_speed_ = speed
    else:
        left_speed_ = 0
        right_speed_ = 0

    left_speed.publish(int(in_range(left_speed_*1.15, -100, 100)))
    right_speed.publish(-right_speed_)

rospy.init_node('pc')
left_speed = rospy.Publisher('speed_L', Int8, queue_size=10)
right_speed = rospy.Publisher('speed_R', Int8, queue_size=10)
keyboard_input = rospy.Subscriber('cmd_vel', Twist, move)
rc100 = rospy.Subscriber('rc100', String, move_from_rc100)

speed = 60
while not rospy.is_shutdown():
    pass
