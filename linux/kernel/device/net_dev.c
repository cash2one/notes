
struct net_device  /*���������豸�Ľṹ,�洢�����豸��������Ϣ*/



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






*/
