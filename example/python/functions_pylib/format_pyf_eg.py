#_*_coding:UTF-8_*_
# -*- coding: utf-8 -*-
 
#====================
#File: abop.py
#Author: Wendy
#Date: 2013-12-03
#====================
 
#eclipse pydev, python3.3
 
age = 25
name = 'Caroline'
 
print('{0} is {1} years old. '.format(name, age)) #�������
print('{0} is a girl. '.format(name))
print('{0:.3} is a decimal. '.format(1/3)) #С�������λ
print('{0:_^11} is a 11 length. '.format(name)) #ʹ��_�����λ
print('{first} is as {second}. '.format(first=name, second='Wendy')) #�����滻
print('My name is {0.name}'.format(open('out.txt', 'w'))) #���÷���
print('My name is {0:8}.'.format('Fred')) #ָ�����


'''
Caroline is 25 years old. 
Caroline is a girl. 
0.333 is a decimal. 
_Caroline__ is a 11 length. 
Caroline is as Wendy. 
My name is out.txt
My name is Fred    .
'''