
--> What Are Functions
 declaration/definition     def foo(): print 'bar'
 function object/reference  foo
 function call/invocation   foo()
 
 In short, when no items are explicitly returned or if None is returned, then  Python 
 returns None. If the function returns exactly one object, then that is the object t-
 hat Python returns and the type of that object stays the same. If the function retu-
 rns multiple objects, Python gathers them all together and returns them in a tuple. 

--> Calling Functions
 Functions are called using the same pair of parentheses,  any input parameters or a-
 rguments must be placed between these calling parentheses. Parentheses are also used
 as part of function declarations to define those arguments. the function operator is 
 also used in Python for class instantiation.
 
 Keyword Arguments
 Default Arguments
 Grouped Arguments

--> Creating Functions

 Functions are created using the def statement, with a syntax like the following:
 
 def function_name(arguments):
    "function_documentation_string"
    function_body_suite

 Declaration versus Definition
  Python does not make a distinction between the two, as a function clause is made u-
  p of a declarative header line immediately followed by its defining suite.
 
 Forward References
  Like some other high-level languages, Python does not permit you to reference or c-
  all a function before it has been declared. 
  
  def foo():
      print 'in foo()'
  bar()
      def bar():
      print 'in bar()'
  >>> foo()
  in foo()
  in bar()
  
  This piece of code is fine because even though a call to bar() (from foo()) appears 
  before bar()’s definition, foo() itself is not called before bar() is declared.  In 
  other words, we declared foo(), then bar(), and then called foo(),but by that time, 
  bar() existed already, so the call succeeds.
  
 Inner or Nested Functions
  It is perfectly legitimate to create function (object)s inside other functions. Th-
  at is the definition of an inner or nested function.	

  The (obvious) way to create an inner function is to define a function from within -
  an outer function’s definition (using the def keyword), as in:  
  -------------------inner.py
  def foo():
      def bar():
          print 'bar() called'
      print 'foo() called'
      bar()
  foo()
  bar()
  ------------------
  > python inner.py
  > foo() called
  > bar() called
  > Traceback (most recent call last):
  >   File "inner.py", line 11, in ?
  >     bar()
  > NameError: name 'bar' is not defined  
  One interesting aspect of inner functions is that they are wholly contained  inside 
  the outer function’s scope If there are no outside references to bar(), it cannot -
  be called from anywhere else except inside the outer function, hence the reason for 
  the exception you see at the end of execution in the above code snippet.
  
  Inner functions turn into something special called closures if the definition of an 
  inner function contains a reference to an object defined in an outer function. 
	  
 Function (and Method) Decorators	  
  Decorators are just “overlays” on top of function calls. These overlays are just a-
  dditional calls that are applied when a function or method is declared. The  syntax 
  for decorators uses a leading “at-sign” ( @ ) followed by the decorator function n-
  ame and optional arguments. It looks something like this:

  @decorator(dec_opt_args)
  def func2Bdecorated(func_opt_args):
       : 	   
  
  class MyClass(object):
      def staticFoo():
          :
      staticFoo = staticmethod(staticFoo)
          :
		  
  With decorators, you can now replace that piece of code with the following:

  class MyClass(object):
      @staticmethod
      def staticFoo():
          :
  Furthermore, decorators can be “stacked” like function calls, so here is a more ge-
  neral example with multiple decorators:

  @deco2
  @deco1
  def func(arg1, arg2, ...): pass

  This is equivalent to creating a composite function:
  def func(arg1, arg2, ...): pass
  func = deco2(deco1(func))
  
  Decorators With and Without Arguments
  
  @decomaker(deco_args)
  def foo(): pass

--> Passing Functions
 Python Functions can be referenced (accessed or aliased to other variables),  passed 
 as arguments to functions, be elements of container objects such as lists and dicti-
 onaries, etc. The one unique characteristic of functions which may set them apart f-
 rom other objects is that they are callable, i.e., they can be invoked via the func-
 tion operator.	  
 
 functions can be aliases to other variables. Because all objects are passed by refe-
 rence, functions are no different. When assigning to another variable, you are assi-
 gning the reference to the same object; and if that object is a function, then all -
 aliases to that same object are callable:
 
 >>> def foo():
 ...     print 'in foo()'
 ...
 >>> bar = foo
 >>> bar()
 in foo()
 
 we can even pass functions in as arguments to other functions for invocation:
 >>> def bar(argfunc):
 ...     argfunc()
 ...
 >>> bar(foo)
 in foo()

