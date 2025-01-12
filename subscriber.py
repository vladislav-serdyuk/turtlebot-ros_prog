#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("I heard %s",data.data)

def subscriber():
    rospy.init_node('hello_topic_subscriber')
    rospy.Subscriber("hello", String, callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    subscriber()