#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("I heard %s",data.data)
    os.system(f'echo {data.data} > /dev/ttyACM0')

def subscriber():
    rospy.init_node('base_topic_publisher')
    rospy.Subscriber("hello", String, callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    subscriber()
