/*******************************************************************************
 RFC793ָ����ʼ���кſ��Կ�����һ��32bit�ļ�������ÿ4ms��1��ѡ�����кŵ�Ŀ������
 ��ֹ�������б��ӳٵķ������Ժ��ظ����䣬������ĳ�����ӵ�һ�˶�����������жϡ�
 ******************************************************************************/

/*******************************************************************************
                   Establishing A TCP Connection
 *******************************************************************************
 ����A������B����TCP����(����ͬʱ�������ӣ�������˵����򵥵����:A����B����)
 1 ����A���� tcp_open_1 ��������
 2 B�յ�SYN�󣬵��� tcp_open_2 ��ӦA
 3 A�յ�B�Ļ�Ӧ�󣬵��� tcp_open_3 ��ӦB�����ӽ�����

 �������ֵ�Ŀ��
 1 �ֱ���߶Է��Լ���"��ʼ���к�"
 *******************************************************************************/

/*******************************************************************************
 ������������:
 �ͻ���A�������ӣ��������Ӻ���"a",����������"recv"��Ȼ��ͻ��˹ر����ӣ�����
 ����Ҳ�ر�����
 ******************************************************************************/

/* A send SYN  SYNռ��1�����к�*/
int tcp_open_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 0;   /*���Լ��ĳ�ʼ���кŸ��߶Է���������0*/ 
	sendhdr->ack_seq = 0;   /*һ��ָ��Ϊ0����δ������ֵû����;*/
	sendhdr->syn     = 1;
	sendhdr->window  = 65535;
}


/* B send SYN+ACK  ACK��ռ�����к�*/
int tcp_open_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 0;     /*initial sequence number һ�����������*/  
	sendhdr->ack_seq = recvhdr->seq + 1; /*0+1�����߶Է������´���������1*/
	sendhdr->syn     = 1;	
	sendhdr->ack     = 1;	
	sendhdr->window  = 8192;/*��������������ڴ�С*/
}


/* A send ACK */
int tcp_open_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = recvhdr->seq + 1;/*0+1�����߶Է������´���������1*/
	sendhdr->ack     = 1;
	sendhdr->window  = 212992;/*��������������ڴ�С*/

}


/* A �ͻ���A������������ַ�"a"*/
int tcp_send1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = 1;
	sendhdr->ack     = 1;
	sendhdr->psh     = 1;
	sendhdr->window  = 212992;/*��������������ڴ�С*/

	/*data len :2*/
}


/* B ���������յ�"a"�󣬻���"recv"���ͻ���*/
int tcp_send2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = recvhdr->seq + 2;/*1+2==3*/
	sendhdr->ack     = 1;
	sendhdr->psh     = 1;
	sendhdr->window  = 65531;/*��������������ڴ�С*/
	/*data len :5*/	
}


/* A ���յ�������������"recv"����Ӧack*/
int tcp_send3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 3;
	sendhdr->ack_seq = recvhdr->seq + 4;/*1+5==6*/
	sendhdr->ack     = 1;
	sendhdr->window  = 212988;/*��������������ڴ�С*/
	/*data len :0*/	
}


/*******************************************************************************
 A �ͻ���A���ȹر�tcp���� ����fin
 �ͻ���A����������ݷ�������󣬻������������һ����ֹ���ݰ����Թر������������
 ��TCP���ӡ������ݰ��У����к�Ϊ���������͵���һ�����ݰ��е�ȷ�Ϻ�ֵ����ȷ�Ϻ�Ϊ
 ���������յ���һ�����ݰ��е����к�+�����ݰ����������ݵĴ�С��
 
 FIN��SYNһ����ҲҪռһ����š������Ϸ�������TCP���ӹر�ʱ���͵���ֹ���ݰ��У�
 ֻ����ֹλ����1��Ȼ��ͻ��˽���ȷ�ϡ�������ʵ�ʵ� TCPʵ���У�����ֹ���ݰ��У�
 ȷ��λ����ֹλ��ͬʱ��Ϊ1�ģ�ȷ��λ��Ϊ1��ʾ�����һ�δ�������ݽ���ȷ�ϣ���ֹ
 λ��Ϊ1��ʾ�رո÷����TCP���ӡ�

 ******************************************************************************/
int tcp_close_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 3;
	sendhdr->ack_seq = 6;	
	sendhdr->ack     = 1;
	sendhdr->fin     = 1;
	sendhdr->window  = 212988;/*��������������ڴ�С*/
}


/******************************************************************************* 
 B ������B��Ӧack 
 �������յ��ͻ��˷��͵���ֹ���ݰ��󣬽��Կͻ��˷���ȷ����Ϣ���Թرո÷����ϵ�TCP
 ���ӡ���ʱ�����ݰ��У����к�Ϊ��1���е�ȷ�Ϻ�ֵ����ȷ�Ϻ�Ϊ��1�������ݰ��е���
 �к�+1��
 ******************************************************************************/
int tcp_close_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
    sendhdr->seq     = 6;
	sendhdr->ack_seq = 3 + 1;/*1��ʾ�յ�fin*/
	sendhdr->ack     = 1;	
	sendhdr->window  = 65533;/*��������������ڴ�С*/
}


/*******************************************************************************
 �ͻ��˵������������ӹر��ˣ����Ƿ��������Լ������ͻ��˷������ݡ����ͽ������ٷ�
 ��fin�ر����ӣ��������з�����ֱ�ӹر���һ������

 B ������B����fin
 ����������������ݷ��������Ҳ����ͻ��˷���һ����ֹ���ݰ����Թر����������
 �ϵ�TCP���ӣ������ݰ��У����к�Ϊ�ͻ��˷��͵���һ�����ݰ��е�ȷ�Ϻ�ֵ����ȷ�Ϻ�
 Ϊ���������͵���һ�����ݰ��е����к�+�����ݰ��������ݵĴ�С��
******************************************************************************/
int tcp_close_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
	sendhdr->seq	 = 6;/*tcp_ack_send�е�acknum*/
	sendhdr->ack_seq = 4;/*ĿǰΪֹ�յ�:syn(1) "a"(2) fin(1)*/
	sendhdr->ack	 = 1;	
	sendhdr->fin     = 1;
	sendhdr->window  = 65533;/*��������������ڴ�С*/
}


/*******************************************************************************
 A �ͻ���A��Ӧack
 �ͻ����յ����������͵���ֹ���ݰ��󣬽��Է���������ȷ����Ϣ���Թرո÷����ϵ�TCP
 ���ӡ���ʱ�����ݰ��У����к�Ϊ��3���е�ȷ�Ϻ�ֵ����ȷ�Ϻ�Ϊ��3�����ݰ��е����к�+1��
 ******************************************************************************/
int tcp_close_4(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
	sendhdr->seq	 = 4;/*A������:syn(1) ack(0) "a"(2) fin(1)*/
	sendhdr->ack_seq = 7;/*A�յ���:ack(0)+syn(1) "recv"(5) fin(1) */
	sendhdr->ack	 = 1;	
	sendhdr->window  = 212988;/*��������������ڴ�С*/
}
