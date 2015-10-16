#!/usr/bin/python
# -*- coding: UTF-8 -*-

import threading
import time

exitFlag = 0

def print_time(threadName, delay, counter):
    while counter:
        if exitFlag:
            thread.exit()
        time.sleep(delay)
        print "%s: %s\n" % (threadName, time.ctime(time.time()))
        counter -= 1
		
class myThread (threading.Thread):   #�̳и���threading.Thread
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):                   #��Ҫִ�еĴ���д��run�������� �߳��ڴ������ֱ������run���� 
        print "Starting " + self.name + '\n'
        print_time(self.name, 1, self.counter)
        print "Exiting " + self.name + '\n'

# �������߳�
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

# �����߳�
thread1.start()
thread2.start()

time.sleep(3)
print "Exiting Main Thread\n"