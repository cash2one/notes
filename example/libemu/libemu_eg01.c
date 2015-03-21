/*libemu test*/
#include <emu/emu.h>
#include <emu/emu_shellcode.h>
#include <emu/emu_memory.h>

struct emu *emu;

char shellcode[] =  
    	"\xbe\x1f\x5e\x89\x76\x09\x31\xc0\x88\x46\x08\x89\x46\x0d\xb0\x0b"  
    	"\x89\xf3\x8d\x4e\x09\x8d\x56\x0d\xcd\x80\x31\xdb\x89\xd8\x40\xcd"  
    	"\x80\xe8\xdc\xff\xff\xff\x2f\x62\x69\x6e\x2f\x6c\x73\x00\xc9\xc3"; 

int main()
{
	emu = emu_new();
	if ( emu_shellcode_test(emu, (uint8_t *)shellcode, 48) >= 0 )
        {
        	fprintf(stderr, "suspecting shellcode\n");
        }
	emu_free(emu);
	return 0;
}

/*
git clone git://git.carnivore.it/libemu.git libemu
cd libemu
autoreconf -v -i
./configure --prefix=/opt/dionaea
make install
*/






















































/*
ʹ��python���shellcode
��С����  ��������
����python��������һ��Ī�����˷ܣ����˾��ñ��Խ��Խ�ã���IT��Ա�������21���Ϳ󹤵Ľ��죬����д��Խ��ֻ�ܴ�������ڵĶ࣬�����������ڵĿ��м�ֵ���ǿ��Ի�ȡ����ļ�ֵ���ο����ڶ���������������ʣ�µĿ�����

    ����DVLabs��һƪ���¡�Shellcode Detection Using Python�����㶯��ʵ����һ�¡�Dvlabs˵:�������ռ��˴������ļ����ĵ���Ҫʶ�����Щ�ĵ���Щ�Ƕ���ģ���Ҫ�������˹�����������Ϊ�˼��ٹ�������������Զ��������ķ������Զ��������ĵ���������Ҫ����֮һ��shellcode��⣬������ĵ����Ƿ����shellcode����

    DVLabs�������ᵽ������python���shellcode��⹤�ߣ�Pylibemu��Pylibscizzle��

Pylibemu ��װ��Libemu http://libemu.carnivore.it/���ṩ�˸���Ĺ��ܣ�����û������ʹ�õĸ��ӳ̶ȡ�Pylibemuһ����Ҫ�Ĺ��ܺ�����test(),����������Կ���shellcode����windows API��Ϣ��

Pylibemuʵ�ʲ��ԣ�

    ��װPylibemu��������https://github.com/buffer/pylibemu��������libemu

git clone git://git.carnivore.it/libemu.git

windowsƽ̨��git��ʹ��msysgit��http://code.google.com/p/msysgit/downloads/list��

    �ҵĲ��Ի�����windows 7 ����windowsƽ̨��ʹ��libemu��Ҫ��װCygwin������Ҫ���°���

- gcc;

- make;

- automake;

- libtool;

- gettext-devel;

- python

    �����غ�libemu���õ�ָ��Ŀ¼�£������windows������Cygwin�Ļ���������

    ��configure.ac�����AC_CONFIG_MACRO_DIR([m4]),��������:

# -*- mode: m4; -*-

# -*- Autoconf -*-

# Process this file with autoconf to produce a configure script.

# $Id$

AC_CONFIG_MACRO_DIR([m4])

AC_PREREQ(2.59)

....

    ��Cygwin���������л���libemuĿ¼����autoreconf -v �Ci

    ɾ����configure.ac����ӵ�AC_CONFIG_MACRO_DIR([m4])

    ��Cygwin������������./configure --prefix=/opt/libemu��������ʾ����

checking for cargos-lib.h... no

configure: creating ./config.status

.in'ig.status: error: cannot find input file: `Makefile

    ����취�ǣ�����notpad++��configure�ļ�ת��Ϊwindows��ʽ�����档�ڽ�configure�ļ�ת����linux��ʽ���档

��������./configure --prefix=/opt/libemu

    ����make���ֻ�������´���

cc1: warnings being treated as errors

userhooks.c: In function ��append��:

userhooks.c:168:3: error: array subscript has type ��char��

Makefile:365: recipe for target `sctest-userhooks.o' failed

make[3]: *** [sctest-userhooks.o] Error 1

make[3]: Leaving directory `/cygdrive/f/linux/libemu/tools/sctest'

Makefile:264: recipe for target `all-recursive' failed

make[2]: *** [all-recursive] Error 1

make[2]: Leaving directory `/cygdrive/f/linux/libemu/tools'

Makefile:353: recipe for target `all-recursive' failed

make[1]: *** [all-recursive] Error 1

make[1]: Leaving directory `/cygdrive/f/linux/libemu'

Makefile:260: recipe for target `all' failed

make: *** [all] Error 2

    ����������޸�tools\sctestĿ¼��userhooks.c��168��Ϊ

if ( isprint((int)data[i]))// || isblank(data[i]))

    ����make install

running build

running build_ext

    ��Pylibeum��ѹ��ָ��Ŀ¼����Cygwin��������

    ����python setup.py build

running build

running build_ext

    ����python setup.py install

running install

running build

running build_ext

building 'pylibemu' extension

...

copying build/lib.cygwin-1.7.9-i686-2.6/pylibemu.dll -> /usr/lib/python2.6/site-packages

running install_egg_info

Writing /usr/lib/python2.6/site-packages/pylibemu-0.1.4-py2.6.egg-info

    �ǳ�˳���İ�װ�ɹ���,��cygwin������python,����python����ʽ����������

Import pylibemu

    ��������鷢����,��ʾ���´���:

>>> import pylibemu

Traceback (most recent call last):

  File "<stdin>", line 1, in <module>

ImportError: No such file or directory

    ������⻨���ҽ�һ�������ʱ��Ž��,��ʵ�ܶ�python�İ�װ����cygwin�»�����������,�����ϸ�ۿ�pylibemu�İ�װ��Ϣ�ᷢ��,pylibemuֻ��site-packagesĿ¼��д��pylibemu-0.1.4-py2.6.egg-info��pylibemu.dll�ļ�,Ҳ����˵ʵ���ļ�ֻ��pylibemu.dll,�������ͨ��google�ѵ���һƪ���һ�������,����˵����ֻ��dll��cygwin pythonģ�����No such file or directoryԭ�������dll�޷�����,ͨ����ʾ����ϸ����һ��ImportError,��ʾ�����ļ���Ŀ¼������,������ģ�鲻���ڡ�

����cygcheck.exe /usr/lib/python2.6/site-packages/pylibemu.dll

    ��ʾ���´���

F:\cygwin\lib\python2.6\site-packages\pylibemu.dll

cygcheck: track_down: could not find cygemu-2.dll

    ԭ�����޷��ҵ�cygemu-2.dll������pylibemu.dll�޷����ء�cygemu-2.dll��libemu��cygwin�±�����ļ������ļ���/opt/libemu/binĿ¼�£���������û�мӻ����������ҵ��������Ǽӻ������������ǽ�cygemu-2.dll����cygwin��binĿ¼��һ�ݡ�


*/
