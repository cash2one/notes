-------------------------------------------------------------------------------------
# http://www.blogjava.net/jasmine214--love/archive/2012/01/10/368191.html
# ��Makefile��дshell�����е���죬�Ͳ�ͬ��shell�﷨��̫һ����������˽⣬��Makefile��
# Ī����������ܽ���һЩ��

# 1 Makefile�ļ���Ŀ����ð�ź������һ�еĴ������shell���롣
# eg��
xx = xx1      # ������makefile����
yy: xx = xx2  # ������makefile���룬makefile���������ֵʱ��'='���������ո�
yy:
    xx=xx3    # ֻ��������shell���� ��shell������=���������пո�Ŷ��
# ��һ�����⣺
# xx=$(shell ����Ĵ���Ҳ��shell����)

# 2 Makefile�е�shell��ÿһ����һ�����̣���ͬ��֮�����ֵ���ܴ��ݡ����ԣ�Makefile�е�
# shell���ܶ೤ҲҪд��һ�С�
# eg��
SUBDIR=src example
all:
    @for subdir in $(SUBDIR); # ����������һ��shell
    do/
        echo "building " $$subdir; 
    done
3��Makefile�еı�����$��ͷ�� ���ԣ�Ϊ�˱����shell�ı�����ͻ��shell�ı�����$$��ͷ
eg1���ӵ�ǰĿ¼·������ȡ�� /application �� /base_class ֮ǰ�Ĳ���
PROJECT_ROOT_DIR = $(shell pwd | awk -F'/application|/base_class' '{print $$1}')
eg2��������$$subdir����shell�еı����� ��$(SUBDIR)��Makefile���еı���

=============================================================================================
1����Makefile��ֻ����target�е���Shell�ű��������ط��ǲ�������ġ��������´������û���κ������

VAR="Hello"
echo "$VAR"

all:
   .....
���ϴ����κ�ʱ�򶼲��������û����target�ڣ�������������Ϊ���£�

VAR="Hello"

all:
    echo "$VAR"
    .....
���ϴ��룬��make all��ʱ�򽫻�ִ��echo���

2����Makefile��ִ��shell���һ�д���һ��������ִ�С���Ҳ��Ϊʲô�ܶ�Makefile���кܶ��е�ĩβ���ǡ�;  \�����Դ�����֤������һ�ж����Ƕ��У�����Makefile������һ��������ִ�У����磺

SUBDIR=src example
all:
    @for subdir in $(SUBDIR); \
    do\
        echo "building "; \
    done
�������Կ���forѭ����ÿ�ж����ԡ�; \����β�ġ�

3��Makefile��������$��ͷ�ĵ��ʶ��ᱻ���ͳ�Makefile�еı������������Ҫ����shell�еı���������������ʽ��ê����λ$��������Ҫ������$���ţ�$$����ʵ�����£�

PATH="/data/"

all:
    echo ${PATH}
    echo $$PATH
�����еĵ�һ��${PATH}���õ���Makefile�еı�����������shell�е�PATH�����������������õ���Shell�е�PATH����������

     �����������Makefile����shellӦ��ע��ĵط���дMakefileһ��Ҫע�⡣