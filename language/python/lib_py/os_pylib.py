# os.

'''
@top
    ��Ҫ������Ŀ¼����·����
@topdown                                                                             |
    Ĭ��ֵ��"True", ��ʾ���ȷ���Ŀ¼���µ��ļ�, Ȼ���ڱ���Ŀ¼������Ŀ¼. Topdown��ֵ|
	Ϊ"False"ʱ, ���ʾ�ȱ���Ŀ¼������Ŀ¼, ������Ŀ¼�µ��ļ�, ��󷵻ظ�Ŀ¼�µ���|
	��.                                                                              |
@onerror                                                                             |
    Ĭ��ֵ��"None", ��ʾ�����ļ�����ʱ�����Ĵ���. �����Ϊ��, ���ṩһ���Զ��庯���� |
	ʾ������Ϣ������������׳��쳣��ֹ����.
@followlinks
    Ĭ��ֵ��False, Ĭ��������ǲ��������ݷ�ʽ��, ���ϵͳ֧����Ҫ����ָ��.
@return
    os.walk����������Ԫ�飺
    dirpath��  Ŀ¼��·����
    dirnames�� dirpathĿ¼��������Ŀ¼�б�������"."��".."����
    filenames��dirpathĿ¼�����з�Ŀ¼�ļ��б�
'''
def walk(top, topdown=True, onerror=None, followlinks=False):
    pass

''' os.system(command)
Execute the command (a string) in a subshell. 
'''
def system(command):
    pass

	
#                      os.path

'''

'''
def join(path, *paths):
    pass
	
''' os.path.split(path)
Split the pathname @path into a pair, (head, tail) where tail is the last pathname c-
omponent and head is everything leading up to that. The tail part will never  contain 
a slash; if path ends in a slash, tail will be empty. If there is no slash in path, -
head will be empty. If path is empty, both head and tail are empty. Trailing  slashes 
are stripped from head unless it is the root (one or more slashes only). In all cases
, join(head, tail) returns a path to the same location as path (but the strings may -
differ). Also see the functions dirname() and basename().

d:\\python\\python.exe -->  ['d:\\python', 'python.exe']
'''
def split(path):
    pass
	
