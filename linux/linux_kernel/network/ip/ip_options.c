
/*******************************************************************************
 @opt:When transmitting a locally generated packet, opt is not NULL and opt->data 
 contains a pointer to an IP header.
 @skb:when processing an ingress packet, the header is contained in the skb input 
 buffer and opt is NULL.In this second case, the ip_options structure is stored in 
 skb->cb(�����Ľ���ͷ�������)
 fun:����ip����ͷ��ѡ��
 ******************************************************************************/
int ip_options_compile(struct ip_options * opt, struct sk_buff * skb);


