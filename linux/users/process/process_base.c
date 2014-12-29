/*
---->���̱�ʶ��
ÿ�����̶���һ���Ǹ�������ʾ��Ψһ����ID��
����IDΪ0�Ľ���:���Ƚ���Ҳ����Ϊ��������(swapper)
����IDΪ1�Ľ���:init����
����IDΪ2�Ľ���:Ҳ�ػ�����(pagedaemon)��

---->�����˳�
�����������쳣��ֹʱ���ں˾����丸���̷���SIGCHLD�ź�(�첽�źţ�Ĭ�Ϻ���)��

---->��������(race conditions) 
a race condition occurs when multiple processes are trying to do something with 
shared data and the final outcome depends on the order in which the processes run. 

----> ����״̬
zombie
    The purpose of the zombie state is to maintain information about the child 
    for the parent to fetch at some later time. This information includes the 
    process ID of the child, its termination status, and information on the 
    resource utilization of the child (CPU time, memory, etc.). If a process 
    terminates, and that process has children in the zombie state, the parent 
    process ID of all the zombie children is set to 1 (the init process), which 
    will inherit the children and clean them up (i.e., init will wait for them, 
    which removes the zombie). Some Unix systems show the COMMAND column for a 
    zombie process as <defunct>.

    Obviously we do not want to leave zombies around. They take up space in the 
    kernel and eventually we can run out of processes. Whenever we fork children, 
    we must wait for them to prevent them from becoming zombies.


----> ����(zombie)���� �¶�����
unix�ṩ��һ�ֻ��ƿ��Ա�ֻ֤Ҫ��������֪���ӽ��̽���ʱ��״̬��Ϣ�� �Ϳ��Եõ���
���ֻ��ƾ���: ��ÿ�������˳���ʱ��,�ں��ͷŸý������е���Դ,�����򿪵��ļ�,ռ
�õ��ڴ�ȡ� ������ȻΪ�䱣��һ������Ϣ(�������̺�the process ID,�˳�״̬the 
termination status of the process,����ʱ��the amount of CPU time taken by the 
process��)��ֱ��������ͨ��wait / waitpid��ȡʱ���ͷš�

�¶����̣�һ���������˳���������һ�������ӽ��̻������У���ô��Щ�ӽ��̽���Ϊ
�¶����̡��¶����̽���init����(���̺�Ϊ1)������������init���̶��������״̬�ռ�
������

��ʬ���̣�һ������ʹ��fork�����ӽ��̣�����ӽ����˳����������̲�û�е���wait��
waitpid��ȡ�ӽ��̵�״̬��Ϣ����ô�ӽ��̵Ľ�����������Ȼ������ϵͳ�С����ֽ��̳�
֮Ϊ�������̡�


----> ������:
���������һЩ���̵����,���Ǳ˴�֮����ߴ��ڸ��ӡ��ֵܹ�ϵ�������ڹ��������������ϵ��
���̱ض�����һ�������飬Ҳֻ������һ�������顣 һ���������п��԰���������̡� ��������������ڴӱ�������ʼ�����������н�����ֹ���뿪���顣
----> �����������:
���������Ϊ�˷���Խ��̽��й�������Ҫ���һ��������Ҫͬʱ����100�����̡�
���û�����ĳ��ԭ��Ҫ��ֹ�������ʱ��Ҫ��û�н����飬����Ҫ�ֶ���һ����ȥɱ����100�����̣�
���ұ���Ҫ�ϸ��ս��̼丸���ֵܹ�ϵ˳�򣬷�������ҽ����������˽����飬
�Ϳ��Խ���100����������Ϊһ�������飬���ǹ���1����ţ�pgrp����
������ѡȡһ��������Ϊ�鳤��ͨ���ǡ����֡���ߵ��Ǹ���ͨ���ý��̵�IDҲ����Ϊ�������ID����
���ھͿ���ͨ��ɱ�����������飬���ر���100�����̣��������ϸ�����ġ�
----> �鳤����
�鳤���̱�ʶ: �������ID==�����ID
�鳤���̿��Դ���һ�������飬�����ý������еĽ��̣�Ȼ����ֹ
ֻҪ����������һ�����̴��ڣ�������ʹ��ڣ����鳤�����Ƿ���ֹ�޹�
������������: �����鴴�������һ�������뿪(��ֹ��ת�Ƶ���һ��������)
----> �Ự:
һ������������ļ���,��ʼ���û���¼,��ֹ���û��˳�.
����Linux�Ƕ��û�������ķ�ʱϵͳ�����Ա���Ҫ֧�ֶ���û�ͬʱʹ��һ������ϵͳ��
��һ���û���¼һ��ϵͳ���γ�һ�λỰ��ÿ���Ự����һ���Ự���죨leader�����������Ự�Ľ��̡�
һ���Ự�ɰ�����������飬��ֻ����һ��ǰ̨�����顣



