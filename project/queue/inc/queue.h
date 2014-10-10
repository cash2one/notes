
typedef struct queue_node_tag
{
    int qn_key;
	void *qn_data;
}queue_node;


typedef struct queue_ctrl_tag
{
    char         q_name[32];
    unsigned int q_w_idx;
	unsigned int q_r_idx;
	unsigned int q_size;  /*���д�С*/
	unsigned int q_count; /*�����е����ݸ�������ʼΪ0д�Ӷ���*/
	queue_node   q_node[0];/*�㳤���飬qnode������ռ�ռ�*/
}queue_s;


/*����һ����СΪ@size�Ķ���,�ɹ����ض��п���ͷ,ʧ�ܷ���NULL*/
queue_s *queue_create(char *name,int size);
 
