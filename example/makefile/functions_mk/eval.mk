#$(eval _text)                                                                       |
#eval����ʹ��Makefile���ж�̬���Ե����ԡ�eval����ʹ��make����һ�ν���_text���. eval |
#��������ֵΪ���ַ�����

.PHONY: all
sources = foo.c bar.c baz.s ugh.h
$(eval sources := $(filter %.c %.s, $(sources)))

all:
	@echo $(sources)
	
#make
#main.c
