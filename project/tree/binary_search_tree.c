#include<stdio.h>
//#include<stddef.h>
#include "binary_search_tree.h"
#include "tree_stack.h"


tree_node_t *tree = &root;

/*������ȱ���������������������ζ�����(�������)���ö�����ʵ�ֵģ�
�Ӷ������ĵ�һ�㣨����㣩��ʼ������������������
��ͬһ���У����մ����ҵ�˳��Խ����һ���ʡ�
���մӸ������Ҷ��㡢�����������������Ĵ�����ʶ������Ľ�㡣
�㷨��
1��ʼ��һ�����У����Ѹ�������жӣ�
2������Ϊ�ǿ�ʱ��ѭ��ִ�в���3������5������ִ��6��
3������ȡ��һ����㣬���ʸý�㣻
4���ý���������Ϊ�ǿգ��򽫸ý�������������У�
5���ý���������Ϊ�ǿգ��򽫸ý�������������У�
6������*/
void tree_traverse_cengci_recursion(tree_node_t *root)
{
}

void tree_traverse_cengci_iterative(tree_node_t *root)
{
}


/*������ȱ���:����ǰ�����������������������*/
void tree_traverse_preorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
    	tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
		
        tree_traverse_preorder_recursion(root->left);
		tree_traverse_preorder_recursion(root->right);
    }
}

void tree_traverse_preorder_iterative(tree_node_t *root)
{
	tree_node_t *node = NULL;
	
	node = root;

	while(node!=NULL||!tree_stack_empty())
	{
		while(NULL != node)
		{
			tree_node_name_show(node);
			printf("key:%d	depth:%d  index: %d\r\n",node->key,node->depth,node->index);
			
			tree_stack_push(node);
			node = node->left;
		}

		if(!tree_stack_empty())
		{
			node = tree_stack_gettop();
			(void)tree_stack_pop();
			node = node->right;
		}
	}
}

void tree_traverse_inorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
        tree_traverse_inorder_recursion(root->left);
		
		tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
		
		tree_traverse_inorder_recursion(root->right);
    }
}

void tree_traverse_inorder_iterative(tree_node_t *root)
{
    tree_node_t *node = NULL;
	
	node = root;

    while(node!=NULL||!tree_stack_empty())
    {
	    while(NULL != node)
	    {
	        tree_stack_push(node);
			node = node->left;
	    }

		if(!tree_stack_empty())
		{
		    node = tree_stack_gettop();
			
			tree_node_name_show(node);
			printf("key:%d  depth:%d  index: %d\r\n",node->key,node->depth,node->index);
			
			(void)tree_stack_pop();
			node = node->right;
		}
    }
}


void tree_traverse_postorder_recursion(tree_node_t *root)
{  
    if(NULL != root)
    {
        tree_traverse_postorder_recursion(root->left);
		tree_traverse_postorder_recursion(root->right);

		tree_node_name_show(root);
		printf("key:%d  depth:%d  index: %d\r\n",root->key,root->depth,root->index);
    }
}

/*����������ա�����-�Һ���-����㡱��˳����з��ʡ�
  Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ���P���Ƚ�����ջ��
  ���P���������Ӻ��Һ��ӣ������ֱ�ӷ�����������P�������ӻ����Һ��ӣ�����
  �����Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣�����������������
  ��P���Һ��Ӻ�����������ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ����������
  ����ǰ�汻���ʣ����Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�*/
void tree_traverse_postorder_iterative(tree_node_t *root)
{
    tree_node_t *pre = NULL;
	tree_node_t *cur = NULL;

    if(NULL == root)
		return;
	
	(void)tree_stack_push(root);

	while(!tree_stack_empty())
	{
	    cur = tree_stack_gettop();

		if(((NULL == cur->right) && (NULL == cur->left)) || 
		   ((NULL != pre) && (pre==cur->right||pre==cur->left)))
		{
		    /*�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�*/
			tree_node_name_show(cur);
			printf("key:%d  depth:%d  index: %d\r\n",cur->key,cur->depth,cur->index);

			(void)tree_stack_pop();
			pre=cur; 
		}
		else
		{
		    if(cur->right!=NULL)
                tree_stack_push(cur->right);
            if(cur->left!=NULL)    
                tree_stack_push(cur->left);
		}
	}
}


