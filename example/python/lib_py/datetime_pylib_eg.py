#_*_coding:UTF-8_*_

from  datetime  import  *  
import  time  
 


# datetime.datetime 
print   'datetime.max:' , datetime.max  
print   'datetime.min:' , datetime.min  
print   'datetime.resolution:' , datetime.resolution  
print   'today():' , datetime.today()  
print   'now():' , datetime.now()  
print   'utcnow():' , datetime.utcnow()  
print   'fromtimestamp(tmstmp):' , datetime.fromtimestamp(time.time())  
print   'utcfromtimestamp(tmstmp):' , datetime.utcfromtimestamp(time.time())

# # ---- ��� ----   
# (%Y-%m-%d %H:%M:%S %f):  2010-04-07 10:52:18 937000   
# (%Y-%m-%d %H:%M:%S %p):  10-04-07 10:52:18 AM   
# %a: Wed    
# %A: Wednesday    
# %b: Apr    
# %B: April    
# ����ʱ��%c: 04/07/10 10:52:18    
# ����%x��04/07/10    
# ʱ��%X��10:52:18    
# ���������ܵĵ�3��    
# �����ǽ���ĵ�097��    
# �����ǽ���ĵ�14��
dt = datetime.now()  
print   '(%Y-%m-%d %H:%M:%S %f): ' , dt.strftime( '%Y-%m-%d %H:%M:%S %f' )  
print   '(%Y-%m-%d %H:%M:%S %p): ' , dt.strftime( '%y-%m-%d %I:%M:%S %p' )  
print   '%%a: %s '  % dt.strftime( '%a' )  
print   '%%A: %s '  % dt.strftime( '%A' )  
print   '%%b: %s '  % dt.strftime( '%b' )  
print   '%%B: %s '  % dt.strftime( '%B' )  
print   '����ʱ��%%c: %s '  % dt.strftime( '%c' )  
print   '����%%x��%s '  % dt.strftime( '%x' )  
print   'ʱ��%%X��%s '  % dt.strftime( '%X' )  
print   '���������ܵĵ�%s�� '  % dt.strftime( '%w' )  
print   '�����ǽ���ĵ�%s�� '  % dt.strftime( '%j' )  
print   '�����ǽ���ĵ�%s�� '  % dt.strftime( '%U' )  











