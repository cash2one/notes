'''
----> 1 
---->====> 1.1
---->====>####> 1.1.1


--> Classes Generate Multiple Instance Objects
 there are two kinds of objects in Python’s OOP model: class objects and instance ob-
 jects. Class objects provide default behavior and serve as factories for instance o-
 bjects. Instance objects are the real objects your programs process—each is a names-
 pace in its own right, but inherits (i.e., has automatic access to) names in the cl-
 ass from which it was created. Class objects come from statements, and instances co-
 me from calls; each time you call a class, you get a new instance of that class.
 
 -->--> Class Objects Provide Default Behavior
  When we run a class statement, we get a class object. Here’s a rundown of the  main
  properties of Python classes:
  1 The @class statement creates a class object and assigns it a name. Just like  the 
    function @def statement, the Python @class statement is an executable statement .
    When reached and run, it generates a new class object and assigns it to the  name
    in the class header. Also, like @defs, @class statements typically run when the -
	files they are coded in are first imported.
  2 Assignments inside @class statements make class attributes. Just like in module -
    files, top-level assignments within a @class statement (not nested in a def) gen-
	erate attributes in a class object. Technically, the @class statement defines a -
	local scope that morphs into the attribute namespace of the class object, just l-
	ike a module’s global scope. After running a @class statement, class attributes -
	are accessed by name qualification: object.name.
  3 Class attributes provide object state and behavior. Attributes of a class  object
    record state information and behavior to be shared by all instances created  from
    the class; function @def statements nested inside a @class generate methods, whi-
	ch process instances.

 -->--> Instance Objects Are Concrete Items
  When we call a class object, we get an instance object. Here’s an overview of the -
  key points behind class instances:
  1 Calling a class object like a function makes a new instance object. Each time a -
    class is called, it creates and returns a new instance object. Instances represe-
	nt concrete items in your program’s domain.
  2 Each instance object inherits class attributes and gets its own namespace. Insta-
    nce objects created from classes are new namespaces; they start out empty but in-
	herit attributes that live in the class objects from which they were generated.
  3 Assignments to attributes of @self in methods make per-instance attributes. Insi-
    de a class’s method functions, the first argument (called @self by convention) r-
	eferences the instance object being processed; assignments to attributes of @self
    create or change data in the instance, not the class.
	
  The end result is that classes define common, shared data and behavior, and generate
  instances. Instances reflect concrete application entities, and record  per-instance 
  data that may vary per object.
  
 -->--> A First Example
 
  >>> class FirstClass:            # Define a class object
         def setdata(self, value): # Define class's methods
             self.data = value     # self is the instance
         def display(self):
             print(self.data)      # self.data: per instance
			 
  Like all compound statements, the @class starts with a header line that lists the -
  class name, followed by a body of one or more nested and (usually) indented statem-
  ents. Here, the nested statements are @defs; they define functions that implement -
  the behavior the class means to export.
  
  As we learned in Part IV, @def is really an assignment. Here, it assigns function -
  objects to the names @setdata and @display in the class statement’s scope, and so -
  generates attributes attached to the class—FirstClass.setdata and FirstClass.display. 
  In fact, any name assigned at the top level of the class’s nested block becomes  an 
  attribute of the class. Functions inside a class are usually called methods. But in 
  a method function, the first argument automatically receives an implied instance o-
  bject when called—the subject of the call.
  
  >>> x = FirstClass() # Make two instances
  >>> y = FirstClass() # Each is a new namespace
  By calling the class this way (notice the parentheses), we generate instance objec-
  ts, which are just namespaces that have access to their classes’ attributes. at th-
  is point, we have three objects: two instances and a class.
  
   +-------+
   |   X   |         is-a               +------------+
   | -data |--------------------------->| FirstClass |
   +-------+                            |            |
                                        | -setdata   |
   +-------+                            | -display   |
   |   X   |         is-a               |            |
   | -data |--------------------------->|            |
   +-------+                            +------------+
  Figure 27-1. Classes and instances are linked namespace objects in a class tree th-
  at is searched by inheritance. Here, the "data" attribute is found in instances, b-
  ut "setdata" and "display" are in the class above them.
  
  The two instances start out empty but have links back to the class from which  they
  were generated. 
  >>> x.setdata("King Arthur") # Call methods: self is x
  >>> y.setdata(3.14159) # Runs: FirstClass.setdata(y, 3.14159)
  Neither x nor y has a @setdata attribute of its own, so to find it, Python  follows 
  the link from instance to class. And that’s about all there is to inheritance in  -
  Python: it happens at attribute qualification time, and it just involves looking up 
  names in linked objects—here, by following the is-a links in Figure 27-1.
  
  In the @setdata function inside FirstClass, the value passed in is assigned to    -
  self.data. Within a method, @self—the name given to the leftmost argument by conve-
  ntion—automatically refers to the instance being processed (x or y), so the assign-
  ments store values in the instances’ namespaces, not the class’s; that’s how the  -
  @data names in Figure 27-1 are created.
  
  >>> x.display() # self.data differs in each instance
  King Arthur
  >>> y.display() # Runs: FirstClass.display(y)
  3.14159
  In fact, if we were to call @display on one of our instances before calling @setdata, 
  we would trigger an undefined name error—the attribute named data doesn’t even exi-
  st in memory until it is assigned within the @setdata method.
  
  we could even generate an entirely new attribute in the instance’s namespace by as-
  signing to its name outside the class’s method functions:
  >>> x.anothername = "spam" # Can set new attributes here too!
  This would attach a new attribute called @anothername, which may or may not be used
  by any of the class’s methods, to the instance object x.

--> The @class Statement 
 @class is a compound statement, with a body of statements typically indented appear-
 ing under the header. In the header, superclasses are listed in parentheses after t-
 he class name, separated by commas. Listing more than one superclass leads to multi-
 ple inheritance, which we’ll discuss more formally in Chapter 31. Here is the state-
 ment’s general form:

 class name(superclass,...): # Assign to name
   attr = value # Shared class data
   def method(self,...): # Methods
     self.attr = value # Per-instance data

 Within the @class statement, any assignments generate class attributes, and special-
 ly named methods overload operators; for instance, a function called __init__ is ca-
 lled at instance object construction time, if defined.

 Like a @def, a @class statement is an object builder,and an implicit assignment—when 
 run, it generates a class object and stores a reference to it in the name used in t-
 he header. Also like a def, a class statement is true executable code—your class do-
 esn’t exist until Python reaches and runs the class statement that defines it. 
 
 As we’ve seen, classes are mostly just @namespaces-that is, tools for defining names
 (i.e., attributes) that export data and logic to clients. When Python executes a cl-
 ass statement (not a call to a class), it runs all the statements in its body,  from 
 top to bottom. Assignments that happen during this process create names in the     -
 class’s local scope, which become attributes in the associated class object. Because 
 of this, classes resemble both modules and functions:
 1 Like functions, class statements are local scopes where names created by nested a-
   ssignments live.
 2 Like names in a module, names assigned in a class statement become attributes in -
   a class object.
 Typically, assignment statements inside the @class statement make data attributes, -
 and nested defs make method attributes. 
 
 class MixedNames: # Define class
   data = 'spam' # Assign class attr
   def __init__(self, value): # Assign method name
     self.data = value # Assign instance attr
   def display(self):
     print(self.data, MixedNames.data) # Instance attr, class attr
	 
 This class contains two defs, which bind class attributes to method functions. It a-
 lso contains an = assignment statement; because this assignment assigns the name   -
 @data inside the class, it lives in the class’s local scope and becomes an attribute 
 of the class object. Like all class attributes, this @data is inherited and shared -
 by all instances of the class that don’t have @data attributes of their own. When we 
 make instances of this class, the name @data is attached to those instances by the -
 assignment to self.data in the constructor method:
 
 >>> x = MixedNames(1) # Make two instance objects
 >>> y = MixedNames(2) # Each has its own data
 >>> x.display(); y.display() # self.data differs, MixedNames.data is the same
 1 spam
 2 spam
 
 The net result is that @data lives in two places: in the instance objects (created -
 by the self.data assignment in __init__), and in the class from which they inherit -
 names(created by the @data assignment in the class). The class’s @display method pr-
 ints both versions, by first qualifying the self instance, and then the class.

--> Methods
 Methods are just function objects created by @def statements nested in a class stat-
 ement’s body.  a method’s first argument always receives the instance object that is 
 the implied subject of the method call.
 
 In other words, Python automatically maps instance method calls to a class’s  method
 functions as follows. Method calls made through an instance, like this:
   instance.method(args...)
 are automatically translated to class method function calls of this form:
   class.method(instance, args...)
   
 -->--> Method Example
 
  class NextClass:           # Define class
    def printer(self, text): # Define method
      self.message = text    # Change instance
      print(self.message)    # Access instance
  
  The name @printer references a function object; because it’s assigned in the  class 
  statement’s scope, it becomes a class object attribute and is inherited by every i-
  nstance made from the class.
  
  >>> x = NextClass() # Make instance
  >>> x.printer('instance call') # Call its method
  instance call
  >>> x.message # Instance changed
  'instance call'
  
  When we call the method by qualifying an instance like this, @printer is first loc-
  ated by inheritance, and then its @self argument is automatically assigned the ins-
  tance object (x); the @text argument gets the string passed at the call ( 'instance 
  call'). Notice that because Python automatically passes the first argument to @self 
  for us, we only actually have to pass in one argument. Inside @printer, the name  -
  @self is used to access or set per-instance data because it refers back to the ins-
  tance currently being processed.
  
  >>> NextClass.printer(x, 'class call') # Direct class call
  class call
  >>> x.message # Instance changed again
  'class call'
  
  As we’ve seen, though, methods may be called in one of two ways—through an instanc-
  e, or through the class itself. For example, we can also call @printer by going th-
  rough the class name, provided we pass an instance to the self argument explicitly.
  
  





  
  
  
  
  
  




--> Creating Classes
 Python classes are created using the @class keyword. 
 |class ClassName(bases):
 |    'class documentation string'
 |    class_suite
 
 类是创建实例的模板，实例是具体的对象。                                              |
                                                                                     |
 |class Student(object):                                                             |
 |    pass	                                                                         |
 class后是类名Student，类名通常是大写开头的单词。紧接着是(object)，表示该类是从哪个类|
 继承下来的，通常，如果没有合适的继承类，就使用object类，这是所有类最终都会继承的类。|
 创建实例是通过 类名+() 实现的                                                       |
 bart = Student() #创建了一个类的实例bart                                            |
 
 复杂一些的例子
 -------------------------------
 class Student(object):
 
     def __init__(self, name, score):
         self.name = name
         self.score = score
 		
     def print_score(self):
         print '%s: %s' % (self.name, self.score)		                             
 --------------------------------
 
--> Class Attributes
 An attribute is a data or functional element that belongs to another object and is -
 accessed via the familiar dotted-attribute notation. One interesting side note about 
 attributes is that when you are accessing an attribute, it is also an object and may 
 have attributes of its own which you can then access, leading to a chain of attribu-
 tes, i.e., myThing.subThing.subSubThing, etc. 
 
 -->--> Class Data Attributes
  Data attributes are simply variables of the class we are defining. Such  attributes 
  are better known to OO programmers as static members, class variables, or static d-
  ata. They represent data that is tied to the class object they belong to and are i-
  ndependent of any class instances. 
  
  Here is an example of using a class data attribute (foo):
  >>> class C(object):
  ... foo = 100
  >>> print C.foo
  100
  >>> C.foo = C.foo + 1
  >>> print C.foo
  101
  Note that nowhere in the code above do you see any references to class instances.

 -->--> Methods (Bound and Unbound Methods)
  In keeping with OOP tradition, Python imposes the restriction that methods cannot -
  be invoked without instances. An instance must be used to perform method calls. Th-
  is restriction describes Python’s concept of binding, where methods must be bound -
  (to an instance) in order to be invoked directly. Unbound methods may also be call-
  ed, but an instance object must be provided explicitly in order for the  invocation 
  to succeed. However, regardless of binding, methods are inherently attributes of t-
  he class they are defined in, even if they are almost always invoked via an instan-
  ce. 

 -->--> Determining Class Attributes
   dir(C)
   C.__dict__
   C.__name__ String name of class C
   C.__doc__ Documentation string for class C
   C.__bases__ Tuple of class C’s parent classes
   C.__dict__ Attributes of C
   C.__module__ Module where C is defined (new in 1.5)
   C.__class__ Class of which C is an instance (new-style classes only)
  
--> Instances
 Instantiation is realized with use of the function operator, as in the following ex-
 ample:
 >>> class MyClass(object): # define class
 ... pass
 >>> mc = MyClass() # instantiate class  
 As you can see, creating instance @mc of class MyClass consists of “calling” the cl-
 ass: MyClass(). The returned object is an instance of the class you called. When you 
 “call” a class using the functional notation, the interpreter instantiates the obje-
 ct, and calls the closest thing Python has to a constructor (if you have written one 
 ) to perform any final customization such as setting instance attributes, and final-
 ly returns the instance to you.
 
 -->--> __init__() “Constructor ” Method
  When the class is invoked, the first step in the instantiation process is to create 
  the instance object. Once the object is available, Python checks if an __init__() -
  method has been implemented. By default, no special actions are enacted on the ins-
  tance without the definition of (or the overriding) of the special method         -
  __init__(). __init__() should not return any object (or return None);
  
 -->--> __new__() “Constructor ” Method
  todo
 -->--> __del__() “Destructor ” Method
  todo
  
--> Instance Attributes
 Instances have only data attributes (methods are strictly class attributes) and  are 
 simply data values that you want to be associated with a particular instance of  any 
 class and are accessible via the familiar dotted-attribute notation. These values a-
 re independent of any other instance or of the class it was instantiated from.  When 
 an instance is deallocated, so are its attributes. 
 
 Instance attributes can be set any time after an instance has been created, in any -
 piece of code that has access to the instance. However, one of the key places  where 
 such attributes are set is in the constructor, __init__().
 
 dir(I)
 >>> class C(object):
 ... pass
 >>> c = C()
 >>> c.foo = 'roger'
 >>> c.bar = 'shrubber'
 >>> dir(c)
 ['__class__', '__delattr__', '__dict__', '__doc__',
 '__getattribute__', '__hash__', '__init__', '__module__',
 '__new__', '__reduce__', '__reduce_ex__', '__repr__',
 '__setattr__', '__str__', '__weakref__', 'bar', 'foo']
 
 I.__class__  Class from which I is instantiated
 I.__dict__   Attributes of I
 
 >>> class C(object): # define class
 ... pass
 ...
 >>> c = C() # create instance
 >>> dir(c) # instance has no attributes
 []
 >>> c.__dict__ # yep, definitely no attributes
 {}
 >>> c.__class__ # class that instantiated us
 <class '__main__.C'>
 >>> c.foo = 1
 >>> c.bar = 'SPAM'
 >>> '%d can of %s please' % (c.foo, c.bar)
 '1 can of SPAM please'
 >>> c.__dict__
 {'foo': 1, 'bar': 'SPAM'}

--> Instance Attributes versus Class Attributes
 Classes and instances are both namespaces. Classes are namespaces for class attribu-
 tes. Instances are namespaces for instance attributes. 

 Class attribute changes are reflected across all instances 
 
 Class attributes can be accessed via a class or an instance. In the example below, -
 when class C is created with the version class attribute, naturally access is allow-
 ed using the class object, i.e., C.version. When instance c is created, access to  -
 c.version fails for the instance, and then Python initiates a search for the name  -
 version first in the instance, then the class, and then the base classes in the inh-
 eritance tree. In this case, it is found in the class:
 >>> class C(object): # define class
 ... version = 1.2 # static member
 ...
 >>> c = C() # instantiation
 >>> C.version # access via class
 1.2 
 >>> c.version # access via instance
 1.2
 >>> C.version += 0.1 # update (only) via class
 >>> C.version # class access
 1.3
 >>> c.version # instance access, which
 1.3 # also reflected change
 However, we can only update the value when referring to it using the class, as in t-
 he C.version increment statement above. Attempting to set or update the class attri-
 bute using the instance name will create an instance attribute that “shadows” access 
 to the class attribute, effectively hiding it from scope until or unless that shadow 
 is removed.
 
 Any type of assignment of a local attribute will result in the creation and assignm-
 ent of an instance attribute, just like a regular Python variable. If a class attri-
 bute exists with the same name, interesting side effects can occur.
 >>> class Foo(object):
 ... x = 1.5
 ...
 >>> foo = Foo()
 >>> foo.x
 1.5
 >>> foo.x = 1.7 # try to update class attr
 >>> foo.x # looks good so far...
 1.7
 >>> Foo.x # nope, just created a new inst attr
 1.5
 >>> del foo.x # delete instance attribute
 >>> foo.x # can now access class attr again
 1.5 
 
 >>> foo.x += .2 # foo.x = Foo.x + 0.2
 >>> foo.x
 1.7
 >>> Foo.x # nope, same thing
 1.5
 
 But… all of this changes if the class attribute is mutable:
 >>> class Foo(object):
 ... x = {2003: 'poe2'}
 ...
 >>> foo = Foo()
 >>> foo.x
 {2003: 'poe2'}
 >>> foo.x[2004] = 'valid path'
 >>> foo.x
 {2003: 'poe2', 2004: 'valid path'}
 >>> Foo.x # it works!!!
 {2003: 'poe2', 2004: 'valid path'}
 >>> del foo.x # no shadow so cannot delete
 Traceback (most recent call last):
 File "<stdin>", line 1, in ?
 del foo.x
 AttributeError: x
 >>>
 
--> Binding and Method Invocation
 First, a method is simply a function defined as part of a class. (This means that  -
 methods are class attributes and not instance attributes). 
 
 Second, methods can be called only when there is an instance of the class upon whic-
 h the method was invoked. When there is an instance present, the method is consider-
 ed bound (to that instance). Without an instance, a method is considered unbound.
 
 And finally, the first argument in any method definition is the variable @self, whi-
 ch represents the instance object invoking the method.
 
 @self
 The variable @self is used in class instance methods to reference the instance to w-
 hich the method is bound. Because a method’s instance is always passed as the  first 
 argument in any method call, @self is the name that was chosen to represent the ins-
 tance. You are required to put @self in the method declaration but do not need to a-
 ctually use the instance (self) within the method.

--> Static Methods and Class Methods

 Static methods are exactly what they are if you are coming from C++ or Java. They a-
 re simply functions (no instance required) that are part of class definitions. Using 
 module functions is still far more common than using static class methods.
 
 Recall that regular methods require an instance (self) as the first argument, and u-
 pon (bound) method invocation, @self is automagically passed to the method. Well, f-
 or class methods, instead of the instance, the class is required as the first argum-
 ent, and it is passed in to the method by the interpreter. The class does not need -
 to be specifically named like self, but most people use @cls as the variable name.

 Now let us look at some examples of these types of methods using classic classes (y-
 ou can also use new-style classes if you want to):
 |class TestStaticMethod:
 |    def foo():
 |        print 'calling static method foo()'
 |    foo = staticmethod(foo)
 |
 |class TestClassMethod:
 |    def foo(cls):
 |        print 'calling class method foo()'
 |        print 'foo() is part of class:', cls.__name__
 |    foo = classmethod(foo)
 The corresponding built-in functions are converted into their respective types and -
 are reassigned back to the same variable name.
 >>> tsm = TestStaticMethod()
 >>> TestStaticMethod.foo()
 calling static method foo()
 >>> tsm.foo()
 calling static method foo()
 >>>
 >>> tcm = TestClassMethod()
 >>> TestClassMethod.foo()
 calling class method foo()
 foo() is part of class: TestClassMethod
 >>> tcm.foo()
 calling class method foo()
 foo() is part of class: TestClassMethod
 
 By using decorators, we can avoid the reassignment above:
 |class TestStaticMethod:
 |    @staticmethod
 |    def foo():
 |        print 'calling static method foo()'
 |
 |class TestClassMethod:
 |    @classmethod
 |    def foo(cls):
 |        print 'calling class method foo()'
 |        print 'foo() is part of class:', cls.__name__







 
----> Attributes, Functions, and Methods
The self parameter is, in fact, what distinguishes methods from functions. Methods (-
or, more technically, bound methods) have their first parameter bound to the instance 
they belong to, so you don’t have to supply it. While you can certainly bind an attr-
ibute to a plain function, it won’t have that special self parameter:
>>> class Class:
        def method(self):
            print 'I have a self!'
>>> def function():
print "I don't..."
>>> instance = Class()
>>> instance.method()
I have a self!
>>> instance.method = function
>>> instance.method()
I don't...
Note that the self parameter is not dependent on calling the method the way I’ve done
until now, as instance.method. You’re free to use another variable that refers to the 
same method:
>>> class Bird:
song = 'Squaawk!'
def sing(self):
print self.song
>>> bird = Bird()
>>> bird.sing()
Squaawk!
>>> birdsong = bird.sing
>>> birdsong()
Squaawk!
Even though the last method call looks exactly like a function call, the variable   -
birdsong refers to the bound method bird.sing, which means that it still has access -
to the self parameter (that is, it is still bound to the same instance of the class).

----> The Class Namespace
The following two statements are (more or less) equivalent:
    def foo(x): return x*x
    foo = lambda x: x*x
Both create a function that returns the square of its argument, and both bind the va-
riable foo to that function. The name foo may be defined in the global (module) scop-
e, or it may be local to some function or method. The same thing happens when you de-
fine a class: all the code in the class statement is executed in a special  namespace 
, the class namespace.This namespace is accessible later by all members of the class. 
Not all Python programmers know that class definitions are simply code sections  that 
are executed, but it can be useful information. For example, you aren’t restricted to 
def statements inside the class definition block:
>>> class C:
print 'Class C being defined...'
Class C being defined...
>>>
Okay, that was a bit silly. But consider the following:
class MemberCounter:
members = 0
def init(self):
MemberCounter.members += 1
>>> m1 = MemberCounter()
>>> m1.init()
>>> MemberCounter.members
1
>>> m2 = MemberCounter()
>>> m2.init()
>>> MemberCounter.members
2
In the preceding code, a variable is defined in the class scope, which can be access-
ed by all the members (instances), in this case to count the number of class members. 
Note the use of init to initialize all the instances: I’ll automate that (that is, t-
urn it into a proper constructor) in Chapter 9.
This class scope variable is accessible from every instance as well, just as  methods 
are:
>>> m1.members
2
>>> m2.members
2
What happens when you rebind the members attribute in an instance?
>>> m1.members = 'Two'
>>> m1.members
'Two'
>>> m2.members
2
The new members value has been written into an attribute in m1, shadowing the       -
class-wide variable. This mirrors the behavior of local and global variables in func-
tions, as discussed in the sidebar "The Problem of Shadowing" in Chapter 6.

----> Specifying a Superclass
subclasses expand on the definitions in their superclasses. You indicate the supercl-
ass in a class statement by writing it in parentheses after the class name:
class Filter:
    def init(self):
    self.blocked = []
    def filter(self, sequence):
        return [x for x in sequence if x not in self.blocked]

class SPAMFilter(Filter): # SPAMFilter is a subclass of Filter
    def init(self): # Overrides init method from Filter superclass
        self.blocked = ['SPAM']

Note two important points in the definition of SPAMFilter:
1 I override the definition of init from Filter by simply providing a new definition.
2 The definition of the filter method carries over (is inherited) from Filter, so yo-
  u don’t need to write the definition again.

>>> issubclass(SPAMFilter, Filter)
True
>>> issubclass(Filter, SPAMFilter)
False
>>> SPAMFilter.__bases__
(<class __main__.Filter at 0x171e40>,)
>>> Filter.__bases__
()
>>> s = SPAMFilter()
>>> isinstance(s, SPAMFilter)
True
>>> isinstance(s, Filter)
True
>>> isinstance(s, str)
False
>>> s.__class__
<class __main__.SPAMFilter at 0x1707c0>

----> Multiple Superclasses
classes:
    class Calculator:
        def calculate(self, expression):
        self.value = eval(expression)

class Talker:
    def talk(self):
        print 'Hi, my value is', self.value

class TalkingCalculator(Calculator, Talker):
    pass

The subclass (TalkingCalculator) does nothing by itself; it inherits all its behavior 
from its superclasses. The point is that it inherits both calculate from Calculator -
and talk from Talker, making it a talking calculator:
>>> tc = TalkingCalculator()
>>> tc.calculate('1+2*3')
>>> tc.talk()
Hi, my value is 7

This is called multiple inheritance, and can be a very powerful tool. However, unles-
s you know you need multiple inheritance, you may want to stay away from it, as it c-
an, in some cases, lead to unforeseen complications.
If you are using multiple inheritance, there is one thing you should look out for: i-
f a method is implemented differently by two or more of the superclasses (that is, y-
ou have two different methods with the same name), you must be careful about the ord-
er of these superclasses (in the class statement). The methods in the earlier classes 
override the methods in the later ones. So if the Calculator class in the preceding -
example had a method called talk, it would override (and make inaccessible) the  talk 
method of the Talker. Reversing their order,
like this:
class TalkingCalculator(Talker, Calculator): pass
would make the talk method of the Talker accessible. If the superclasses share a com-
mon superclass, the order in which the superclasses are visited while looking for a -
given attribute or method is called the method resolution order (MRO), and follows  a 
rather complicated algorithm. Luckily, it works very well, so you probably don’t need 
to worry about it.
  
+-----------------------------------------------------------------------------------+|
|-->-->-->-->-->-->-->-->-->-->-->-->      类 基础         <--<--<--<--<--<--<--<-- ||
+-----------------------------------------------------------------------------------+|
                                                                                     |
类是创建实例的模板，实例是具体的对象。                                               |
                                                                                     |
----> 1 通过class关键字定义类                                                        |
| class Student(object):                                                             |
|     pass	                                                                         |
class后是类名Student，类名通常是大写开头的单词。紧接着是(object)，表示该类是从哪个类 |
继承下来的，通常，如果没有合适的继承类，就使用object类，这是所有类最终都会继承的类。 |
创建实例是通过 类名+() 实现的                                                        |
bart = Student() #创建了一个类的实例bart                                             |
------------------------------------------------------------------------------------+|
----> 2 类的属性和方法                                                               |
self的概念(todo)                                                                     |
---->====> 2.1 属性：类中封装的变量 如下面的 name 、 score                           |
实例的变量名如果以__开头，就变成了一个私有变量（private），只有内部可以访问，外部不能|
访问。不能直接访问__name是因为Python解释器对外把__name变量改成了_Student__name，所以 |
，仍然可以通过_Student__name来访问__name变量：                                       |
* >>> bart._Student__name                                                            |
* 'Bart Simpson'                                                                     |
#变量名类似__xxx__的，是特殊变量，特殊变量是可以直接访问的，不是private变量。以一个下|
划线开头的实例变量名，比如_name表示虽然我可以被访问，但是，请把我视为私有变量，不要随|
意访问。                                                                             |
---->====> 2.2 方法：类中封装的函数 如下面的print_score                              |
------------------------------------------------------------------------------------+|
----> 3 创建实例的时候，可以初始化一些默认属性                                       |
通过定义一个特殊的__init__方法，在创建实例的时候，就把name，score等属性绑上去：      |
*  class Student(object):
*
*   def __init__(self, name, score):
*       self.name = name
*       self.score = score
*		
*   def print_score(self):
*       print '%s: %s' % (self.name, self.score)		                             |
__init__方法的第一个参数永远是self，表示创建的实例本身，因此，在__init__方法内部，就 |
可以把各种属性绑定到self，因为self就指向创建的实例本身。有了__init__方法，在创建实例 |
的时候，就不能传入空的参数了，必须传入与__init__方法匹配的参数，但self不需要传，     |		
* >>> bart = Student('Bart Simpson', 59)
* >>> bart.name
* 'Bart Simpson'
* >>> bart.score
* 59
* >>> bart.print_score()
* Bart Simpson: 59                                                                   |
Python允许对实例变量绑定任何数据，也就是说，对于两个实例变量，虽然它们都是同一个类的 |
不同实例，但拥有的变量名称都可能不同：                                               |
* >>> bart = Student('Bart Simpson', 59)
* >>> lisa=Student('Lisa Simpson', 87)
* >>> bart.age = 8
* >>> bart.age
* 8
* >>> lisa.age
* Traceback (most recent call last):
*   File "<stdin>", line 1, in <module>
* AttributeError: 'Student' object has no attribute 'age'
------------------------------------------------------------------------------------+|
----> 4 继承和多态                                                                   |
子类：定义一个class的时候，可以从某个现有的class继承，新的class称为子类(Subclass)子类|
      获得父类的全部功能，如果子类定义了相同的方法则覆盖父类的方法。
#     在继承关系中，如果一个实例的数据类型是某个子类，那它的数据类型也可以被看做是父类。但是，反过来就不行
#父类:被继承的class称为基类、父类或超类（Base class、Super class）。
#多态:有了继承，才能有多态。多态是指同一个方法在父类和子类中有不同的功能。
#     例如父类A定义了一个方法f,他的子类B和C分别重新定义了方法f.如果一个函数的入参是父类类型,此时子类也可以直接调用
#     子类B调用使用B中定义的方法,子类C调用使用C中定义的方法。
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->-->--> 5 动态添加属性和方法 <--<--<--<--<--<--<--<--<--*
#**************************************************************************************  
#正常情况下，当我们定义了一个class，创建了一个class的实例后，我们可以给该实例绑定任何属性和方法，这就是动态语言的灵活性。先定义class：
>>> class Student(object):
...     pass
...
#然后，尝试给实例绑定一个属性：
>>> s = Student()
>>> s.name = 'Michael' # 动态给实例绑定一个属性
>>> print s.name
Michael
#还可以尝试给实例绑定一个方法：
>>> def set_age(self, age): # 定义一个函数作为实例方法
...     self.age = age
...
>>> from types import MethodType
>>> s.set_age = MethodType(set_age, s, Student) # 给实例绑定一个方法
>>> s.set_age(25) # 调用实例方法
>>> s.age # 测试结果
25
#但是，给一个实例绑定的方法，对另一个实例是不起作用的：
>>> s2 = Student() # 创建新的实例
>>> s2.set_age(25) # 尝试调用方法
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'Student' object has no attribute 'set_age'
#为了给所有实例都绑定方法，可以给class绑定方法：
>>> def set_score(self, score):
...     self.score = score
...
>>> Student.set_score = MethodType(set_score, None, Student)
#给class绑定方法后，所有实例均可调用：
>>> s.set_score(100)
>>> s.score
100
>>> s2.set_score(99)
>>> s2.score
99
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->-->--> 6 限制类的属性和方法 <--<--<--<--<--<--<--<--<--*
#************************************************************************************** 
#如果我们想要限制class的属性怎么办？比如，只允许对Student实例添加name和age属性。
#为了达到限制的目的，Python允许在定义class的时候，定义一个特殊的__slots__变量，来限制该class能添加的属性：
>>> class Student(object):
...     __slots__ = ('name', 'age') # 用tuple定义允许绑定的属性名称
...
#然后，我们试试：
>>> s = Student() # 创建新的实例
>>> s.name = 'Michael' # 绑定属性'name'
>>> s.age = 25 # 绑定属性'age'
>>> s.score = 99 # 绑定属性'score'
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'Student' object has no attribute 'score'
#由于'score'没有被放到__slots__中，所以不能绑定score属性，试图绑定score将得到AttributeError的错误。
#使用__slots__要注意，__slots__定义的属性仅对当前类起作用，对继承的子类是不起作用的：
>>> class GraduateStudent(Student):
...     pass
...
>>> g = GraduateStudent()
>>> g.score = 9999
#除非在子类中也定义__slots__，这样，子类允许定义的属性就是自身的__slots__加上父类的__slots__。
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->--> 7 把方法变成属性@property <--<--<--<--<--<--<--<-- *
#************************************************************************************** 
#Python内置的@property装饰器就是负责把一个方法变成属性调用的：
class Student(object):

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, value):
        if not isinstance(value, int):
            raise ValueError('score must be an integer!')
        if value < 0 or value > 100:
            raise ValueError('score must between 0 ~ 100!')
        self._score = value
#@property的实现比较复杂，我们先考察如何使用。把一个getter方法变成属性，
#只需要加上@property就可以了，此时，@property本身又创建了另一个装饰器@score.setter，
#负责把一个setter方法变成属性赋值，于是，我们就拥有一个可控的属性操作：
>>> s = Student()
>>> s.score = 60 # OK，实际转化为s.set_score(60)
>>> s.score # OK，实际转化为s.get_score()
60
>>> s.score = 9999
Traceback (most recent call last):
  ...
ValueError: score must between 0 ~ 100!
#注意到这个神奇的@property，我们在对实例属性操作的时候，就知道该属性很可能不是直接暴露的，而是通过getter和setter方法来实现的。
#还可以定义只读属性，只定义getter方法，不定义setter方法就是一个只读属性：
class Student(object):

    @property
    def birth(self):
        return self._birth

    @birth.setter
    def birth(self, value):
        self._birth = value

    @property
    def age(self):
        return 2014 - self._birth
#上面的birth是可读写属性，而age就是一个只读属性，因为age可以根据birth和当前时间计算出来。
#
#
#
#
#

#
#
#
#
#
#
'''
