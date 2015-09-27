#_*_coding:UTF-8_*_
'''
http://www.cnblogs.com/coser/archive/2011/12/17/2291160.html


'''

import struct
import binascii
import ctypes

'''                                                                                  |
�����У����ȶ�����һ��Ԫ�����ݣ�����int��string��float�����������ͣ�Ȼ������struct |
���󣬲��ƶ���format��I3sf����I ��ʾint��3s��ʾ�����ַ����ȵ��ַ�����f ��ʾ float�����|
ͨ��struct��pack��unpack���д���ͽ����ͨ�����������Է��֣�value��pack֮��ת��Ϊ|
��һ�ζ������ֽڴ�����unpack���԰Ѹ��ֽڴ���ת����һ��Ԫ�飬����ֵ��ע����Ƕ���float|
�ľ��ȷ����˸ı䣬������һЩ�������ϵͳ�ȿ͹������������ġ����֮���������ռ�õ��� |
������C�����е�structʮ�����ơ�                                                      |
�����
Original values: (1, 'abc', 2.7) 
Format string : I3sf 
Uses : 12 bytes 
Packed Value : 0100000061626300cdcc2c40 
Unpacked Type : <type 'tuple'>  Value: (1, 'abc', 2.700000047683716)
'''
values = (1, 'abc', 2.7)
s = struct.Struct('I3sf')
packed_data = s.pack(*values)
unpacked_data = s.unpack(packed_data)
 
print 'Original values:', values
print 'Format string :', s.format
print 'Uses :', s.size, 'bytes'
print 'Packed Value :', binascii.hexlify(packed_data)
print 'Unpacked Type :', type(unpacked_data), ' Value:', unpacked_data


'''                                                                                  |
pack�������Ƕ��������ݽ��в��������´�����һ���ڴ�ռ����ڷ��أ�Ҳ����˵����ÿ��pack |
�������ڴ��з������Ӧ���ڴ���Դ������ʱ��һ�ֺܴ�������˷ѡ�structģ�黹�ṩ��     |
pack_into() �� unpack_from()�ķ�������������������⣬Ҳ���Ƕ�һ���Ѿ���ǰ����õ�   |
buffer�����ֽڵ���䣬������ÿ�ζ�����һ���¶�����ֽڽ��д洢��                     |
�����
Before : 000000000000000000000000 
After pack: 0100000061626300cdcc2c40 
After unpack: (1, 'abc', 2.700000047683716) 
'''
values = (1, 'abc', 2.7)
s = struct.Struct('I3sf')
prebuffer = ctypes.create_string_buffer(s.size)
print 'Before :',binascii.hexlify(prebuffer)
s.pack_into(prebuffer,0,*values)
print 'After pack:',binascii.hexlify(prebuffer)
unpacked = s.unpack_from(prebuffer,0)
print 'After unpack:',unpacked

'''                                                                                  |
pack_into��unpack_from�������Ƕ�string buffer������в��������ṩ��offset�������û���|
��ͨ��ָ����Ӧ��offset��ʹ��Ӧ�Ĵ����ø��������磬���ǿ��԰Ѷ������pack��һ�� |
buffer���棬Ȼ��ͨ��ָ����ͬ��offset����unpack��                                     |
�����
Before : 0000000000000000000000000000000000000000 
After pack: 0100000061626300cdcc2c406465666765000000 
(1, 'abc', 2.700000047683716) 
('defg', 101)
'''
values1 = (1, 'abc', 2.7)
values2 = ('defg',101)
s1 = struct.Struct('I3sf')
s2 = struct.Struct('4sI')
 
prebuffer = ctypes.create_string_buffer(s1.size+s2.size)
print 'Before :',binascii.hexlify(prebuffer)
s1.pack_into(prebuffer,0,*values1)
s2.pack_into(prebuffer,s1.size,*values2)
print 'After pack:',binascii.hexlify(prebuffer)
print s1.unpack_from(prebuffer,0)
print s2.unpack_from(prebuffer,s1.size)