--> Argument
 -->--> Positional Arguments, Default arguments
  Positional arguments must be passed in the exact order in which they are defined f-
  or the functions that are called. The syntax for declaring variables with default -
  values in Python is such that all positional arguments must come before any default 
  arguments:
  
  def func(posargs, defarg1=dval1, defarg2=dval2,...):
      "function_documentation_string"
      function_body_suite

  Each default argument is followed by an assignment statement of its default  value. 
  If no value is given during a function call, then this assignment is realized.
  
 -->--> Collecting Parameters

  def print_params(*params):
     print params
	 
  The star in front of the parameter puts all the values into the same tuple. It gat-
  hers them up, so to speak.
  
  >>> print_params(1, 2, 3)
  (1, 2, 3)

  def print_params_3(**params):
     print params
 
  >>> print_params_3(x=1, y=2, z=3)
  {'z': 3, 'x': 1, 'y': 2}
  
  Yep, we get a dictionary rather than a tuple. 

  -->--> Reversing the Process
   Now you’ve learned about gathering up parameters in tuples and dictionaries, but it 
   is in fact possible to do the "opposite" as well, with the same two operators, *and 
   **. This is simply done by using the * or ** operator at the "other end" — that is,
   when calling the function rather than when defining it. 
  
   def add(x, y): return x + y
   params = (1, 2) 
   >>> add(*params)
   3
  
   You can use the same technique with dictionaries, using the ** operator.
  
   def print_params_3(**params): print params
   >>> params = {'name': 'Sir Robin', 'greeting': 'Well met'}
   >>> hello_3(**params)
   Well met, Sir Robin!	  

--> Closures
 If references are made from inside an inner function to an object defined in any ou-
 ter scope (but not in the global scope), the inner function then is known as a     -
 @closure. The variables defined in the outer function but used or referred to by the 
 inner function are called free variables. A closure combines an inner function’s own 
 code and scope along with the scope of an outer function. closure variables live  in 
 a function’s namespace and scope.
 
 Simple Closure Example
 
 By using the variable @count inside it, we have created a closure because it now ca-
 rries with it the scope of counter().
 
 def counter(start_at=0):
     count = [start_at]
     def incr():
         count[0] += 1
         return count[0]
     return incr
	 
 >>> count = counter(5)
 >>> print count()
 6
 >>> print count()
 7
 >>> count2 = counter(100)
 >>> print count2()
 101
 >>> print count()
 8	 
	 


