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
def file(name[, mode[, buffering]]):
    pass