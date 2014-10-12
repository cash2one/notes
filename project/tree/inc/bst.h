#ifndef __BST_H__
#define __BST_H__

/*binary search tree*/

#define BST_NAMELEN 32 /*��������\0*/

/*����������ڵ�ṹ*/
typedef struct bstnode
{
	struct bstnode *bst_parent; /*���ڵ�*/
	struct bstnode *bst_left;   /*����*/
	struct bstnode *bst_right;  /*�Һ���*/
	int             bst_key;    /*�ڵ�keyֵ*/
}bstnode_t;

typedef struct bstctr
{
    char       bst_name[32];
	int        bst_nodenums;
	bstnode_t *bst_root;
}bst_ctrl;


#endif
