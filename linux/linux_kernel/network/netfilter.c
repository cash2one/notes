
NF_HOOK(
  uint8_t pf,                   /*Э��������Netfilter�ܹ�ͬ����������IP��֮�⣬����������������������PF_INET6��PF_DECnet������*/
  unsigned int hook,            /*HOOK������֣�����IP�㣬����ȡ��������ֵ*/
  struct sk_buff *skb,          /**/
  struct net_device *in,        /*���ݰ��������豸����struct net_device�ṹ��ʾ*/
  struct net_device *out,       /*���ݰ���ȥ���豸����struct net_device�ṹ��ʾ*/
  int (*okfn)(struct sk_buff *))/*����ָ�룬�����еĸ�HOOK������еǼǺ����������ת���ߴ�����*/

NF_HOOK_THRESH(
uint8_t pf, 
unsigned int hook, 
struct sk_buff *skb,
struct net_device *in, 
struct net_device *out,
int (*okfn)(struct sk_buff *), 
int thresh)/*ָ��ͨ���ú�ȥ�������Ӻ���ʱ�����ȼ�*/


nf_hooks


/*���ص�*/
nf_inet_hooks
nf_hook_ops
nf_hookfn


ip_rcv
ip_forward
ip_output
ip_local_deliver
ip_push_pending_frames


/*��������ϵͳiptable_filter*/
struct xt_af
struct xt_table  /*�������һЩͨ�õĻ�����Ϣ��������ƣ�������Э��أ���Ӱ���hook��ȵ�*/
struct xt_table_info /*���й����һЩ������Ϣ��ͬʱ�ڸýṹ��ĩβָʾ�˸ñ������й������ڵ㣬�����еĵ�һ������*/
struct ipt_replace
struct ebt_replace_kernel

initial_table

xt_init
iptable_filter_init

iptable_filter_net_init
  ipt_register_table

	




