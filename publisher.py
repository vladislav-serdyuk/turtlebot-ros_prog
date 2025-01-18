#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

pub = rospy.Publisher('hello', String, queue_size=10)
rospy.init_node('base_topic_publisher')

while not rospy.is_shutdown():
    pub.publish("a")
    rospy.sleep(1)
    pub.publish("b")
    rospy.sleep(1)