tree_node_t *tree_search(tree_node_t *pnode, int key)
{
    if(NULL == pnode || key == pnode->key)
		return pnode;

	if(key < pnode->key)
		return tree_search(pnode->left,key);
	else
		return tree_search(pnode->right,key);
}
tree_node_t *tree_search_iterative (tree_node_t *pnode, int key)
{
    while(NULL != pnode && key != pnode->key)
    {
        if(key < pnode->key)
			pnode = pnode->left;
		else
			pnode = pnode->right;
    }

	return pnode;
}
tree_node_t *tree_min (tree_node_t *pnode)
{
    if(NULL == pnode){
		return NULL;
    }
	
    while(NULL != pnode->left){
        pnode = pnode->left;
    }

	return pnode;
}
tree_node_t *tree_max (tree_node_t *pnode)
{
    if(NULL == pnode){
		return NULL;
    }

    while(NULL != pnode->right){
        pnode = pnode->right;
    }

	return pnode;
}
tree_node_t *tree_successor (tree_node_t *pnode)
{
    tree_node_t *pparent;

    if(NULL != pnode->right)
		return tree_min(pnode->right);

	pparent = pnode->parent;

	while(NULL != pparent && pnode == pparent->right)
	{
	    pnode   = pparent;
		pparent = pparent->parent;
	}

	return pparent;
}
tree_node_t *tree_predecessor(tree_node_t *pnode)
{
    tree_node_t *pparent;

    if(NULL != pnode->left)
		return tree_max(pnode->left);

	pparent = pnode->parent;

	while(NULL != pparent && pnode == pparent->left)
	{
	    pnode   = pparent;
		pparent = pparent->parent;
	}

	return pparent;
}

void tree_insert(tree_node_t *proot,tree_node_t *pnode)
{
    tree_node_t *pfather = NULL;
	tree_node_t *ptree_node = proot;

	while(NULL != ptree_node)
	{
	    pfather = ptree_node;

		if(pnode->key < ptree_node->key)
			ptree_node = ptree_node->left;
		else
			ptree_node = ptree_node->right;
	}

	pnode->parent = pfather;

	if(NULL == pfather)
	{
		tree = pnode;/*��Ϊ�գ�node��Ϊ���ڵ�*/
	}
	else
	{
	    if(pnode->key < pfather->key)
			pfather->left = pnode;
		else
			pfather->right = pnode;
	}
}

tree_node_t *tree_delete(tree_node_t *proot,tree_node_t *pnode)
{    
	tree_node_t *pdel;      /*��ɾ���ڵ㣬���ܾ���pnode(pnode�����һ������)��Ҳ����ʹpnode�ĺ��(pnode����������)*/
	tree_node_t *pchild_del;/*��ɾ���ڵ���ӽڵ�*/

    /*ȷ����ɾ���Ľڵ㣬pnode����pnode�ĺ��*/
    if(NULL == pnode->left || NULL == pnode->right)
		pdel = pnode;
	else
		pdel = tree_successor(pnode);

	/*pdel�����һ����Ů���ҵ���NULL��Ů��û����Ůpchild_delΪ��*/
	if(NULL != pdel->left)
		pchild_del = pdel->left;
	else
		pchild_del = pdel->right;

	if(NULL != pchild_del)
		pchild_del->parent = pdel->parent;

	if(NULL == pdel->parent)
	{
        tree = pchild_del;
	}
	else
	{
		if(pdel == pdel->parent->left)
			pdel->parent->left = pchild_del;
		else
			pdel->parent->right = pchild_del;
	}

	if(pnode != pdel)
		pnode->key = pdel->key;

	return pdel;/*����ʵ����ɾ���Ľڵ�*/	
}
