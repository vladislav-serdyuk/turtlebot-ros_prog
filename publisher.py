#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Int32
from pynput.keyboard import Key, Listener

rospy.init_node('pc')
left_speed = rospy.Publisher('speed_L', Int32, queue_size=10)
right_speed = rospy.Publisher('speed_L', Int32, queue_size=10)

def show(key):
    if key == 'w':
        left_speed.publish(speed)
        right_speed.publish(speed)
    elif key == 'a':
        left_speed.publish(-speed)
        right_speed.publish(speed)
    elif key == 'd':
        left_speed.publish(speed)
        right_speed.publish(-speed)
    elif key == 's':
        left_speed.publish(-speed)
        right_speed.publish(-speed)
    else:
        left_speed.publish(0)
        right_speed.publish(0)

speed = 50
while not rospy.is_shutdown():
    with Listener(on_press=show) as listener:
        listener.join()
