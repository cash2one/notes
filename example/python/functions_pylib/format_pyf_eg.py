#_*_coding:UTF-8_*_
# -*- coding: utf-8 -*-
 
#====================
#File: abop.py
#Author: Wendy
#Date: 2013-12-03
#====================
 
#eclipse pydev, python3.3
#coding=utf-8
'''
����ָ�����賤�ȵ��ַ����Ķ��뷽ʽ:
< ��Ĭ�ϣ������
> �Ҷ���
^ �м����
= ��ֻ�������֣���С�������в���
'''
print '1:\t|{0:>10},'.format('wangyu')
print '2:\t|{0:4.2f}'.format(1.1415926)
print '3:\t|',format(1.1415926,'<10.2f')
print '4:\t|{0:<10},{1:<15}'.format('wangyu',1.1415926)
print '5:\t|User ID: {uid} Last seen: {last_login}'.format(uid='root',last_login = '5 Mar 2008 07:20') 
 
'''��ʽ��ָʾ�����԰���һ��չʾ���������Ƹ�ʽ��
���磬���������Ա���ʽ��Ϊһ���ʽ����������ʾ��
'b' - �����ơ���������2Ϊ�������������
'c' - �ַ����ڴ�ӡ֮ǰ������ת���ɶ�Ӧ��Unicode�ַ�����
'd' - ʮ������������������10Ϊ�������������
'o' - �˽��ơ���������8Ϊ�������������
'x' - ʮ�����ơ���������16Ϊ�������������9���ϵ�λ����Сд��ĸ��
'e' - �ݷ��š��ÿ�ѧ��������ӡ���֡���'e'��ʾ�ݡ�
'g' - һ���ʽ������ֵ��fixed-point��ʽ���������ֵ�ر���ʱ��������ʽ��ӡ��
'n' - ���֡���ֵΪ����ʱ��'d'��ͬ��ֵΪ������ʱ��'g'��ͬ����ͬ������������������ò������ַָ�����
'%' - �ٷ���������ֵ����100Ȼ����fixed-point('f')��ʽ��ӡ��ֵ�������һ���ٷֺš�
'''
 
print '6:\t|{0:b}'.format(3)
print '7:\t|{0:c}'.format(3)
print '8:\t|{0:d}'.format(3)
print '9:\t|{0:o}'.format(3)
print '10:\t|{0:x}'.format(3)
print '11:\t|{0:e}'.format(3.75)
print '12:\t|{0:g}'.format(3.75)
print '13:\t|{0:n}'.format(3.75) #������
print '14:\t|{0:n}'.format(3)    #����
print '15:\t|{0:%}'.format(3.75)
 
#������ʽ�Ŀ���format
a = int(raw_input('a:'))
b = int(raw_input('b:'))
print '16:\t|%*.*f' % (a, b, 1.1415926)
 
print '17:\t|{array[2]}'.format(array=range(10))
print '18:\t|{attr.__class__}'.format(attr=0)
print '19:\t|{digit:*^ 10.5f}'.format(digit=1.0/3)
 
'''
������Ϳ��Զ���һ��__format__()����������������ʽ���Լ���
�������һ����ʽ��ָʾ����Ϊ������
'''
def __format__(self, format_spec):
 if isinstance(format_spec, unicode):
  return unicode(str(self))
 else:
  return str(self) 
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