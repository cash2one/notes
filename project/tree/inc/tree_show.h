#ifndef __TREE_SHOW_H__
#define __TREE_SHOW_H__


/*��ʾ���Ľڵ�,���ĸ߶������6,�ڵ��keyֵ�������λ��.��ʾ����ʽ����ͼ��ʾ:

                                |------------------------------20------------------------------|
                                |                                                              |
                |--------------15--------------|                                |--------------30--------------|
                |                              |                                |                              |
        |------14------|                |------16------|                |------25------|                |------40------| */
int tree_show(tree_node_t *pnode,int depth);












#endif



/*

                                |------------------------------NN------------------------------|
                                |                                                              |
                |--------------NN--------------|                                |--------------NN--------------|
                |                              |                                |                              |
        |------NN------|                |------NN------|                |------NN------|                |------NN------|
        |              |                |              |                |              |                |              |
    |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|
    |      |        |      |        |      |        |      |        |      |        |      |        |      |        |      |
   NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN
  |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |
 NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN
 ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

                                                               64
                               32                                                              96
               16                              48                              80                              112
*/

