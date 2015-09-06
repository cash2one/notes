#_*_coding:UTF-8_*_
#python csv

import os
import csv

'''
    ��python�У�CSV(Comma Separated Values)���������������Ϊ�����ŷָ�ֵ
    �ٸ����ӣ��磺test_csv = 'one, two, three, 4, 5'
    ����test_csv���������˵��������ʹ����������ֵ�����ŷָ���ֵ����������ʽ
    �ڵ���͵����зǳ���������python(version:3.3.2)��API����������һ����

        The so-called CSV(Comma Separated Values) format is the most
        common import and export for spreadsheets and databases.

    csvģ�鶨�������º�����

        csv.reader(csvfile, dialect = 'excel', **fmtparams)
            Retuen a reader object which will iterate over lines
            in the given csvfile.
    A short usage example:
        import csv
        with open('eggs.csv', newline = '') as cf:
            spamreader = csv.reader(cf, delimiter = ' ',  quotechar = '|')
            for row in spamreader:
                print(','.join(row))

        csv.write(csvfile, dialect = 'excel', **fmtparams)
            Return a writer object reaponsible for converting the
            user's data into delimited strings on the given file-like
            object.

    A short usage example:
        import csv
        with open('eggs.csv', 'w', newline = '') as cf:
            spamwrite = csv.writer(cf, delimiter = ' ', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
            spamwriter.writerow(['Spam'] * 5 + ['Baked Beans'])
            spamwriter.writerow(['Spam', 'Lovely Spam', 'Wonderful Spam'])
'''

#global var
SHOW_LOG = True
#csv file apth
CSV_FILE_PATH = ''

def write_data_2_csv_file(path, data):
    '''������д�뵽csv�ļ�
    �����Ҫд������ݽ������ƣ�
    ���ݸ�ʽΪһ���б�['one', 'two', 'three', 'four']
    '''
    if SHOW_LOG:
        print('���ļ�:[{}]'.format(path))
    with open(path, 'w', newline = '') as cf:
        writer = csv.writer(cf, delimiter = ',', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
        if SHOW_LOG:
            print('д������:{}'.format(data))
        writer.writerow(data)
    
def write_datas_2_csv_file(path, datas):
    '''������д�뵽csv�ļ�
    �����Ҫд������ݽ������ƣ�
    ���ݸ�ʽΪһ���б�,�б������ÿһ��Ԫ�ض���һ���б�
    [
    ['one', 'two', 'three', 'four'],
    ['1', '2', '3'],
    ['a', 'b', 'c', 'd']
    ]
    '''
    if SHOW_LOG:
        print('���ļ�:[{}]'.format(path))
    with open(path, 'w', newline = '') as cf:
        writer = csv.writer(cf, delimiter = ',', quotechar = '|', quoting = csv.QUOTE_MINIMAL)
        for row in datas:
            if SHOW_LOG:
                print('д������:{}'.format(row))
            writer.writerow(row)

def read_csv_file(path):
    '''��ȡָ����csv�ļ������Ұ�csv�ļ����������ַ�������ʽ����'''
    if os.path.exists(path):
        if SHOW_LOG:
            print('���ļ�:[{}]'.format(path))
        content = ''
        with open(path, newline = '') as cf:
            reader = csv.reader(cf, delimiter = ' ', quotechar = '|')
            try:
                for row in reader:
                    if SHOW_LOG:
                        print('��ȡ��:{}'.format(row))
                    c = ','.join(row) +'\n'
                    content += c
                return content[0:-1]
            except csv.Errow as e:
                sys.exit('file {}, line {} : {}'.format(path, reader.line_num, e))
    else:
        print('�������ļ�:[{}]'.format(path))
                
def mkdirs(path):
    '''�����༶Ŀ¼'''
    if os.path.exists(path):
        if SHOW_LOG:
            print('The path [{}] existing!'.format(path))
    else:
        if SHOW_LOG:
            print('The path [{}] dosen\'t exist!'.format(path))
        os.makedirs(path)
        if SHOW_LOG:
            print('Created the path [{}]'.format(path))

def get_path(absPath):
    '''��ȡ��һ������·����Ŀ¼��
    �����·����'C:\\test\\test.csv'
    �򷵻ص���'C:\\test'
    '''
    if os.path.exists(absPath):
        if SHOW_LOG:
            print('the path [{}] existing!'.format(absPath))
        return os.path.split(absPath)[0]
    else:
        return os.path.split(absPath)[0]

def init():
    global SHOW_LOG
    SHOW_LOG = True
    global CSV_FILE_PATH
    CSV_FILE_PATH = 'C:\\test\\test.csv'
    csv_dir = get_path(CSV_FILE_PATH)
    mkdirs(csv_dir)
        
def main():
    init()
    data = ['one', 'two', 'three', 'four']
    datas = [
    ['one', 'two', 'three', 'four'],
    ['1', '2', '3'],
    ['a', 'b', 'c', 'd'],
    ['�й�', '����', '�ձ�', '����', '�¼���']
    ]
    write_data_2_csv_file(CSV_FILE_PATH, data)
    content = read_csv_file(CSV_FILE_PATH)
    print(content)
    print('#' * 50)
    write_datas_2_csv_file(CSV_FILE_PATH,  datas)
    content = read_csv_file(CSV_FILE_PATH)
    print(content)

    
if __name__ == '__main__':
    main()