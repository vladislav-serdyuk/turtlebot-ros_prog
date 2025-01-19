#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Int32

pub = rospy.Publisher('speed_L', Int32, queue_size=10)
rospy.init_node('pc')

while not rospy.is_shutdown():
    for speed in range(40, -40, -5):
        pub.publish(speed)
        rospy.sleep(0.1)
    for speed in range(-40, 40, 5):
        pub.publish(speed)
        rospy.sleep(0.1)
