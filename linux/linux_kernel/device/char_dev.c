/*
struct cdev һ�����ֽṹ��ʾһ���ַ��豸

chrdevs   �豸�Ź���
cdev_map  �ַ��豸����

�ȸ㵽�豸��       alloc_chrdev_region 
�Ѿ����˾�ֱ��ע�� register_chrdev_region
�����豸���ٳ�ʼ�� cdev_init
������           cdev_add


init_special_inode ע�� def_chr_fops chrdev_open
do_dentry_open -> fops_get

chrdev_open  ���ַ��豸��ͨ�ú���



