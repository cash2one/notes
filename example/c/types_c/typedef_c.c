/*-----------------------------------------------------------------------------------
 typedef����, ���typedef, Ϊ�������ʹ���һ���µ�����. typedef��ʹ�÷�������:
     typedef existing_type new_type_name ;
 ע��:typedef���������µ�����. ������Ϊ�����������һ��ͬ����.
 
     typedef unsigned int WORD; 
 ������һ��unsigned int��ͬ���, ����ΪWORD, ��������κ���Ҫint��������ʹ��WORD.

 ----> typedef������,ָ��
 ���ǿ��Բ��������������ظ�������81���ַ�Ԫ�ص�����:
     char line[81]; 
     char text[81];
 ����һ��typedef, ÿ��Ҫ�õ���ͬ���ͺʹ�С������ʱ, ��������:
     typedef char Line[81]; 
     Line text, secondline;

 ͬ��, ������������������ָ���﷨:
     typedef char * pstr; 
     pstr str = "abc";
     int mystrcmp(pstr, pstr);

 ----> typedef�ͺ���
 /notes/example/c/pointer_c/pointer_base_c.c



 ----------------------------------------------------------------------------------*/
