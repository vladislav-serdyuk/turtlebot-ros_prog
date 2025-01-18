#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

pub = rospy.Publisher('control', String, queue_size=10)
rospy.init_node('pc')

while not rospy.is_shutdown():
    for speed in range(-30, 30):
        sp2 = speed + 100
        pub.publish(f'sl{sp2//100}{sp2//10%10}{sp2%10}')
        rospy.sleep(0.1)
    pub.publish(f'sl100')
    for speed in range(-30, 30):
        sp2 = speed + 100
        pub.publish(f'sr{sp2//100}{sp2//10%10}{sp2%10}')
        rospy.sleep(0.1)
    pub.publish(f'sr100')
