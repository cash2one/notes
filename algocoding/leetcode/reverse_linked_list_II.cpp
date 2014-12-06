/*******************************************************************************
                           reverse_linked_list_II 
********************************************************************************
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m =<= n <= length of list.
********************************************************************************
                    Definition for singly-linked list.
********************************************************************************
struct ListNode 
{
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        
    }
};
********************************************************************************
                            algo
********************************************************************************
header->1->2->3->4->5->NULL
Ϊ�˷�ת�����������������ͷ����next��ָ����2�����ý��1��next��ָ����3��
��󽫽��2��next��ָ����1��������˵�һ�ν�����˳��ͱ����
        Header-���2-���1-���3-���4-NULL��
Ȼ�������ͬ�Ľ��������3�ƶ������2��ǰ�棬Ȼ���ٽ����4�ƶ������3��ǰ������
�˷�ת

����Ľ���:����һ���������ֵ�վ��һ�ţ���һ�Ƕӳ�
�ϴ����һ˵: ��һ�������һ���ֵ��Ŷ�����������ס�Ŷ�����һ���ֵ�
�ϴ���Ŷ�˵: �Ŷ���������С�ӳ��ˣ���ס��һ����
�ϴ����һ˵: �ٰ������һ���ֵ���������������ס��������һ���ֶ�
�ϴ������˵: ������������С�ӳ��ˣ���ס��һ����
...
*******************************************************************************/

struct ListNode 
{
	  int val;
	  ListNode *next;
	  ListNode(int x) : val(x), next(NULL) {}
};


// LeetCode, Reverse Linked List II
//  time O(n), mem O(1)
class Solution {
public:
ListNode *reverseBetween(ListNode *head, int m, int n) 
{
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy;
	
    for (int i = 0; i < m-1; ++i)
        prev = prev->next; 
	
    ListNode* const head2 = prev;
    prev = head2->next;
    ListNode *cur = prev->next;

/* ��ʱ
   head2 ָ�� m ��ǰһ���ڵ㣬�˺�head2һֱ���䣬���ڵ�λ�û��
   prev  ָ�� m �ڵ�
   cur   ָ�� m ����һ���ڵ�
*/
    for (int i = m; i < n; ++i) 
	{
        prev->next = cur->next;
        cur->next = head2->next;
        head2->next = cur; 
        cur = prev->next;
    }
	
    return dummy.next;
}

ListNode *reverseBetween2(ListNode *head, int m, int n)
{
	int i;
	ListNode  lhead(-1);
	ListNode *rhead = NULL;
	ListNode *cur	= NULL;
	ListNode *pre	= NULL;

	if(NULL == head)
	{
		return NULL;
	}
	
	lhead.next = head;
	pre = &lhead;
	
	for(i = 0; i < m-1; ++i)
	{
		pre = pre->next;
	}

	rhead = pre;	 /* rhead ָ�� m ��ǰһ���ڵ�(�п�����lhead) */
	pre = pre->next; /* pre   ָ�� m �ڵ�(��Ϊ��)*/
	cur = pre->next; /* cur   ָ�� m ����һ���ڵ� */

	for(i = m; i < n; ++i)
	{
		if(NULL == cur)
			break;
		
		pre->next = cur->next;
		cur->next = rhead->next;
		rhead->next = cur;
		cur = pre->next;
	}

	return lhead.next;
}



};


