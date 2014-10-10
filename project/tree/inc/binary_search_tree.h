/********************************************************************

                         ���������
 1 �������Ĺؼ��� <= ���ڵ�Ĺؼ��֣��������Ĺؼ��� >= ���ڵ�Ĺؼ���
 2 �������(�������)��key��С�������
 3 �涨ÿ���ڵ㶼�����Լ�������
 
 ********************************************************************/
 
typedef struct tree_node_struct
{
	struct tree_node_struct *parent;
	struct tree_node_struct *left;
	struct tree_node_struct *right;
		 
	int key;
	 
	int depth;/*�ڵ�߶ȣ����ڵ���0*/
	int index;/*�ڵ��ڱ�������� ��һ����0 �ڶ�����1*/
}tree_node_t;

extern tree_node_t node01;
extern tree_node_t node02;
extern tree_node_t node03;
extern tree_node_t node04;
extern tree_node_t node05;
extern tree_node_t node06;
extern tree_node_t node07;
extern tree_node_t node08;
extern tree_node_t node09;
extern tree_node_t node10;
extern tree_node_t root;
extern tree_node_t *tree;

/*����Ľڵ�*/
extern tree_node_t *tree_min (tree_node_t *pnode);


/*���ҵĽڵ�*/
extern tree_node_t *tree_max (tree_node_t *pnode);


/*��������ĺ�̽ڵ�:�������������������������Ǹ��ڵ㡣��ǰ�ڵ���@pnode
  1 p�������ǿգ����Ϊ��������������ڵ�(keyֵ��С)
  2 p������Ϊ�գ���Ѱ���丸�ڵ㡣���p���丸�ڵ���Һ��ӣ���ô�丸�ڵ��Ѿ�������ˡ�
    �Ը��ڵ�Ϊ��ǰ�ڵ����Ѱ����ֱ���ҵ�һ���ڵ㣬����ڵ����丸�ڵ�����ӡ�
    ��������Ҳû���ҵ������Ľڵ㣬��ôp�����������һ������ڵ㣬û�к��*/
extern tree_node_t *tree_successor (tree_node_t *pnode);


/*�ҽڵ�node��ǰ��
  ����ǰ��:���������������ڽڵ�nodeǰ������Ǹ��ڵ㡣 
  ���Ӳ�Ϊ��:ǰ����node�����������ڵ�
  ����Ϊ��  :ǰ����node���ȣ���������ȵ��Һ���Ҳ��node������
               ��node���ڵ㣬���������ڵ���ͨ�������ҵ��ģ����������Ѱ��*/
extern tree_node_t *tree_predecessor(tree_node_t *pnode);

/*���� �ݹ�汾*/
extern tree_node_t *tree_search(tree_node_t *pnode, int key);

/*���� �����汾*/
extern tree_node_t *tree_search_iterative (tree_node_t *pnode, int key);

/*����������������*/
extern void tree_traverse_inorder_recursion(tree_node_t *root);


/**********************************************************************
          ��������:�ѽڵ�pnode���뵽���У����ĸ��ڵ���proot
 ----------------------------------------------------------------------
 1 ����key�Ĵ�С�ҵ�һ��ΪNULL��λ�ã�����ط�����pnodeҪ����ĵط���
 2 ���prootΪ�գ�pnode����Ϊ������ĸ��ڵ�
 **********************************************************************/
extern void tree_insert(tree_node_t *proot,tree_node_t *pnode);


/**********************************************************************
		   ��������:�ѽڵ�pnode������ɾ�������ĸ��ڵ���proot
  ---------------------------------------------------------------------
  node����Ů    :ֱ��ɾ����Ҫ�ж�node���丸�ڵ�����ӻ����Һ��ӣ�Ȼ��Ѹ��ڵ�����ӻ��Һ�����NULL
  node��һ����Ů:ֱ��ɾ����Ҫ�ж�node���丸�ڵ�����ӻ����Һ��ӣ�Ȼ��Ѹ��ڵ�����ӻ��Һ�����Ϊnode�ڵ�Ĳ�Ϊ�յĺ���
  node��������Ů:ɾ��node�ĺ��(û������Ů)��Ȼ���node��keyֵ��Ϊ���̵�keyֵ.�Լ�ɾ������˭����Լ�?��Ȼ�Ǻ���ˡ�

  1 ����pnode�ҵ�����Ҫɾ���Ľڵ�pdel,���ܾ���pnode��Ҳ����ʹpnode�ĺ��
  2 pchild_del��Ϊpdel�ķǿ��ӽڵ㣬�Ҳ������ÿ�
  3 pchild_del�ǿվ͸�pchild_del�Ҹ����ף����������û�и��ף�˵�����Ǹ��ڵ㰡���ð�������޵����ڵ�ɡ�
  4 ɾ��pdel�������ж�pdel���丸�׵����ӻ����Һ��ӣ������ӾͰ��Լ��ĺ���pchild_del��Ϊ�Լ����׵����ӡ�
  5 ����������pdel�������pnode��˵��pnode���������ӣ���pnode��keyֵ��Ϊ���̵�keyֵ
  ***********************************************************************/
extern tree_node_t *tree_delete(tree_node_t *proot,tree_node_t *pnode);
