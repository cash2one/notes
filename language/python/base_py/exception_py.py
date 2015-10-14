'''
http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386832284796780f5db7b5744bf9989f8d845ef77712000 
ѭ�򽥽�ѧPython 9.�쳣���� http://www.cnblogs.com/IPrograming/p/Python_error_handler.html


----> What Is an Exception?
To represent exceptional conditions, Python uses exception objects. When it encounte-
rs an error, it raises an exception. If such an exception object is not handled (or -
caught), the program terminates with a so-called traceback (an error message):
>>> 1/0
Traceback (most recent call last):
File "<stdin>", line 1, in ?
ZeroDivisionError: integer division or modulo by zero

each exception is an instance of some class (in this case ZeroDivisionError), and th-
ese instances may be raised and caught in various ways, allowing you to trap the err-
or and do something about it instead of just letting the entire program fail.


----> Catching Exceptions
--------------------------------------------
try:
    x = input('Enter the first number: ')
    y = input('Enter the second number: ')
    print x/y
except ZeroDivisionError:
    print "The second number can't be zero!"
except TypeError:
    print "That wasn't a number, was it?"

try:
    x = input('Enter the first number: ')
    y = input('Enter the second number: ')
    print x/y
except (ZeroDivisionError, TypeError, NameError):
    print 'Your numbers were bogus...'	
--------------------------------------------
Exceptions propagate out of functions to where they��re called, and if they��re not ca-
ught there either, the exceptions will "bubble up" to the top level of the program. -
This means that you can use try/except to catch exceptions that are raised in other -
people��s functions. 

--------------------------------------------
try:
    print 'try...'
    r = 10 / 0
    print 'result:', r
except ZeroDivisionError, e:
    print 'except:', e
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
��������ΪĳЩ������ܻ����ʱ���Ϳ�����try��������δ��룬���ִ�г�����������벻|
�����ִ�У�����ֱ����ת����������룬��except���飬ִ����except�������finally|
���飬��ִ��finally���飬���ˣ�ִ����ϡ�����Ĵ����ڼ���10 / 0ʱ�����һ��������|
����󡣿����ж��except������ͬ���͵Ĵ���                                       |
--------------------------------------------
try:
    print 'try...'
    r = 10 / int('a')
    print 'result:', r
except ValueError, e:
    print 'ValueError:', e
except ZeroDivisionError, e:
    print 'ZeroDivisionError:', e
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
int()�������ܻ��׳�ValueError������������һ��except����ValueError������һ��except����|
ZeroDivisionError�����⣬���û�д�������������except��������һ��else����û�д�|
����ʱ�����Զ�ִ��else��䣺                                                       |
--------------------------------------------  
try:
    print 'try...'
    r = 10 / int('a')
    print 'result:', r
except ValueError, e:
    print 'ValueError:', e
except ZeroDivisionError, e:
    print 'ZeroDivisionError:', e
else:
    print 'no error!'
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
Python�Ĵ�����ʵҲ��class�����еĴ������Ͷ��̳���BaseException��������ʹ��exceptʱ�� |
Ҫע����ǣ���������������͵Ĵ��󣬻���������Ҳ��һ���򾡡������磺                   |

try:
    foo()
except StandardError, e:
    print 'StandardError'
except ValueError, e:
    print 'ValueError'
                                                                                     |
�ڶ���except��ԶҲ���񲻵�ValueError����ΪValueError��StandardError�����࣬����У�Ҳ|
����һ��except�������ˡ�Python���еĴ����Ǵ�BaseException�������ģ������Ĵ������ͺ�|
�̳й�ϵ�����                                                                     |
https://docs.python.org/2/library/exceptions.html#exception-hierarchy                |
                                                                                     |
ʹ��try...except���������һ���޴�ĺô������ǿ��Կ�Խ�����ã����纯��main()���� |
foo()��foo()����bar()�����bar()�����ˣ���ʱ��ֻҪmain()�����ˣ��Ϳ��Դ���       |

def foo(s):
    return 10 / int(s)

def bar(s):
    return foo(s) * 2

def main():
    try:
        bar('0')
    except StandardError, e:
        print 'Error!'
    finally:
        print 'finally...'
                                                                                     |
Ҳ����˵������Ҫ��ÿ�����ܳ���ĵط�ȥ�������ֻҪ�ں��ʵĲ��ȥ�������Ϳ����ˡ� |
����һ�����ʹ�������дtry...except...finally���鷳���������û�б��������ͻ�һֱ |
�����ף����Python���������񣬴�ӡһ��������Ϣ��Ȼ������˳���������err.py��       |

err.py (an example)
 -------------------------------------------- 
 # err.py:                            0
 def foo(s):                         # 1
     return 10 / int(s)

 def bar(s):
     return foo(s) * 2
 
 def main():
     bar('0')

 main()                             # 11
 -------------------------------------------- 
 ִ�У�������£�
 $ python err.py
 Traceback (most recent call last):
   File "err.py", line 11, in <module>
     main()
   File "err.py", line 9, in main
     bar('0')
   File "err.py", line 6, in bar
     return foo(s) * 2
   File "err.py", line 3, in foo
     return 10 / int(s)
 ZeroDivisionError: integer division or modulo by zero
                                                                                      |
 ���������£����µ��ǲ�֪����������ˡ����������Ϣ�Ƕ�λ����Ĺؼ������Ǵ������¿� |
 �Կ�����������ĵ��ú�������
 
 ������Ϣ��1�У�
 Traceback (most recent call last):
 �����������Ǵ���ĸ�����Ϣ��
 
 ��2�У�
   File "err.py", line 11, in <module>
     main()
 ����main()�����ˣ��ڴ����ļ�err.py�ĵ�11�д��룬��ԭ���ǵ�9�У�
 
   File "err.py", line 9, in main
     bar('0')
 ����bar('0')�����ˣ��ڴ����ļ�err.py�ĵ�9�д��룬��ԭ���ǵ�6�У�
 
   File "err.py", line 6, in bar
     return foo(s) * 2
 ԭ����return foo(s) * 2����������ˣ����⻹��������ԭ�򣬼������¿���
 
   File "err.py", line 3, in foo
     return 10 / int(s)
 ԭ����return 10 / int(s)����������ˣ����Ǵ��������Դͷ����Ϊ�����ӡ�ˣ�
 
 ZeroDivisionError: integer division or modulo by zero                                |
 ���ݴ�������ZeroDivisionError�������жϣ�int(s)����û�г�������int(s)����0���ڼ� |
 ��10 / 0ʱ�������ˣ��ҵ�����Դͷ��

----> ��¼����
                                                                                      |
 ��������������Ȼ������Python����������ӡ�������ջ��������Ҳ�������ˡ���Ȼ������ |
 ������󣬾Ϳ��԰Ѵ����ջ��ӡ������Ȼ���������ԭ��ͬʱ���ó������ִ����ȥ��     |
 Python���õ�loggingģ����Էǳ����׵ؼ�¼������Ϣ��                                  |
 -------------------------------------------- 
 # err.py
 import logging 
 
 def foo(s):
     return 10 / int(s)
 
 def bar(s):
     return foo(s) * 2
 
 def main():
     try:
         bar('0')
     except StandardError, e:
         logging.exception(e)
 
 main()
 print 'END'
 -------------------------------------------- 
 
 ͬ���ǳ����������ӡ�������Ϣ������ִ�У��������˳���
 
 $ python err.py
 ERROR:root:integer division or modulo by zero
 Traceback (most recent call last):
   File "err.py", line 12, in main
     bar('0')
   File "err.py", line 8, in bar
     return foo(s) * 2
   File "err.py", line 5, in foo
     return 10 / int(s)
 ZeroDivisionError: integer division or modulo by zero
 END
 
 ͨ�����ã�logging�����԰Ѵ����¼����־�ļ�������º��Ų顣
                                                                                     |
																					 
----> �׳�����                                                                       |
 exception_rasie_eg.py

----> �������������һ�ִ�����ķ�ʽ��
 -------------------------------------------- 
 # err.py
 def foo(s):
     n = int(s)
     return 10 / n
 
 def bar(s):
     try:
         return foo(s) * 2
     except StandardError, e:
         print 'Error!'
         raise
 
 def main():
     bar('0')
 
 main()
 -------------------------------------------- 
                                                                                      |
 ��bar()�����У����������Ѿ������˴��󣬵��ǣ���ӡһ��Error!���ְѴ���ͨ��raise��� |
 �׳�ȥ�ˣ��ⲻ�в�ô�� ��ʵ���ִ�����ʽ����û���������൱�������������Ŀ��ֻ�Ǽ�|
 ¼һ�£����ں���׷�١����ǣ����ڵ�ǰ������֪��Ӧ����ô����ô������ԣ���ǡ���ķ�ʽ |
 �Ǽ��������ף��ö��������ȥ����raise�����������������ͻ�ѵ�ǰ����ԭ���׳�������|
 ����except��raiseһ��Error�������԰�һ�����͵Ĵ���ת������һ�����ͣ�                 |
 
 try:
     10 / 0
 except ZeroDivisionError:
     raise ValueError('input error!')

 ֻҪ�Ǻ����ת���߼��Ϳ��ԣ����ǣ�����Ӧ�ð�һ��IOErrorת���ɺ�����ɵ�ValueError��

'''

