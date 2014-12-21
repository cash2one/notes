/*******************************************************************************
�����������Ҫ�����ڴ���߶������ÿ��ֻȡ��һʱ����������������(union)��
1)��������һ���ṹ��
2)�������г�Ա����ڻ���ַ��ƫ������Ϊ0��
3)�˽ṹ�ռ�Ҫ���㹻������"��"�ĳ�Ա��
4)����뷽ʽҪ�ʺ��������еĳ�Ա��
�������������������
�����������е����г�Ա�ǹ���һ���ڴ�ģ����ÿ����Ա�Ĵ���׵�ַ��������������
���Ļ���ַ��ƫ����Ϊ0�������г�Ա���׵�ַ����һ���ġ�Ϊ��ʹ�����г�Ա�ܹ�����һ��
�ڴ棬��˸ÿռ�����㹻������Щ��Ա�����ĳ�Ա��������䡰���뷽ʽҪ�ʺ�������
�еĳ�Ա����ָ�����������г�Ա��������뷽ʽ��
*******************************************************************************/

#include<stdlib.h>
#include<stdio.h>

struct _cat
{
    int c_age;
	int c_weight;
};

struct _dog
{
    int d_age;
	int d_weight;
	int d_colour;
};

struct peta
{
    union
    {
    struct _cat p_cat;
    struct _dog p_dog;
    };
	int p_type;
};

struct petb
{
    union
    {
    struct _cat p_cat;
    struct _dog p_dog;
    }u;
	int p_type;
};

int main()
{
    struct peta peta;
	struct petb petb;

	printf("\r\nsizeof(struct peta) :%d",sizeof(struct petb));	
	printf("\r\nsizeof(petb.u)      :%d",sizeof(petb.u));
	printf("\r\nsizeof(petb.u.p_cat):%d",sizeof(petb.u.p_cat));
	printf("\r\nsizeof(petb.u.p_dog):%d",sizeof(petb.u.p_dog));

	printf("\r\nsizeof(peta.p_cat):%d",sizeof(peta.p_cat));
	printf("\r\nsizeof(peta.p_dog):%d",sizeof(peta.p_dog));
	
	printf("\r\nAddr peta       :%p",&peta);
	printf("\r\nAddr peta.p_cat :%p",&peta.p_cat);
	printf("\r\nAddr peta.p_dog :%p",&peta.p_dog);

	return 0;	
}

