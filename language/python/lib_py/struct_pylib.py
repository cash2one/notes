'''                                                                                  |
Python��һ�ŷǳ��������ԣ������������͵ı�ʾ��������������Ԥ������������ͣ��磺�� |
C#�У������;Ͷ�����8�֣�����ֻ���������ֻ������ͣ��ַ�������������������Ԫ�飬�б�|
�ֵ䡣ͨ���������������ͣ����ǿ�����ɴ󲿷ֹ���������Python��Ҫͨ��������������ƽ̨ |
���н�����ʱ�򣬱��뿼�ǵ�����Щ��������������ƽ̨������֮������ͽ��л���ת�����⡣ |
����ȷ���C++д�Ŀͻ��˷���һ��int��(4�ֽ�)���������ݵ�Pythonд�ķ�������Python���յ�|
��ʾ���������4���ֽ����ݣ���ô������Python��ʶ�������أ� Python�ı�׼ģ��struct���� |
�����������⡣                                                                     |

----> �ֽ�˳��                                                                       |
����ĺ���ֽ�˳��Ĭ�������ɲ���ϵͳ�ľ����ģ���Ȼstructģ��Ҳ�ṩ���Զ����ֽ�˳��� |
���ܣ�����ָ����˴洢��С�˴洢���ض����ֽ�˳�򣬶��ڵײ�ͨ�ŵ��ֽ�˳����ʮ����Ҫ�� |
����ͬ���ֽ�˳��ʹ洢��ʽҲ�ᵼ���ֽڴ�С�Ĳ�ͬ����format�ַ���ǰ������ض��ķ��ż� |
���Ա�ʾ��ͬ���ֽ�˳��洢��ʽ���������С�˴洢 s = struct.Struct(��<I3sf��)�Ϳ����ˡ�|
�ٷ�api library Ҳ�ṩ����Ӧ�Ķ����б�                                             |
Character    Byte order                Size        Alignment
@            native                    native      native
=            native                    standard    none
<            little-endian             standard    none
>            big-endian                standard    none
!            network (= big-endian)    standard    none

----> Format Characters
Format    C Type                Python type          Standard size    Notes
x         pad byte              no value          
c         char                  string of length 1   1     
b         signed char           integer              1                (3)
B         unsigned char         integer              1                (3)
?         _Bool                 bool                 1                (1)
h         short                 integer              2                (3)
H         unsigned short        integer              2                (3)
i         int                   integer              4                (3)
I         unsigned int          integer              4                (3)
l         long                  integer              4                (3)
L         unsigned long         integer              4                (3)
q         long long             integer              8                (2), (3)
Q         unsigned long long    integer              8                (2), (3)
f         float                 float                4                (4)
d         double                float                8                (4)
s         char[]                string          
p         char[]                string          
P         void *                integer                               (5), (3)


'''