BaseException (6.1. Exception hierarchy. The class hierarchy for built-in exceptions is:
 +-- SystemExit
 +-- KeyboardInterrupt
 +-- GeneratorExit
 +-- Exception
      +-- StopIteration
      +-- StandardError
      |    +-- BufferError
      |    +-- ArithmeticError
      |    |    +-- FloatingPointError
      |    |    +-- OverflowError
      |    |    +-- ZeroDivisionError
      |    +-- AssertionError
      |    +-- AttributeError
      |    +-- EnvironmentError
      |    |    +-- IOError
      |    |    +-- OSError
      |    |         +-- WindowsError (Windows)
      |    |         +-- VMSError (VMS)
      |    +-- EOFError
      |    +-- ImportError
      |    +-- LookupError
      |    |    +-- IndexError
      |    |    +-- KeyError
      |    +-- MemoryError
      |    +-- NameError
      |    |    +-- UnboundLocalError
      |    +-- ReferenceError
      |    +-- RuntimeError
      |    |    +-- NotImplementedError
      |    +-- SyntaxError
      |    |    +-- IndentationError
      |    |         +-- TabError
      |    +-- SystemError
      |    +-- TypeError
      |    +-- ValueError
      |         +-- UnicodeError
      |              +-- UnicodeDecodeError
      |              +-- UnicodeEncodeError
      |              +-- UnicodeTranslateError
      +-- Warning
           +-- DeprecationWarning
           +-- PendingDeprecationWarning
           +-- RuntimeWarning
           +-- SyntaxWarning
           +-- UserWarning
           +-- FutureWarning
	   +-- ImportWarning
	   +-- UnicodeWarning
	   +-- BytesWarning




