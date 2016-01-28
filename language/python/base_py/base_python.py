introduction
setup

operators
types
file_io
function
module
class
namespace

object






--> primary prompt, secondary prompt
 In all interactive examples, you will see the Python primary ( >>> ) and secondary -
 ( ... ) prompts. The primary prompt is a way for the interpreter to let you know th-
 at it is expecting the next Python statement, while the secondary prompt indicates -
 that the interpreter is waiting for additional input to complete the current statem-
 ent.
 
 
Functions that do not explicitly
return a value by the programmer automatically return None

--> print
 





----> ģ��Ͱ�
 module_py.py

----> ����ռ�
 ��pythonģ���н���

----> �ļ�����
 �ļ������������ file_objects_py.py
 ����python�ļ����� http://www.cnblogs.com/rollenholt/archive/2012/04/23/2466179.html

 fileinput: Iterate over lines from multiple input streams

 file_io_py.py

----> �ļ�ϵͳ
 os
 os.path

----> ���߳�
 thread_pylib_eg.py

 
--> ����֪ʶ
 ��python�����������Ǿ�����Ҫ���ļ����в�����Windows�µ��ļ�Ŀ¼·��ʹ�÷�б�ܡ�\�����ָ������ǣ��ʹ��������һ����Python�������棬��б�ܡ�\����ת��������硰\n����ʾ�س�����\t����ʾ�Ʊ���ȵȡ����������������windowsϰ��ʹ�á�\����ʾ�ļ�·�����ͻ�������塣
      ���磺��c:\test.txt�����ʾc�̸�Ŀ¼�µ�һ���ļ������Ǳ�ʾһ���ַ����أ���Ϊ��\t��Ҳ���Խ���Ϊ�Ʊ������������������жϣ��⵱Ȼ��һ���ܼ򵥵����⡣���ǻ������޷�������ȷ���ж��ˣ�ֻ��û������Ĵ�������Ż���ȷִ�С�
      ����취�����������κ�һ����д��ʽ���ɣ�
ʹ��б�ܡ�/��: "c:/test.txt"�� ���÷�б�ܾ�û������������ 
����б�ܷ���ת��: "c:\\test.txt"�� ��Ϊ��б����ת�������������"\\"�ͱ�ʾһ����б�ܷ��� 
ʹ��Python��raw string: r"c:\test.txt" �� python�����ַ���ǰ�������ĸr����ʾ������һ��ԭʼ�ַ���raw string������raw string��Ҫ��Ϊ������ʽ������windows·����Ƶģ��������������������ã����ܻ�����⡣ 
 
 
 
 
PEP
 http://legacy.python.org/dev/peps/

universal newlines
    A manner of interpreting text streams in which all of the following are recogniz-
	ed as ending a line: the Unix end-of-line convention '\n', the Windows convention 
	'\r\n', and the old Macintosh convention '\r'. See PEP 278 and PEP 3116, as  well 
	as str.splitlines() for an additional use.

http://www.zhihu.com/question/20670869   ��������






? Hash mark ( # ) indicates Python comments
? NEWLINE ( \n ) is the standard line separator (one statement per line)
? Backslash ( \ ) continues a line
? Semicolon ( ; ) joins two statements on a line
? Colon ( : ) separates a header line from its suite
? Statements (code blocks) grouped as suites

Suites delimited via indentation
Code that is not indented, i.e., the highest level of code, is considered the  ��main�� 
portion of the script.

? Python files organized as modules

--> None
 None��һ������ĳ�����
 None��False��ͬ��
 None����0��
 None���ǿ��ַ�����
 None���κ��������������ͱȽ���Զ����False��
 None���Լ�����������NoneType��
 ����Խ�None���Ƹ��κα����������㲻�ܴ�������NoneType����
 >>> type(None)  
 <class 'NoneType'>
 >>> None == 0
 False  
 >>> None == ''  
 False  
 >>> None == None  
 True  
 >>> None == False  
 False  

variable assignment
  The equal sign ( = ) is the main Python assignment operator. (The others are augme-
  nted assignment operator)
  anInt = -12
  In Python, objects are referenced, so on assignment, a reference (not a value) to -
  an object is what is being assigned, whether the object was just created or was a -
  pre-existing object. 
  Also, if you are familiar with C, you know that assignments are treated as express-
  ions. This is not the case in Python, where assignments do not have inherent value-
  s. Statements such as the following are invalid in Python:
  >>> x = 1
  >>> y = (x = x + 1) # assignments not expressions!
  File "<stdin>", line 1
  y = (x = x + 1)
  ^
  SyntaxError: invalid syntax
  Chaining together assignments is okay, though (more on this later):
  >>> y = x = x + 1
  >>> x, y
  (2, 2)  
  
  Augmented Assignment
  Beginning in Python 2.0, the equal sign can be combined with an arithmetic operati-
  on and the resulting value reassigned to the existing variable. Known as  augmented 
  assignment, statements such as . . .
  x = x + 1
  . . . can now be written as . . .
  x += 1
  Python does not support pre-/post-increment nor pre-/post-decrement operators  such 
  as x++ or --x.
  
  Multiple Assignment
  >>> x = y = z = 1
  >>> x
  1
  >>> y
  1
  >>> z
  1
  In the above example, an integer object (with the value 1) is created, and x, y, a-
  nd z are all assigned the same reference to that object. This is the process of as-
  signing a single object to multiple variables. It is also possible in Python to as-
  sign multiple objects to multiple variables.
  
  ��Multuple�� Assignment
  Another way of assigning multiple variables is using what we shall call the ��multu-
  ple�� assignment. This is not an official Python term, but we use ��multuple�� here b-
  ecause when assigning variables this way, the objects on both sides of the equal s-
  ign are tuples
  >>> x, y, z = 1, 2, 'a string'
  >>> x
  1
  >>> y
  2
  >>> z
  'a string'
  Parentheses are normally used to denote tuples, and although they are optional,  we 
  recommend them anywhere they make the code easier to read:
  >>> (x, y, z) = (1, 2, 'a string')
  
  One interesting side effect of Python��s ��multuple�� assignment is that we no  longer 
  need a temporary variable to swap the values of two variables.
  # swapping variables in Python
  >>> x, y = 1, 2
  >>> x
  1
  >>> y
  2
  >>> x, y = y, x
  >>> x
  2
  >>> y
  1
  Obviously, Python performs evaluation before making assignments.

Identifiers  
  Identifiers are the set of valid strings that are allowed as names in a computer l-
  anguage. The rules for Python identifier strings are like most other high-level pr-
  ogramming languages that come from the C world:
  ? First character must be a letter or underscore ( _ )
  ? Any additional characters can be alphanumeric or underscore
  ? Case-sensitive
  
  Keywords
  Built-ins
  
  Special Underscore Identifiers
  ? _xxx Do not import with 'from module import *'
  ? __xxx__ System-defined name
  ? __xxx Request private name mangling in classes
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  




















