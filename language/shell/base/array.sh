linux shell�ڱ�̷����windows ������ǿ��̫�࣬��������ѭ�������㡣�Ѿ��������ͷ��涼�ǲ��ܱȽϵġ� �����Ǹ�����ʹ��ʱ�򣬶��������鷽��һЩ�������е��ܽᡣ
 
1.���鶨��
 
[chengmo@centos5 ~]$ a=(1 2 3 4 5)
[chengmo@centos5 ~]$ echo $a
1
 
һ�����ű�ʾ�����飬����Ԫ���á��ո񡱷��ŷָ��
 
2.�����ȡ�븳ֵ
�õ����ȣ�
[chengmo@centos5 ~]$ echo ${#a[@]}
5
��${#������[@��*]} ���Եõ����鳤��
��ȡ��
[chengmo@centos5 ~]$ echo ${a[2]} 
3
[chengmo@centos5 ~]$ echo ${a[*]} 
1 2 3 4 5   
��${������[�±�]} �±��Ǵ�0��ʼ  �±��ǣ�*����@ �õ�������������
��ֵ:
[chengmo@centos5 ~]$ a[1]=100
[chengmo@centos5 ~]$ echo ${a[*]} 
1 100 3 4 5
 
[chengmo@centos5 ~]$ a[5]=100     
[chengmo@centos5 ~]$ echo ${a[*]}
1 100 3 4 5 100
ֱ��ͨ�� ������[�±�] �Ϳ��Զ���������ø�ֵ������±겻���ڣ��Զ������һ������Ԫ��
ɾ��:
[chengmo@centos5 ~]$ a=(1 2 3 4 5)
[chengmo@centos5 ~]$ unset a
[chengmo@centos5 ~]$ echo ${a[*]}
[chengmo@centos5 ~]$ a=(1 2 3 4 5)
[chengmo@centos5 ~]$ unset a[1]   
[chengmo@centos5 ~]$ echo ${a[*]} 
1 3 4 5
[chengmo@centos5 ~]$ echo ${#a[*]}
4
ֱ��ͨ����unset ����[�±�] ���������Ӧ��Ԫ�أ������±꣬����������ݡ�
 
 
3.����ʹ��
��Ƭ:
[chengmo@centos5 ~]$ a=(1 2 3 4 5)
[chengmo@centos5 ~]$ echo ${a[@]:0:3}
1 2 3
[chengmo@centos5 ~]$ echo ${a[@]:1:4}
2 3 4 5
[chengmo@centos5 ~]$ c=(${a[@]:1:4})
[chengmo@centos5 ~]$ echo ${#c[@]}
4
[chengmo@centos5 ~]$ echo ${c[*]} 
2 3 4 5
ֱ��ͨ�� ${������[@��*]:��ʼλ��:����} ��Ƭԭ�����飬�������ַ������м��á��ո񡱷ֿ������������ϡ�()�������õ���Ƭ���飬�������ӣ�c ����һ�������ݡ�
�滻:
[chengmo@centos5 ~]$ a=(1 2 3 4 5)    
[chengmo@centos5 ~]$ echo ${a[@]/3/100}
1 2 100 4 5
[chengmo@centos5 ~]$ echo ${a[@]}
1 2 3 4 5
[chengmo@centos5 ~]$ a=(${a[@]/3/100}) 
[chengmo@centos5 ~]$ echo ${a[@]}     
1 2 100 4 5
���÷����ǣ�${������[@��*]/�����ַ�/�滻�ַ�} �ò�������ı�ԭ���������ݣ������Ҫ�޸ģ����Կ��������ӣ����¶������ݡ