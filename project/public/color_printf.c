#include <stdio.h>

/*-----------------------------------------------------------------------------------
 �����ַ���ͨ�ø�ʽ����: Esc[{attr1};...;{attrn}m

 ����:
 Esc ��ת���ַ�, ��ֵΪ"\033";
 [ �ǳ�������������;
 {attr1};...{attrn} ����������, ͨ������һ�����ض���������ִ���, ÿ������֮���÷ֺŷָ�;
 m �������泣���ַ�m;

 �����б�����:
 1. ͨ�ø�ʽ����:
 0 ������������;  1 ����/�Ӵ�;  2 ����;  4 �»���;  5 ��˸;  7 ��ת;  8 ����;

 2. ������ɫ
 30 ��ɫ;  31 ��ɫ;  32 ��ɫ;  33 ��ɫ;  34 ��ɫ;  35 Ʒ��;  36 ��ɫ;  37 ��ɫ

 3. ����ɫ:
 40 ��ɫ;  41 ��ɫ;  42 ��ɫ;  43 ��ɫ;  44 ��ɫ;  45 Ʒ��;  46 ��ɫ;  47 ��ɫ
 ----------------------------------------------------------------------------------*/
int main()
{
    printf("\033[1;40;32m__This text is xxx__\033[0m\n");
    printf("\033[2;40;32m__This text is xxx__\033[0m\n");
    printf("\033[3;40;32m__This text is xxx__\033[0m\n");
    printf("\033[4;40;32m__This text is xxx__\033[0m\n");
    printf("\033[5;40;32m__This text is xxx__\033[0m\n");
    printf("\033[6;40;32m__This text is xxx__\033[0m\n");
    printf("\033[7;40;32m__This text is xxx__\033[0m\n");

    printf("\033[1;4;40;32m__This text is xxx__\033[0m\n");

	
    printf("\033[40;30m__This text is xxx__\033[0m\n");
    printf("\033[40;31m__This text is xxx__\033[0m\n");
    printf("\033[40;32m__This text is xxx__\033[0m\n");
    printf("\033[40;33m__This text is xxx__\033[0m\n");
    printf("\033[40;34m__This text is xxx__\033[0m\n");
    printf("\033[40;35m__This text is xxx__\033[0m\n");
    printf("\033[40;36m__This text is xxx__\033[0m\n");
    printf("\033[40;37m__This text is xxx__\033[0m\n");

    printf("\033[41;30m__This text is xxx__\033[0m\n");
    printf("\033[41;31m__This text is xxx__\033[0m\n");
    printf("\033[41;32m__This text is xxx__\033[0m\n");
    printf("\033[41;33m__This text is xxx__\033[0m\n");
    printf("\033[41;34m__This text is xxx__\033[0m\n");
    printf("\033[41;35m__This text is xxx__\033[0m\n");
    printf("\033[41;36m__This text is xxx__\033[0m\n");
    printf("\033[41;37m__This text is xxx__\033[0m\n");

    printf("\033[42;30m__This text is xxx__\033[0m\n");
    printf("\033[42;31m__This text is xxx__\033[0m\n");
    printf("\033[42;32m__This text is xxx__\033[0m\n");
    printf("\033[42;33m__This text is xxx__\033[0m\n");
    printf("\033[42;34m__This text is xxx__\033[0m\n");
    printf("\033[42;35m__This text is xxx__\033[0m\n");
    printf("\033[42;36m__This text is xxx__\033[0m\n");
    printf("\033[42;37m__This text is xxx__\033[0m\n");

    printf("\033[43;30m__This text is xxx__\033[0m\n");
    printf("\033[43;31m__This text is xxx__\033[0m\n");
    printf("\033[43;32m__This text is xxx__\033[0m\n");
    printf("\033[43;33m__This text is xxx__\033[0m\n");
    printf("\033[43;34m__This text is xxx__\033[0m\n");
    printf("\033[43;35m__This text is xxx__\033[0m\n");
    printf("\033[43;36m__This text is xxx__\033[0m\n");
    printf("\033[43;37m__This text is xxx__\033[0m\n");

    printf("\033[44;30m__This text is xxx__\033[0m\n");
    printf("\033[44;31m__This text is xxx__\033[0m\n");
    printf("\033[44;32m__This text is xxx__\033[0m\n");
    printf("\033[44;33m__This text is xxx__\033[0m\n");
    printf("\033[44;34m__This text is xxx__\033[0m\n");
    printf("\033[44;35m__This text is xxx__\033[0m\n");
    printf("\033[44;36m__This text is xxx__\033[0m\n");
    printf("\033[44;37m__This text is xxx__\033[0m\n");

    printf("\033[45;30m__This text is xxx__\033[0m\n");
    printf("\033[45;31m__This text is xxx__\033[0m\n");
    printf("\033[45;32m__This text is xxx__\033[0m\n");
    printf("\033[45;33m__This text is xxx__\033[0m\n");
    printf("\033[45;34m__This text is xxx__\033[0m\n");
    printf("\033[45;35m__This text is xxx__\033[0m\n");
    printf("\033[45;36m__This text is xxx__\033[0m\n");
    printf("\033[45;37m__This text is xxx__\033[0m\n");

    printf("\033[46;30m__This text is xxx__\033[0m\n");
    printf("\033[46;31m__This text is xxx__\033[0m\n");
    printf("\033[46;32m__This text is xxx__\033[0m\n");
    printf("\033[46;33m__This text is xxx__\033[0m\n");
    printf("\033[46;34m__This text is xxx__\033[0m\n");
    printf("\033[46;35m__This text is xxx__\033[0m\n");
    printf("\033[46;36m__This text is xxx__\033[0m\n");
    printf("\033[46;37m__This text is xxx__\033[0m\n");

	printf("\033[47;30m__This text is xxx__\033[0m\n");
    printf("\033[47;31m__This text is xxx__\033[0m\n");
    printf("\033[47;32m__This text is xxx__\033[0m\n");
    printf("\033[47;33m__This text is xxx__\033[0m\n");
    printf("\033[47;34m__This text is xxx__\033[0m\n");
    printf("\033[47;35m__This text is xxx__\033[0m\n");
    printf("\033[47;36m__This text is xxx__\033[0m\n");
    printf("\033[47;37m__This text is xxx__\033[0m\n");

	return 0;
}
