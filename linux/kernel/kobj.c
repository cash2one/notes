kobject
kset
	
/*�趨kobject��name��Ա*/
int kobject_set_name(struct kobject *kobj, const char *fmt, ...)

/*��ʼ��һ���ں˶����kobject�ṹ*/
void kobject_init(struct kobject *kobj, struct kobj_type *ktype)

/*
  1 ����kobject�����Ĳ�ι�ϵ
  2 ��sysfs�ļ�ϵͳ�н���һ��Ŀ¼*/
int kobject_add(struct kobject *kobj, struct kobject *parent,const char *fmt, ...)

int kobject_init_and_add(struct kobject *kobj, struct kobj_type *ktype,struct kobject *parent, const char *fmt, ...)

/*���䲢��ʼ��һ��kobject*/
struct kobject *kobject_create(void)

struct kobject *kobject_create_and_add(const char *name, struct kobject *parent)

/*��sysfs�ļ����а�kobj��Ӧ��Ŀ¼ɾ��,���kobj����ĳһkset�Ļ�,�����kset��������ɾ��*/
void kobject_del(struct kobject *kobj)


/*Ϊһ��kobject���󴴽�һ�������ļ�(kobj->sd��Ӧ��Ŀ¼������һ�������ļ�)
  �û��ռ�ʹ����������ļ�ʱ,ͨ��open�򿪣����ջ����sysfs_open_file*/
sysfs_create_file
sysfs_remove_file






kset_init
kset_register
kset_create_and_add



kobject_uevent


bus_type  /*����*/
bus_attribute  /*��������*/


buses_init
bus_register
bus_create_file



struct device /*�豸*/
struct kset *devices_kset;/*����device�����ں˶��������*/

devices_init
device_initialize
device_register



struct device_driver /*����*/


struct class   /*�豸��*/


