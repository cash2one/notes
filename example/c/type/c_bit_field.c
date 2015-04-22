/*******************************************************************************

λ��(bit-field)
  ����λΪ��λ������ṹ��(��������)�еĳ�Ա������ռ�Ŀռ䡣����λ�εĽṹ��(������)
  ��Ϊλ�νṹ������λ�νṹ���ܹ���ʡ�ռ䣬�ַ����ڲ�����

λ�εĶ����ʽΪ:
  type  [var]: digits

  ����typeֻ��Ϊint��unsigned int��signed int��������(int���ܲ��ܱ�ʾ�����ӱ�������
  ��������VC��int��Ĭ����signed int���ܹ���ʾ����)��λ������var�ǿ�ѡ������������ʡ�ԡ�
  digits��ʾ��λ����ռ�Ķ�����λ����

����һ��λ�νṹ������������δ���ȥ���壺

         struct node
         {
             unsigned int a:4;       //λ��a��ռ4λ
             unsigned int  :0;       //����λ�Σ�ռ0λ
             unsigned int b:4;       //λ��b��ռ4λ
             int c:32;           //λ��c��ռ32λ
             int  :6;               //����λ�Σ�ռ6λ
         };

 һ.λ�ε�ʹ��
    1)λ�ε�����ֻ����int��unsigned int��signed int�������ͣ�������char�ͻ��߸����ͣ�
      signed char��unsigned char linux�ں��������char short�ȣ���gcc�й�??
    2)λ��ռ�Ķ�����λ�����ܳ����û����������ܱ�ʾ�����λ����������VC��int��ռ4
    ���ֽڣ���ô���ֻ����32λ��
    3)����λ�β��ܱ����ʣ����ǻ�ռ�ݿռ䣻
    4)���ܶ�λ�ν���ȡ��ַ������
    5)��λ��ռ�Ķ�����λ��Ϊ0�������λ�α���������λ�Σ���һ��λ�δ���һ��λ�δ�
    ����Ԫ(�����λ�δ洢��Ԫ��������VC��������4���ֽ�)��ʼ��ţ�
    6)��λ�γ����ڱ��ʽ�У�����Զ����������������Զ�ת��Ϊint�ͻ���unsigned int��
    7)��λ�θ�ֵʱ����ò�Ҫ����λ�����ܱ�ʾ�����Χ��������ܻ�������벻���Ľ����
    8)λ�β��ܳ����������ʽ��
 
 ��.λ�νṹ���ڴ��еĴ洢��ʽ
    1)���һ��λ�δ洢��Ԫ�ܹ��洢����λ�νṹ�е����г�Ա����ôλ�νṹ�е�����
    ��Աֻ�ܷ���һ��λ�δ洢��Ԫ�У����ܷ�������λ�δ洢��Ԫ�У����һ��λ�δ洢
    ��Ԫ����������λ�νṹ�е����г�Ա����ô��ʣ���λ�δ���һ��λ�δ洢��Ԫ��ʼ
    ��š�(��VC��λ�δ洢��Ԫ�Ĵ�С��4�ֽ�).
 
    2)���һ��λ�νṹ��ֻ��һ��ռ��0λ������λ�Σ���ֻռ1��0�ֽڵĿռ�(C������
    ��ռ0�ֽڣ���C++��ռ1�ֽ�)�����������κ�����£�һ��λ�νṹ��ռ�Ŀռ�������
    һ��λ�δ洢��Ԫ�Ĵ�С��

 ******************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node
{
    unsigned int a:1;      /* ����һ����0λ��λ�Σ�������ռ4Byte */
}S; 

typedef struct node1      /* ��C++��ռ1�ֽڵĿռ� ����C��ռ0�ֽ�  */
{
    unsigned int :0;
}S1;

typedef struct node2
{
    unsigned int a:1;
    unsigned int  :0;     /* ��һ��λ�η���һ���µ�λ�δ洢��Ԫ ������ռ4+4=8Byte  */
    unsigned c:32;         
}S2;

typedef struct node3
{
    unsigned int a:4;
    unsigned int  :0;
    int :6;               /* ���λ�η���һ���µ�λ�δ洢��Ԫ  */
    unsigned c:32;       /* ����6+32>32����λ��cҲ����һ���µ�λ�δ洢��Ԫ������ռ4+4+4=12Byte  */
}S3;

