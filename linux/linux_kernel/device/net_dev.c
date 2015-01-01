
struct net_device  /*���������豸�Ľṹ,�洢�����豸��������Ϣ*/

alloc_netdev
netdev_priv  /* ��ȡ˽����������ָ��*/

/*******************************************************************************
@sizeof_priv:���������˽����������С
@name:����ӿڵ����ƣ��û��ռ�ɼ�
@setup:�ص���������ʼ��һЩ�ṹ���еı���

function:����һ��net_device���͵Ķ���������������������豸
*******************************************************************************/

struct net_device *alloc_netdev_mqs(int sizeof_priv, const char *name,
		unsigned char name_assign_type,
		void (*setup)(struct net_device *),
		unsigned int txqs, unsigned int rxqs);

/**
 *	free_netdev - free network device
 *	@dev: device
 *
 *	This function does the last stage of destroying an allocated device
 * 	interface. The reference to the device object is released.
 *	If this is the last reference then it will be freed.
 */
void free_netdev(struct net_device *dev);


#define alloc_etherdev /*���䲢��ʼ��һ����̫���豸*/





/*******************************************************************************
net_device�����������豸��һ���������ֻ�е��������ע�ᵽϵͳ�к��ں�������
ϵͳ���ͻ��߷���һ���������ݰ�ʱ�Ż���õ�net_device�����ṩ�ĺ��������Ե�����һ
���µ�net_device���󲢳�ʼ����Ҫ����ע�ᵽϵͳ�С�register_netdev ����������
���ܡ�

��һ��NIC�豸��ϵͳ�ɹ�ע������������뵽ϵͳ�������豸�б������ϵ�С����ں�
��������ϵͳ�߲�Ҫ����һ�����ݰ�ʱ��ͨ������·�ɱ�õ��ӿ���Ϣ(�����ҵ���eth0)
Ȼ���ٵ��豸�б��в��Ҷ�Ӧ���豸��
*******************************************************************************/
int register_netdev(struct net_device *dev);


void unregister_netdev(struct net_device *dev);



/*******************************************************************************
�����豸���������ṩ�����й��ܵļ��ϳ�֮Ϊ�豸����
�豸���������� net_device_ops �ṹ��

int (*ndo_init)(struct net_device *dev);
    This function is called once when network device is registered.The network 
    device can use this to any late stage initializaton or semantic validattion. 
    It can fail with an error code which will be propogated back to register_netdev

void (*ndo_uninit)(struct net_device *dev);
    This function is called when device is unregistered or when registration fails. 
    It is not called if init fails.

int (*ndo_open)(struct net_device *dev);
    This function is called when network device transistions to the up state.
    ���豸���ڵ�����ӿڱ�����ʱ������ʵ��ipconfig����ĳһ����ӿ�ʱ���ӿڽ����򿪡�
    ��ʱndo_open�������ã����������¹���:������շ����������ݰ�����Ҫ����Դ����ʼ
    ���豸��Ӳ���жϲ���ϵͳע���жϣ�����watchdog��ʱ����֪ͨ�ϲ�������ϵͳ��ǰ�ӿ�
    �Ѿ����ȡ�
    
int (*ndo_stop)(struct net_device *dev);
    This function is called when network device transistions to the down state.

netdev_tx_t (*ndo_start_xmit) (struct sk_buff *skb,struct net_device *dev);
    ͨ��DMA��@skb�е����ݿ����������豸�Ĵ洢�ռ��У�Ȼ���������豸��Ӳ���߼���
    ����豸�洢�ռ��е����ݷ��ͳ�ȥ���ɹ����豸����һ��Ӳ���ж�֪ͨ�����������
    ��Ӧ�Ĵ��������ͷ�@skb������������һЩͳ�Ƶȡ�
    dev_queue_xmit

*******************************************************************************/

struct net_device_ops
{
    int   (*ndo_init)(struct net_device *dev);
    void  (*ndo_uninit)(struct net_device *dev);
    netdev_tx_t (*ndo_start_xmit) (struct sk_buff *skb,struct net_device *dev);
};

/*******************************************************************************
��ʵ�е������豸����������Ҫ����ʵ�����������ε��� netif_stop_queue �� 
netif_start_queue������һ�����͵������:��һ�������豸�Ľӿ�ʱ�����ú����Ը���
�ںˣ�������ϵͳ�߲������Ե���dev_hard_start_xmit�������ݰ��ķ���;�������豸��
�ڱ��ر�ʱ����Ӧ����������Ӧ�õ���ǰ����֪ͨ�ϲ���롣

*******************************************************************************/



/**
 *	netif_stop_queue - stop transmitted packets
 *	@dev: network device
 *
 *	Stop upper layers calling the device hard_start_xmit routine.
 *	Used for flow control when transmit resources are unavailable.
 */
static inline void netif_stop_queue(struct net_device *dev);


/**
 *	netif_start_queue - allow transmit
 *	@dev: network device
 *
 *	Allow upper layers to call the device hard_start_xmit routine.
 */
static inline void netif_start_queue(struct net_device *dev);



/* ����������ж������Ƿ�æ */
int dev_hard_start_xmit(struct sk_buff *skb, struct net_device *dev,struct netdev_queue *txq);



/*
=================== �հ�����
1 �����豸�յ���������DMA�����ݿ�����CPU���ڴ��У�Ȼ���CPU�����жϡ�
2 CPU����Ԥ��ע����жϴ����������������ݰ���
3 �жϴ������з���һ���׽��ֻ�����skb����ȷ�����ݰ����豸�ڴ��д��䵽��skb��ָ��ϵͳ�ڴ档
4 Ȼ�����netif_rx(skb)��netif_rxֻ�ǽ��յ������ݰ�����һ�����ն����ϣ�Ȼ�󴥷�NET_RX_SOFTIRQ���жϡ�

����:
1 ���жϴ������� net_dev_init() ��ע�ᡣ
  open_softirq(NET_TX_SOFTIRQ, net_tx_action, NULL);
  open_softirq(NET_RX_SOFTIRQ, net_rx_action, NULL);
2 �����׽��ֻ�����skb�Ľӿ� dev_alloc_skb()


********************************************************************************
NAPI(new api)
napi������ж�����ѯ�ĸ������ơ��������ݰ�����ʱ�ᴥ��Ӳ���жϣ����жϴ����йر�
�жϣ�Ȼ�������ѯģʽ��ֱ�����е����ݰ�������ϣ������¿����жϣ�������һ���ж�
��ѯ���ڡ�

*/
