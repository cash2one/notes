/*
bfs:breadth first search ����������� 
1 �������·��
 for any vertex v reachable from s,BFS computes a shortest path from s to v



color[u] ������ɫ ������ white gray black 
white ��ɫ��ʾ��δ����
gray vertices, which are discovered vertices that have not yet had their adjacency 
lists fully examined. 
black ��ɫ��ʾ

�Ӷ���S��ʼ��ͼG������
BFS(G, s) 
{
	for each vertex uin G
	{
	    color[u] = WHITE 
	    d[u] = ��
	    p[u] = NIL
	}
	
	color[s] = GRAY 
	d[s] = 0 
	p[s] = NIL 
	    
	Q = NULL (��)
	ENQUEUE(Q, s)

	while Q �� NULL
	{
	    u = DEQUEUE(Q)
	    
	    for each vin Adj[u] 
	    {
	        if color[v] == WHITE
	        {
	            color[v] = GRAY 
	            d[v] = d[u] + 1 
	            p[v] = u
	            ENQUEUE(Q, v) 
	         }       
	    }
	    color[u] = BLACK 
	}
}



*/



