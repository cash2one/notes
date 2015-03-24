#!/bin/bash
#------------------------------------------------------------------------------------
#The if statement has the following syntax:
#if commands; then
#commands
#[elif commands; then
#commands...]
#[else
#commands]
#fi
#
#
#λ�ò��� $1�� $2,..., $N��$#�����������еĲ��������� $0�����˽ű������֣�
if [ ! $#==2 ]; then
    echo "Usage: $0 para1 para2"
    exit 0
fi
#
if [$para1 -le $para2]; then
    echo "para1 <= para2"
else
    echo "para > para2"
fi
#
#shell �����ʹ�õ���if������жϲ���
#�Cb ��file���ڲ����ǿ��ļ�ʱ������
#-c ��file���ڲ������ַ��ļ�ʱ������
#-d ��pathname���ڲ�����һ��Ŀ¼ʱ������
#-e ��pathnameָ�����ļ���Ŀ¼����ʱ������
#-f ��file���ڲ����������ļ�ʱ������
#-g ����pathnameָ�����ļ���Ŀ¼���ڲ���������SGIDλʱ����Ϊ��
#-h ��file���ڲ����Ƿ��������ļ�ʱ�����棬��ѡ����һЩ��ϵͳ����Ч
#-k ����pathnameָ�����ļ���Ŀ¼���ڲ��������ˡ�ճ�͡�λʱ������
#-p ��file���ڲ���������ܵ�ʱ����Ϊ��
#-r ����pathnameָ�����ļ���Ŀ¼���ڲ��ҿɶ�ʱ����Ϊ��
#-s ��file�����ļ���С����0ʱ������
#-u ����pathnameָ�����ļ���Ŀ¼���ڲ���������SUIDλʱ������
#-w ����pathnameָ�����ļ���Ŀ¼���ڲ��ҿ�ִ��ʱ�����档һ��Ŀ¼Ϊ���������ݱ����ʱ�Ȼ
#   �ǿ�ִ�еġ�
#-o ����pathnameָ�����ļ���Ŀ¼���ڲ��ұ��ӵ�ǰ���̵���Ч�û�ID��ָ�����û�ӵ��ʱ����
#   �档

#UNIX Shell ����Ƚ��ַ�д����
#-eq   ����
#-ne    ������
#-gt    ����
#-lt    С��
#-le    С�ڵ���
#-ge   ���ڵ���
#-z    �մ�
#=    �����ַ����
#!=    �����ַ�����
#-n    �ǿմ�
#-------------------------------------------------------------------------
#��Ϊ��ϸ��˵����
#�����                     ����                          ʾ��

#�ļ��Ƚ������
#-e filename     ��� filename ���ڣ���Ϊ��            [ -e /var/log/syslog ]
#-d filename     ��� filename ΪĿ¼����Ϊ��          [ -d /tmp/mydir ]
#-f filename     ��� filename Ϊ�����ļ�����Ϊ��      [ -f /usr/bin/grep ]
#-L filename     ��� filename Ϊ�������ӣ���Ϊ��      [ -L /usr/bin/grep ]
#-r filename     ��� filename �ɶ�����Ϊ��            [ -r /var/log/syslog ]
#-w filename     ��� filename ��д����Ϊ��            [ -w /var/mytmp.txt ]
#-x filename     ��� filename ��ִ�У���Ϊ��          [ -L /usr/bin/grep ]

#filename1 -nt filename2 ��� filename1 �� filename2 �£���Ϊ�� 
#[ /tmp/install/etc/services -nt /etc/services ]
#filename1 -ot filename2   ��� filename1 �� filename2 �ɣ���Ϊ��  
#[ /boot/bzImage -ot arch/i386/boot/bzImage ]

#�ַ����Ƚ������ ����ע�����ŵ�ʹ�ã����Ƿ�ֹ�ո����Ҵ���ĺ÷�����
#-z string           ��� string ����Ϊ�㣬��Ϊ��         [ -z $myvar ]
#-n string           ��� string ���ȷ��㣬��Ϊ��         [ -n $myvar ]
#string1 = string2   ��� string1 �� string2 ��ͬ����Ϊ�� [ $myvar = one two three ]
#string1 != string2  ��� string1 �� string2 ��ͬ����Ϊ�� [ $myvar != one two three ]

#�����Ƚ������
#num1 -eq num2       ����        [ 3 -eq $mynum ]
#num1 -ne num2       ������      [ 3 -ne $mynum ]
#num1 -lt num2       С��        [ 3 -lt $mynum ]
#num1 -le num2       С�ڻ����  [ 3 -le $mynum ]
#num1 -gt num2       ����        [ 3 -gt $mynum ]
#num1 -ge num2       ���ڻ����  [ 3 -ge $mynum ]