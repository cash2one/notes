#_*_coding:UTF-8_*_

'''
��Ϊ������class������һ��������ǲ��񵽸�class��һ��ʵ������ˣ����󲢲���ƾ�ղ����� |
���������ⴴ�����׳��ġ�Python�����ú������׳��ܶ����͵Ĵ��������Լ���д�ĺ���Ҳ�� |
���׳��������Ҫ�׳��������ȸ�����Ҫ�����Զ���һ�������class��ѡ��ü̳й�ϵ��Ȼ|
����raise����׳�һ�������ʵ����                                                  |

ִ�У����������ٵ������Լ�����Ĵ���

$ python err.py
Traceback (most recent call last):
  ...
__main__.FooError: invalid value: 0
                                                                                     |
ֻ���ڱ�Ҫ��ʱ��Ŷ��������Լ��Ĵ������͡��������ѡ��Python���е����õĴ������ͣ��� |
��ValueError��TypeError��������ʹ��Python���õĴ������͡�
'''
# err.py
class FooError(StandardError):
    pass

def foo(s):
    n = int(s)
    if n==0:
        raise FooError('invalid value: %s' % s)
    return 10 / n

foo(0)
