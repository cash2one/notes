
def file(name[, mode[, buffering]]):
    '''
    ��δ��ļ�
    handle=open(file_name,access_mode="r")
    file_name������������ϣ���򿪵��ļ����ַ������ƣ�access_mode �е�'r'��ʾ��ȡ����w����ʾд�룬'a'��ʾ��ӣ����������õ��ı�ʵ���С�+����ʾ��д����b����ʾ2���Ʒ��ʣ����δ�ṩaccess_mode,Ĭ��Ϊ��r��.

    ���open()�ɹ���һ���ļ��������ᱻ���ء�

    filename=raw_input('enter file')
    fobj=open(filename,'r')
    for eachline in fobj:
        print eachline,
    fobj.close()
    #���ǵ� print ������ġ�������ʲô��˼�ɣ���ʾ��ÿ�δ�ӡ�������У����Ǽ���ո�
    '''
    pass
    
    
def open(name[, mode[, buffering]]):
    '''
    @mode:
      'r' Read mode
      'w' Write mode
      'a' Append mode
      'b' Binary mode (added to other mode)
      '+' Read/write mode (added to other mode)
      Explicitly specifying read mode has the same effect as not supplying a mode st-
      ring at all. The write mode enables you to write to the file. The '+' can be a-
      dded to any of the other modes to indicate that both reading and writing is al-
      lowed. The 'b' mode changes the way the file is handled. Generally, Python ass-
	  umes that you are dealing with text files (containing characters). 
    @buffering
      If the parameter is 0 (or False), input/output (I/O) is unbuffered (all reads -
	  and writes go directly from/to the disk); if it is 1 (or True), I/O is buffere-
	  d (meaning that Python may use memory instead of disk space to make things go -
	  faster, and only update when you use flush or close). Larger numbers indicate -
	  the buffer size (in bytes), while �C1 (or any negative number) sets the buffer -
	  size to the default.
	 
    You can open files with the @open function. The @open function takes a file  name 
    as its only mandatory argument, and returns a file object. If the file cannot  be 
    opened(file doesn��t exist, for example), IOError is raised. 
    '''