typedef struct node4  
{
    unsigned int a:1;
    char b;               /* ��һ��λ�δ洢��Ԫ���ܹ��������еĳ�Ա������ռ4Byte  */
    int c:1;
    int d:2;
    unsigned int e:2;
}S4;

struct _bf1
{
    unsigned char a:1;
    unsigned char b:1;
    unsigned char c:1;
    
};

struct _bf2
{
    unsigned short a:1;
    unsigned short b:1;
    unsigned short c:1;
    
};

struct _bf3
{
    unsigned short a:1;
    unsigned short b:1;
    unsigned short c:1;
    
};

struct _bf4
{
    union
    {
        struct _bf3 bf3;
        int a;
    };
};


void bit_field_test01()
{
    struct _bf1 bf1;
    struct _bf2 bf2;
    
    printf("\r\nsizeof(bf1) :%d",sizeof(bf1));
    printf("\r\nsizeof(bf2) :%d",sizeof(bf2));
    
}

void bit_field_test02()
{
    struct _bf4 bf4 = {0};
    
    bf4.bf3.a = 1;
    printf("\r\nbf3.a :0x%x",bf4.a);

    bf4.a = 0;
    bf4.bf3.b= 1;
    printf("\r\nbf3.a :0x%x",bf4.a);    
}


void dump_native_bits_storage_layout(unsigned char *p, int bytes_num)
{
    union flag_t 
    {
        unsigned char c;
        struct base_flag_t 
        {
            unsigned int p7:1,
                         p6:1,
                         p5:1,
                         p4:1,
                         p3:1,
                         p2:1,
                         p1:1,
                         p0:1;
        } base;
    } f;
    int i;

    for (i = 0; i < bytes_num; i++) 
    {
        f.c = *(p + i);
        printf("%p: %d%d%d%d%d%d%d%d \n",p + i,f.base.p7,f.base.p6,f.base.p5,f.base.p4,
                                         f.base.p3,f.base.p2,f.base.p1,f.base.p0);
    }
    printf("\n");
}

struct short_flag_t2 {
    unsigned short a : 7,
                   b : 10;
};

struct short_flag_t3 {
    unsigned short a : 2,
                   b : 3;
}; 

/*
layout test :
0x22ccd4: 10001110
0x22ccd5: 00000000
0x22ccd6: 10100111
0x22ccd7: 11000000

0x22ccd2: 01001000
0x22ccd3: 00000000
*/
int bits_storage_layout_test()
{
    struct short_flag_t2 s;
    struct short_flag_t3 s3;
    
    memset(&s, 0, sizeof(s));
    s.a = 113; /* 0111 0001 */
    s.b = 997; /* 0011 1110 0101 */
    printf("\nlayout test :\n");
    dump_native_bits_storage_layout((unsigned char*)&s, sizeof(s));

    memset(&s3, 0, sizeof(s3));
    s3.a = 2; /* 10 */
    s3.b = 4; /* 100 */
    dump_native_bits_storage_layout((unsigned char*)&s3, sizeof(s3));
    
    return 0;
}


struct bool_flag_t {
    _Bool a : 1,
          b : 1;
};

struct char_flag_t {
    unsigned char a : 2,
                  b : 3;
};

struct short_flag_t {
    unsigned short a : 2,
                   b : 3;
};

struct int_flag_t {
    int a : 2,
        b : 3;
};

/* output: 1 1 2 4 4 */
int bits_size_test()
{
    printf("bits size test:\n");
    printf("%ld ", sizeof(struct bool_flag_t));
    printf("%ld ", sizeof(struct char_flag_t));
    printf("%ld ", sizeof(struct short_flag_t));
    printf("%ld ", sizeof(struct short_flag_t2));    
    printf("%ld\n", sizeof(struct int_flag_t));

    return 0;
}


int main(int argc, char *argv[])
{
    S4 s4;
    s4.a=1;
    s4.c=1;
    s4.d=2;              
    s4.e=3;
    printf("%d %d %d %d\n",s4.a,s4.c,s4.d,s4.e);
    printf("%d %d %d %d %d\n",sizeof(S),sizeof(S1),sizeof(S2),sizeof(S3),sizeof(S4));

    bit_field_test01();
    bit_field_test02();
    bits_storage_layout_test();
    bits_size_test();
    return 0;
}


