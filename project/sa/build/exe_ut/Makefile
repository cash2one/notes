# 本次构建要生成的exe文件
EXE = sa_ut.out
EXES_DIR = $(ROOT)/build/exe_ut

# 本次构建要生成的lib
LIB = 
LIB_DIR = 

# 本次构建所依赖的头文件路径(公共头文件路径在总的makefile中定义) 
# 无需加 -I
INCLUDE_DIRS += $(ROOT)/include

# 本次构建所依赖的库，库名字前无需加-l，路径要加-L			   
LINK_LIBS += sa
LINK_LIBS_DIRS += -L$(ROOT)/build/libs

# 中间文件存储路径
OBJS_DIR =

# now begin
include $(ROOT)/build/make.rule