'''
----> positional parameters, Keyword Parameters
 |def hello_1(greeting, name):
 |  print '%s, %s!' % (greeting, name)

 @greeting @name are called positional parameters because their positions are import-
 ant. 
 
 hello_1('a','b') 
 hello_1('b','a')   # print not same
 
 hello_1(name='world', greeting='Hello')
 hello_1(greeting='Hello', name='world') # print same

 The parameters that are supplied with a name like this are called keyword parameters. 

 |def hello_3(greeting='Hello', name='world'):
 |   print '%s, %s!' % (greeting, name)

 When a parameter has a default value like this, you don’t need to supply it when you 
 call the function! You can supply none, some, or all, as the situation might dictat-
 e:
 >>> hello_3()
 Hello, world!
 >>> hello_3('Greetings')
 Greetings, world!
 >>> hello_3('Greetings', 'universe')
 Greetings, universe!
 >>> hello_3(name='Gumby')
 Hello, Gumby!

 |def hello_4(name, greeting='Hello', punctuation='!'):
 |    print '%s, %s%s' % (greeting, name, punctuation)
 This function can be called in many ways. Here are some of them:
 >>> hello_4('Mars')
 Hello, Mars!
 >>> hello_4('Mars', 'Howdy')
 Howdy, Mars!
 >>> hello_4('Mars', 'Howdy', '...')
 Howdy, Mars...
 >>> hello_4('Mars', punctuation='.')
 Hello, Mars.
 >>> hello_4('Mars', greeting='Top of the morning to ya')
 Top of the morning to ya, Mars!
 >>> hello_4()
 Traceback (most recent call last):
 File "<pyshell#64>", line 1, in ?
 hello_4()
 TypeError: hello_4() takes at least 1 argument (0 given)
 
----> Collecting Parameters
 |def print_params(*params):
 |  print params
 The star in front of the parameter puts all the values into the same tuple. It gath-
 ers them up, so to speak. 
 >>> print_params(1, 2, 3)
 (1, 2, 3)

 |def print_params_3(**params):
 |   print params
 >>> print_params_3(x=1, y=2, z=3)
 {'z': 3, 'x': 1, 'y': 2}
 Yep, we get a dictionary rather than a tuple. 

 Reversing the Process
 Now you’ve learned about gathering up parameters in tuples and dictionaries, but  it 
 is in fact possible to do the "opposite" as well, with the same two operators, * and 
 **. This is simply done by using the * or ** operator at the "other end" — that is ,
 when calling the function rather than when defining it. 
 |def add(x, y): return x + y
 params = (1, 2) 
 >>> add(*params)
 3
 You can use the same technique with dictionaries, using the ** operator.
 def print_params_3(**params): print params
 >>> params = {'name': 'Sir Robin', 'greeting': 'Well met'}
 >>> hello_3(**params)
 Well met, Sir Robin!

----> Can I Change a Parameter
 Parameters are kept in what is called a local scope
 >>> def try_to_change(n):
 n = 'Mr. Gumby'
 >>> name = 'Mrs. Entity'
 >>> try_to_change(name)
 >>> name
 'Mrs. Entity'
 It’s just as if you did something like this:
 >>> name = 'Mrs. Entity'
 >>> n = name # This is almost what happens when passing a parameter
 >>> n = 'Mr. Gumby' # This is done inside the function
 >>> name
 'Mrs. Entity'
 But consider what happens if you use a mutable data structure such as a list:
 >>> def change(n):
 n[0] = 'Mr. Gumby'
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> change(names)
 >>> names
 ['Mr. Gumby', 'Mrs. Thing']
 Let’s do it again without the function call:
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> n = names # Again pretending to pass names as a parameter
 >>> n[0] = 'Mr. Gumby' # Change the list
 >>> names
 ['Mr. Gumby', 'Mrs. Thing']
 You’ve seen this sort of thing before. When two variables refer to the same list,  -
 they . . . refer to the same list. It’s really as simple as that. If you want to av-
 oid this, you must make a copy of the list. When you do slicing on a sequence, the -
 returned slice is always a copy. Thus, if you make a slice of the entire list, you -
 get a copy:
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> n = names[:]
 Now n and names contain two separate (nonidentical) lists that are equal:
 >>> n is names
 False
 >>> n == names
 True
 If you change n now (as you did inside the function change), it won’t affect names:
 >>> n[0] = 'Mr. Gumby'
 >>> n
 ['Mr. Gumby', 'Mrs. Thing']
 >>> names
 ['Mrs. Entity', 'Mrs. Thing']
 Let’s try this trick with change:
 >>> change(names[:])
 >>> names
 ['Mrs. Entity', 'Mrs. Thing']
 Now the parameter n contains a copy, and your original list is safe.

----> Scoping
 What are variables, really? You can think of them as names referring to values.  So, 
 after the assignment x = 1, the name x refers to the value 1. It’s almost like usin-
 g dictionaries, where keys refer to values, except that you’re using an  "invisible" 
 dictionary. Actually, this isn’t far from the truth. There is a built-in function c-
 alled @vars, which returns this dictionary:
 >>> x = 1
 >>> scope = vars()
 >>> scope['x']
 1
 >>> scope['x'] += 1
 >>> x
 2
 This sort of "invisible dictionary" is called a namespace or scope. So, how many na-
 mespaces are there? In addition to the global scope, each function call creates a n-
 ew one:
 >>> def foo(): x = 42
 ...
 >>> x = 1
 >>> foo()
 >>> x
 1

 The parameters work just like local variables, so there is no problem in having a p-
 arameter with the same name as a global variable:
 >>> def output(x): print x
 ...
 >>> x = 1
 >>> y = 2
 >>> output(y)
 2

 But what if you want to access the global variables inside a function? 
 >>> def combine(parameter): print parameter + external
 ...
 >>> external = 'berry'
 >>> combine('Shrub')
 Shrubberry

 If a local variable or parameter exists with the same name as the global variable y-
 ou want to access, you can’t do it directly. The global variable is shadowed by  the 
 local one. If needed, you can still gain access to the global variable by using  the 
 function @globals.

 >>> def combine(parameter):
 print parameter + globals()['parameter']
 ...
 >>> parameter = 'berry'
 >>> combine('Shrub')
 Shrubberry

 And how do you think you can tell it to make a variable global?
 >>> x = 1
 >>> def change_global():
 global x
 x = x + 1
 >>> change_global()
 >>> x
 2

----> NESTED SCOPES closure
 Python functions may be nested, you can put one inside another. Here is an example:
 |def foo():
 |   def bar():
 |       print "Hello, world!"
 |   bar()
 Nesting is normally not all that useful, but there is one particular application th-
 at stands out: using one function to "create" another. This means that you can (amo-
 ng other things) write functions like the following:
 |def multiplier(factor):
 |  def multiplyByFactor(number):
 |      return number*factor
 |  return multiplyByFactor
 One function is inside another, and the outer function returns the inner one; that -
 is, the function itself is returned, it is not called. What’s important is that  the 
 returned function still has access to the scope where it was defined; in other words
 , it carries its environment (and the associated local variables) with it! Each time 
 the outer function is called, the inner one gets redefined, and each time, the vari-
 able factor may have a new value. Because of Python’s nested scopes, this variable -
 from the outer local scope (of multiplier) is accessible in the inner function later 
 on, as follows:
 >>> double = multiplier(2)
 >>> double(5)
 10
 >>> triple = multiplier(3)
 >>> triple(3)
 9
 >>> multiplier(5)(4)
 20
 A function such as multiplyByFactor that stores its enclosing scopes is called a   -
 @closure.










#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->          1 定义函数           <--<--<--<--<--<--<-#
#******************************************************************************# 
#在Python中，定义一个函数要使用def语句，依次写出函数名、括号、括号中的参数和冒号
#:，然后，在缩进块中编写函数体，函数的返回值用return语句返回。例如:
def my_abs(x):
    if x >= 0:
        return x
    else:
        return -x
#遇到return时，函数就执行完毕，并将结果返回。
#如果没有return语句，函数执行完毕后也会返回结果，只是结果为None。
#return None可以简写为return。

########空函数
#如果想定义一个什么事也不做的空函数，可以用pass语句：
def nop():
    pass
#pass语句什么都不做，可以用来作为占位符，比如现在还没想
#好怎么写函数的代码，就可以先放一个pass，让代码能运行起来。

#pass还可以用在其他语句里，比如：
if age >= 18:
    pass
#缺少了pass，代码运行就会有语法错误。

########参数检查
#调用函数时，如果参数个数不对，Python解释器会自动检查出来，并抛出TypeError：
>>> my_abs(1, 2)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: my_abs() takes exactly 1 argument (2 given)
#但是如果参数类型不对，Python解释器就无法帮我们检查。
#数据类型检查可以用内置函数isinstance实现：
def my_abs(x):
    if not isinstance(x, (int, float)):
        raise TypeError('bad operand type')
    if x >= 0:
        return x
    else:
        return -x
#添加了参数检查后，如果传入错误的参数类型，函数就可以抛出一个错误：
>>> my_abs('A')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 3, in my_abs
TypeError: bad operand type

########返回多个值
#函数可以返回多个值吗？答案是肯定的。
#比如在游戏中经常需要从一个点移动到另一个点，给出坐标、位移和角度，就可以计算
#出新的新的坐标：

import math

def move(x, y, step, angle=0):
    nx = x + step * math.cos(angle)
    ny = y - step * math.sin(angle)
    return nx, ny
#这样我们就可以同时获得返回值：

>>> x, y = move(100, 100, 60, math.pi / 6)
>>> print x, y
151.961524227 70.0

#但其实这只是一种假象，Python函数返回的仍然是单一值：

>>> r = move(100, 100, 60, math.pi / 6)
>>> print r
(151.96152422706632, 70.0)
#原来返回值是一个tuple！但是，在语法上，返回一个tuple可以省略括号，而多个变量
#可以同时接收一个tuple，按位置赋给对应的值，所以，Python的函数返回多值其实就是
#返回一个tuple，但写起来更方便。
#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->          2 函数的参数         <--<--<--<--<--<--<-#
#******************************************************************************#
#定义函数的时候，我们把参数的名字和位置确定下来，函数的接口定义就完成了。对于函
#数的调用者来说，只需要知道如何传递正确的参数，以及函数将返回什么样的值就够了，
#函数内部的复杂逻辑被封装起来，调用者无需了解。
#Python的函数定义非常简单，但灵活度却非常大。除了正常定义的必选参数外，还可以使
#用默认参数、可变参数和关键字参数，使得函数定义出来的接口，不但能处理复杂的参数，
#还可以简化调用者的代码。

########默认参数
#当我们调用power(5)时，相当于调用power(5, 2)：
def power(x, n=2):
    s = 1
    while n > 0:
        n = n - 1
        s = s * x
    return s
#默认参数可以简化函数的调用。设置默认参数时，有几点要注意：
#一是必选参数在前，默认参数在后，否则Python的解释器会报错（思考一下为什么默认参
#数不能放在必选参数前面）；
#二是如何设置默认参数。
#当函数有多个参数时，把变化大的参数放前面，变化小的参数放后面。变化小的参数就可
#以作为默认参数。
def enroll(name, gender, age=6, city='Beijing'):
    print 'name:', name
    print 'gender:', gender
    print 'age:', age
    print 'city:', city
#有多个默认参数时，调用的时候，既可以按顺序提供默认参数，比如调用
enroll('Bob', 'M', 7)
#意思是，除了name，gender这两个参数外，最后1个参数应用在参数age上，city参数由于
#没有提供，仍然使用默认值。
#也可以不按顺序提供部分默认参数。当不按顺序提供部分默认参数时，需要把参数名写上。
#比如调用
enroll('Adam', 'M', city='Tianjin')
#意思是，city参数用传进去的值，其他默认参数继续使用默认值。

####默认参数有个最大的坑，演示如下：
#先定义一个函数，传入一个list，添加一个END再返回：
def add_end(L=[]):
    L.append('END')
    return L
#当你正常调用时，结果似乎不错：
>>> add_end([1, 2, 3])
[1, 2, 3, 'END']
>>> add_end(['x', 'y', 'z'])
['x', 'y', 'z', 'END']
#当你使用默认参数调用时，一开始结果也是对的：
>>> add_end()
['END']
#但是，再次调用add_end()时，结果就不对了：
>>> add_end()
['END', 'END']
>>> add_end()
['END', 'END', 'END']
#很多初学者很疑惑，默认参数是[]，但是函数似乎每次都“记住了”上次添加了'END'后的
#list。

#原因解释如下：
#Python函数在定义的时候，默认参数L的值就被计算出来了，即[]，因为默认参数L也是一
#个变量，它指向对象[]，每次调用该函数，如果改变了L的内容，则下次调用时，默认参数
#的内容就变了，不再是函数定义时的[]了。

#所以，定义默认参数要牢记一点：默认参数必须指向不变对象！
#要修改上面的例子，我们可以用None这个不变对象来实现：
def add_end(L=None):
    if L is None:
        L = []
    L.append('END')
    return L
#现在，无论调用多少次，都不会有问题：
>>> add_end()
['END']
>>> add_end()
['END']
#为什么要设计str、None这样的不变对象呢？因为不变对象一旦创建，对象内部的数据就不
#能修改，这样就减少了由于修改数据导致的错误。此外，由于对象不变，多任务环境下同
#时读取对象不需要加锁，同时读一点问题都没有。我们在编写程序时，如果可以设计一个
#不变对象，那就尽量设计成不变对象。

####可变参数
#给定一组数字a，b，c……，请计算a^2 + b^2 + c^2 + ……。
def calc(*numbers):
    sum = 0
    for n in numbers:
        sum = sum + n * n
    return sum
#参数前面加了一个*号。在函数内部，参数numbers接收到的是一个tuple
#调用该函数时，可以传入任意个参数，包括0个参数：
>>> calc(1, 2)
5
>>> calc()
0	
>>> nums = [1, 2, 3]
>>> calc(*nums)
14

######## 关键字参数
#可变参数允许你传入0个或任意个参数，这些可变参数在函数调用时自动组装为一个tuple。
#而关键字参数允许你传入0个或任意个含参数名的参数，这些关键字参数在函数内部自动组
#装为一个dict。请看示例：
def person(name, age, **kw):
    print 'name:', name, 'age:', age, 'other:', kw
#函数person除了必选参数name和age外，还接受关键字参数kw。在调用该函数时，可以只传
#入必选参数：
>>> person('Michael', 30)
name: Michael age: 30 other: {}
#也可以传入任意个数的关键字参数：
>>> person('Bob', 35, city='Beijing')
name: Bob age: 35 other: {'city': 'Beijing'}
>>> person('Adam', 45, gender='M', job='Engineer')
name: Adam age: 45 other: {'gender': 'M', 'job': 'Engineer'}
#关键字参数有什么用？它可以扩展函数的功能。比如，在person函数里，我们保证能接收
#到name和age这两个参数，但是，如果调用者愿意提供更多的参数，我们也能收到。试想
#你正在做一个用户注册的功能，除了用户名和年龄是必填项外，其他都是可选项，利用关
#键字参数来定义这个函数就能满足注册的需求。

#和可变参数类似，也可以先组装出一个dict，然后，把该dict转换为关键字参数传进去：
>>> kw = {'city': 'Beijing', 'job': 'Engineer'}
>>> person('Jack', 24, city=kw['city'], job=kw['job'])
name: Jack age: 24 other: {'city': 'Beijing', 'job': 'Engineer'}
#当然，上面复杂的调用可以用简化的写法：
>>> kw = {'city': 'Beijing', 'job': 'Engineer'}
>>> person('Jack', 24, **kw)
name: Jack age: 24 other: {'city': 'Beijing', 'job': 'Engineer'}

######## 参数组合

#在Python中定义函数，可以用必选参数、默认参数、可变参数和关键字参数，这4种参数都
#可以一起使用，或者只用其中某些，但是请注意，参数定义的顺序必须是：必选参数、默
#认参数、可变参数和关键字参数。

#比如定义一个函数，包含上述4种参数：

def func(a, b, c=0, *args, **kw):
    print 'a =', a, 'b =', b, 'c =', c, 'args =', args, 'kw =', kw
#在函数调用的时候，Python解释器自动按照参数位置和参数名把对应的参数传进去。
>>> func(1, 2)
a = 1 b = 2 c = 0 args = () kw = {}
>>> func(1, 2, c=3)
a = 1 b = 2 c = 3 args = () kw = {}
>>> func(1, 2, 3, 'a', 'b')
a = 1 b = 2 c = 3 args = ('a', 'b') kw = {}
>>> func(1, 2, 3, 'a', 'b', x=99)
a = 1 b = 2 c = 3 args = ('a', 'b') kw = {'x': 99}
#最神奇的是通过一个tuple和dict，你也可以调用该函数：
>>> args = (1, 2, 3, 4)
>>> kw = {'x': 99}
>>> func(*args, **kw)
a = 1 b = 2 c = 3 args = (4,) kw = {'x': 99}
#所以，对于任意函数，都可以通过类似func(*args, **kw)的形式调用它，无论它的参数是
#如何定义的。

#参数使用小结
#Python的函数具有非常灵活的参数形态，既可以实现简单的调用，又可以传入非常复杂的
#参数。
#默认参数一定要用不可变对象，如果是可变对象，运行会有逻辑错误！
#要注意定义可变参数和关键字参数的语法：
#*args是可变参数，args接收的是一个tuple；
#**kw是关键字参数，kw接收的是一个dict。
#以及调用函数时如何传入可变参数和关键字参数的语法：
#可变参数既可以直接传入：func(1, 2, 3)，又可以先组装list或tuple，再通过*args传入
#：func(*(1, 2, 3))；
#关键字参数既可以直接传入：func(a=1, b=2)，又可以先组装dict，再通过**kw传入：
#func(**{'a': 1, 'b': 2})。
#使用*args和**kw是Python的习惯写法，当然也可以用其他参数名，但最好使用习惯用法。

#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->          3 递归函数           <--<--<--<--<--<--<-#
#******************************************************************************#
#在函数内部，可以调用其他函数。如果一个函数在内部调用自身本身，这个函数就是递归
#函数。

#举个例子，我们来计算阶乘n! = 1 x 2 x 3 x ... x n，用函数fact(n)表示，可以看出：
#fact(n) = n! = 1 x 2 x 3 x ... x (n-1) x n = (n-1)! x n = fact(n-1) x n
#所以，fact(n)可以表示为n x fact(n-1)，只有n=1时需要特殊处理。
#于是，fact(n)用递归的方式写出来就是：

def fact(n):
    if n==1:
        return 1
    return n * fact(n - 1)
#上面就是一个递归函数。可以试试：

>>> fact(1)
1
>>> fact(5)
120
>>> fact(100)

#===> fact(5)
#===> 5 * fact(4)
#===> 5 * (4 * fact(3))
#===> 5 * (4 * (3 * fact(2)))
#===> 5 * (4 * (3 * (2 * fact(1))))
#===> 5 * (4 * (3 * (2 * 1)))
#===> 5 * (4 * (3 * 2))
#===> 5 * (4 * 6)
#===> 5 * 24
#===> 120
#递归函数的优点是定义简单，逻辑清晰。理论上，所有的递归函数都可以写成循环的方式，
#但循环的逻辑不如递归清晰。

#使用递归函数需要注意防止栈溢出。在计算机中，函数调用是通过栈（stack）这种数据结
#构实现的，每当进入一个函数调用，栈就会加一层栈帧，每当函数返回，栈就会减一层栈
#帧。由于栈的大小不是无限的，所以，递归调用的次数过多，会导致栈溢出。可以试试
#fact(1000)：
>>> fact(1000)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 4, in fact
  ...
  File "<stdin>", line 4, in fact
RuntimeError: maximum recursion depth exceeded
#解决递归调用栈溢出的方法是通过尾递归优化，事实上尾递归和循环的效果是一样的，所
#以，把循环看成是一种特殊的尾递归函数也是可以的。

#尾递归是指，在函数返回的时候，调用自身本身，并且，return语句不能包含表达式。这
#样，编译器或者解释器就可以把尾递归做优化，使递归本身无论调用多少次，都只占用一
#个栈帧，不会出现栈溢出的情况。

#上面的fact(n)函数由于return n * fact(n - 1)引入了乘法表达式，所以就不是尾递归了。
#要改成尾递归方式，需要多一点代码，主要是要把每一步的乘积传入到递归函数中：

def fact(n):
    return fact_iter(1, 1, n)

def fact_iter(product, count, max):
    if count > max:
        return product
    return fact_iter(product * count, count + 1, max)
#可以看到，return fact_iter(product * count, count + 1, max)仅返回递归函数本身，
#product * count和count + 1在函数调用前就会被计算，不影响函数调用。

#fact(5)对应的fact_iter(1, 1, 5)的调用如下：

#===> fact_iter(1, 1, 5)
#===> fact_iter(1, 2, 5)
#===> fact_iter(2, 3, 5)
#===> fact_iter(6, 4, 5)
#===> fact_iter(24, 5, 5)
#===> fact_iter(120, 6, 5)
#===> 120
#尾递归调用时，如果做了优化，栈不会增长，因此，无论多少次调用也不会导致栈溢出。

#遗憾的是，大多数编程语言没有针对尾递归做优化，Python解释器也没有做优化，所以，
#即使把上面的fact(n)函数改成尾递归方式，也会导致栈溢出。

#有一个针对尾递归优化的decorator，可以参考源码：

#http://code.activestate.com/recipes/474088-tail-call-optimization-decorator/

#我们后面会讲到如何编写decorator。现在，只需要使用这个@tail_call_optimized，就可
#以顺利计算出fact(1000)：

#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->       4 函数作为返回值        <--<--<--<--<--<--<-#
#******************************************************************************#
#高阶函数除了可以接受函数作为参数外，还可以把函数作为结果值返回。
#我们来实现一个可变参数的求和。通常情况下，求和的函数是这样定义的：
def calc_sum(*args):
    ax = 0
    for n in args:
        ax = ax + n
    return ax
#但是，如果不需要立刻求和，而是在后面的代码中，根据需要再计算怎么办？可以不返回
#求和的结果，而是返回求和的函数！
def lazy_sum(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum
#当我们调用lazy_sum()时，返回的并不是求和结果，而是求和函数：
>>> f = lazy_sum(1, 3, 5, 7, 9)
>>> f
<function sum at 0x10452f668>
#调用函数f时，才真正计算求和的结果：
>>> f()
25
#在这个例子中，我们在函数lazy_sum中又定义了函数sum，并且，内部函数sum可以引用外
#部函数lazy_sum的参数和局部变量，当lazy_sum返回函数sum时，相关参数和变量都保存
#在返回的函数中，这种称为“闭包（Closure）”的程序结构拥有极大的威力。

#请再注意一点，当我们调用lazy_sum()时，每次调用都会返回一个新的函数，即使传入相
#同的参数：
>>> f1 = lazy_sum(1, 3, 5, 7, 9)
>>> f2 = lazy_sum(1, 3, 5, 7, 9)
>>> f1==f2
False
#f1()和f2()的调用结果互不影响。
#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->          5 匿名函数           <--<--<--<--<--<--<-#
#******************************************************************************#
#当我们在传入函数时，有些时候，不需要显式地定义函数，直接传入匿名函数更方便。
#在Python中，对匿名函数提供了有限支持。还是以map()函数为例，计算f(x)=x2时，除了
#定义一个f(x)的函数外，还可以直接传入匿名函数：
>>> map(lambda x: x * x, [1, 2, 3, 4, 5, 6, 7, 8, 9])
[1, 4, 9, 16, 25, 36, 49, 64, 81]
#通过对比可以看出，匿名函数lambda x: x * x实际上就是：
def f(x):
    return x * x
#关键字lambda表示匿名函数，冒号前面的x表示函数参数。
#匿名函数有个限制，就是只能有一个表达式，不用写return，返回值就是该表达式的结果。
#用匿名函数有个好处，因为函数没有名字，不必担心函数名冲突。此外，匿名函数也是一
#个函数对象，也可以把匿名函数赋值给一个变量，再利用变量来调用该函数：
>>> f = lambda x: x * x
>>> f
<function <lambda> at 0x10453d7d0>
>>> f(5)
25
#同样，也可以把匿名函数作为返回值返回，比如：
def build(x, y):
    return lambda: x * x + y * y
#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->           5 装饰器            <--<--<--<--<--<--<-#
#******************************************************************************#
#函数也是一个对象，而且函数对象可以被赋值给变量，所以，通过变量也能调用该函数。
>>> def now():
...     print '2013-12-25'
...
>>> f = now
>>> f()
2013-12-25
#函数对象有一个__name__属性，可以拿到函数的名字：
>>> now.__name__
'now'
>>> f.__name__
'now'
#现在，假设我们要增强now()函数的功能，比如，在函数调用前后自动打印日志，但又不希
#望修改now()函数的定义，这种在代码运行期间动态增加功能的方式，称之为“装饰器”
#（Decorator）。

#本质上，decorator就是一个返回函数的高阶函数。所以，我们要定义一个能打印日志的
#decorator，可以定义如下：
def log(func):
    def wrapper(*args, **kw):
        print 'call %s():' % func.__name__
        return func(*args, **kw)
    return wrapper
#观察上面的log，因为它是一个decorator，所以接受一个函数作为参数，并返回一个函数。
#我们要借助Python的@语法，把decorator置于函数的定义处：
@log
def now():
    print '2013-12-25'
#调用now()函数，不仅会运行now()函数本身，还会在运行now()函数前打印一行日志：
>>> now()
call now():
2013-12-25

#把@log放到now()函数的定义处，相当于执行了语句：
now = log(now)
#由于log()是一个decorator，返回一个函数，所以，原来的now()函数仍然存在，只是现在
#同名的now变量指向了新的函数，于是调用now()将执行新函数，即在log()函数中返回的
#wrapper()函数。

#wrapper()函数的参数定义是(*args, **kw)，因此，wrapper()函数可以接受任意参数的
#调用。在wrapper()函数内，首先打印日志，再紧接着调用原始函数。

#如果decorator本身需要传入参数，那就需要编写一个返回decorator的高阶函数，写出来
#会更复杂。比如，要自定义log的文本：
def log(text):
    def decorator(func):
        def wrapper(*args, **kw):
            print '%s %s():' % (text, func.__name__)
            return func(*args, **kw)
        return wrapper
    return decorator
#这个3层嵌套的decorator用法如下：
@log('execute')
def now():
    print '2013-12-25'
#执行结果如下：
>>> now()
execute now():
2013-12-25
#和两层嵌套的decorator相比，3层嵌套的效果是这样的：
>>> now = log('execute')(now)
#我们来剖析上面的语句，首先执行log('execute')，返回的是decorator函数，再调用返
#回的函数，参数是now函数，返回值最终是wrapper函数。

#以上两种decorator的定义都没有问题，但还差最后一步。因为我们讲了函数也是对象，
#它有__name__等属性，但你去看经过decorator装饰之后的函数，它们的__name__已经从
#原来的'now'变成了'wrapper'：
>>> now.__name__
'wrapper'
#因为返回的那个wrapper()函数名字就是'wrapper'，所以，需要把原始函数的__name__
#等属性复制到wrapper()函数中，否则，有些依赖函数签名的代码执行就会出错。

#不需要编写wrapper.__name__ = func.__name__这样的代码，Python内置的
#functools.wraps就是干这个事的，所以，一个完整的decorator的写法如下：
import functools
def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print 'call %s():' % func.__name__
        return func(*args, **kw)
    return wrapper
#或者针对带参数的decorator：
import functools

def log(text):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            print '%s %s():' % (text, func.__name__)
            return func(*args, **kw)
        return wrapper
    return decorator
#import functools是导入functools模块。模块的概念稍候讲解。现在，只需记住在定义
#wrapper()的前面加上@functools.wraps(func)即可。

#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->           5 偏函数            <--<--<--<--<--<--<-#
#******************************************************************************#
#Python的functools模块提供了很多有用的功能，其中一个就是偏函数
#（Partial function）。要注意，这里的偏函数和数学意义上的偏函数不一样。
#当函数的参数个数太多，需要简化时，使用functools.partial可以创建一个新的函数，这
#个新函数可以固定住原函数的部分参数，从而在调用时更简单。

#int()函数可以把字符串转换为整数，当仅传入字符串时，int()函数默认按十进制转换：
>>> int('12345')
12345
#但int()函数还提供额外的base参数，默认值为10。如果传入base参数，就可以做N进制的
#转换：
>>> int('12345', base=8)
5349
>>> int('12345', 16)
74565
#假设要转换大量的二进制字符串，每次都传入int(x, base=2)非常麻烦，于是，我们想到
#，可以定义一个int2()的函数，默认把base=2传进去：
def int2(x, base=2):
    return int(x, base)
#这样，我们转换二进制就非常方便了：
>>> int2('1000000')
64
>>> int2('1010101')
85
#functools.partial就是帮助我们创建一个偏函数的，不需要我们自己定义int2()，可以
#直接使用下面的代码创建一个新的函数int2：
>>> import functools
>>> int2 = functools.partial(int, base=2)
>>> int2('1000000')
64
>>> int2('1010101')
85
#所以，简单总结functools.partial的作用就是，把一个函数的某些参数（不管有没有默认
#值）给固定住（也就是设置默认值），返回一个新的函数，调用这个新函数会更简单。

#注意到上面的新的int2函数，仅仅是把base参数重新设定默认值为2，但也可以在函数调用
#时传入其他值：

>>> int2('1000000', base=10)
1000000
#最后，创建偏函数时，要从右到左固定参数，就是说，对于函数f(a1, a2, a3)，可以固定
#a3，也可以固定a3和a2，也可以固定a3，a2和a1，但不要跳着固定，比如只固定a1和a3，
#把a2漏下了。如果这样做，调用新的函数会更复杂，可以自己试试。
'''
