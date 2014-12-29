#include <iostream>
#include <fstream>
using namespace std;

#if 0
const int max_n = 100;//����֧�ֵ��������
const int max_people = 10000;//����֧�ֵ��������

int n;//�����
int peopleTotal;//���������ڽ��ӵ�����
int peopleNeed[max_n];//ÿ�������Ҫ������
int gold[max_n];//ÿ������ܹ��ڳ����Ľ�����
int maxGold[max_people][max_n];//maxGold[i][j]������i������ǰj������ܹ��õ�����������������-1ʱ��ʾδ֪

//��ʼ������ 
void init()
{
    ifstream inputFile("beibao.in");
    inputFile>>peopleTotal>>n;
    for(int i=0; i<n; i++)
        inputFile>>peopleNeed[i]>>gold[i];
    inputFile.close();
            
    for(int i=0; i<=peopleTotal; i++)
        for(int j=0; j<n; j++)
            maxGold[i][j] = -1;//����-1ʱ��ʾδ֪ [��Ӧ��̬�滮�еġ�������¼��]
        
}

//����ڽ���people���˺�ǰmineNum�����ʱ�ܹ��õ�������������ע�⡰ǰ���ٸ���Ҳ�Ǵ�0��ʼ��ŵ�
int GetMaxGold(int people, int mineNum)
{
    //�������ص���������
    int retMaxGold;

    //�������������������  [��Ӧ��̬�滮�еġ�������¼��]
    if(maxGold[people][mineNum] != -1)
    {
        //��ñ���������ֵ
        retMaxGold = maxGold[people][mineNum];
    }
    else if(mineNum == 0)//�������һ�����ʱ [��Ӧ��̬�滮�еġ��߽硱]
    {
        //�������������㹻�����������
        if(people >= peopleNeed[mineNum])
        {    
            //�õ������ֵ�����������Ľ�����
            retMaxGold = gold[mineNum];
        }
        else//������Ψһ��һ�����Ҳ���ܿ���
        {
            //�õ������ֵΪ0������
            retMaxGold = 0;
        }
    }
    else if(people >= peopleNeed[mineNum])//����������˹������������ [��Ӧ��̬�滮�еġ������ӽṹ��]
    {
        //���ǿ����벻�������������ȡ���ֵ
        retMaxGold = max(GetMaxGold(people - peopleNeed[mineNum],mineNum -1) + gold[mineNum],
                                        GetMaxGold(people,mineNum - 1));
    }
    else//����������˲�������������� [��Ӧ��̬�滮�еġ������ӽṹ��]
    {
        //�����ǲ����ɵ����
        retMaxGold  = GetMaxGold(people,mineNum - 1);
    }
    
    //������¼    
    maxGold[people][mineNum] = retMaxGold;
    return retMaxGold;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //��ʼ������
    init();
    //�������peopleTotal���˺�n������ܹ���õ������������ٴ����ѱ�Ŵ�0��ʼ���������һ�������Ϊn-1
    cout<<GetMaxGold(peopleTotal,n-1);
    system("pause");
    return 0;
}
#endif

#define MINE_MAX 100  /* ���������� */
#define PEOP_MAX 1000 /* �˵������� */

int golds[MINE_MAX]; /* ÿ�����Ľ����� */
int needs[MINE_MAX]; /* ������������������� */
int record[PEOP_MAX][MINE_MAX];/* ������i������ǰj������ܹ��õ�����������������-1ʱ��ʾδ֪ */

int get_max_gold(int peoples,int mines)
{
    int max_gold;
	int sub_a;
	int sub_b;

    if(0 == mines)
    {
        if(peoples >= needs[mines])
        {    
            max_gold = golds[mines];
        }
        else
        {
            max_gold = 0;
        }

		return max_gold;
    }

    /* ��������㹻����������ѡ�񣬲���ֻ��һ��ѡ�� */
    if(peoples >= needs[mines])
    {
        sub_a = get_max_gold(peoples - needs[mines],mines -1) + golds[mines];
	    sub_b = get_max_gold(peoples,mines - 1);
	    max_gold = max(sub_a,sub_b);
    }
	else
	{
	    max_gold = get_max_gold(peoples,mines-1);
	}
    
    return max_gold;
}

/* �ⷨ2: ������¼ */
int get_max_gold2(int peoples,int mines)
{
    int max_gold;
	int sub_a;
	int sub_b;

    if(record[peoples][mines] != -1)
    {
        max_gold = record[peoples][mines];
		return max_gold;		
    }

    if(0 == mines)
    {
        if(peoples >= needs[mines])
        {    
            max_gold = golds[mines];
        }
        else
        {
            max_gold = 0;
        }

		return max_gold;
    }

    /* ��������㹻����������ѡ�񣬲���ֻ��һ��ѡ�� */
    if(peoples >= needs[mines])
    {
        sub_a = get_max_gold(peoples - needs[mines],mines -1) + golds[mines];
	    sub_b = get_max_gold(peoples,mines - 1);
	    max_gold = max(sub_a,sub_b);
    }
	else
	{
	    max_gold = get_max_gold(peoples,mines-1);
	}
	        
    record[peoples][mines] = max_gold;  /* ������¼ */
	
    return max_gold;
}


/******************************************************************************/
void max_gold_test_result(char *place,int expect,int result)
{    	
	if(expect == result)
		cout << place << " : " << "pass " << expect << "/" << result << endl;
	else
		cout << place << " : " << "fail " << expect << "/" << result << endl;
}

void max_gold_test_init()
{
    for(int i=0; i<=PEOP_MAX; i++)
        for(int j=0; j<MINE_MAX; j++)
            record[i][j] = -1;
}

/* 100������5����� ��:133 */
void max_gold_test_01()
{
    max_gold_test_init();
	
    golds[0] = 92;golds[1] = 22;golds[2] = 87;golds[3] = 46;golds[4] = 90;
	needs[0] = 77;needs[1] = 22;needs[2] = 29;needs[3] = 50;needs[4] = 99;

	max_gold_test_result((char *)"max gold test 01-1",133,get_max_gold(100,5));
	max_gold_test_result((char *)"max gold test 01-2",133,get_max_gold2(100,5));	
}

/* 200������8����� ��:334 */
void max_gold_test_02()
{
    max_gold_test_init();

    golds[0] = 83;golds[1] = 14;golds[2] = 54;golds[3] = 79;
	golds[4] = 72;golds[5] = 52;golds[6] = 48;golds[7] = 62;
	
    needs[0] = 79;needs[1] = 58;needs[2] = 86;needs[3] = 11;
	needs[4] = 28;needs[5] = 62;needs[6] = 15;needs[7] = 68;

	max_gold_test_result((char *)"max gold test 02-1",334,get_max_gold(200,8));
	max_gold_test_result((char *)"max gold test 02-2",334,get_max_gold2(200,8));
	
}

/* 300������10����� ��:388 */
void max_gold_test_03()
{
    max_gold_test_init();

    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
	
    needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;

	max_gold_test_result((char *)"max gold test 03-1",388,get_max_gold(300,10));
	max_gold_test_result((char *)"max gold test 03-2",388,get_max_gold2(300,10));

}

/*
1000 100
71 26
34 59
82 30
23 19
1 66
88 85
12 94
57 8
10 3
68 44
5 5
33 1
37 41
69 82
98 76
24 1
26 12
83 81
16 73
26 32
18 74
43 54
52 62
71 41
22 19
65 10
68 65
8 53
40 56
40 53
24 70
72 66
16 58
34 22
10 72
19 33
28 96
13 88
34 68
98 45
29 44
31 61
79 78
33 78
60 6
74 66
44 11
56 59
54 83
17 48
63 52
83 7
100 51
54 37
10 89
5 72
79 23
42 52
65 55
93 44
52 57
64 45
85 11
68 90
54 31
62 38
29 48
40 75
35 56
90 64
47 73
77 66
87 35
75 50
39 16
18 51
38 33
25 58
61 85
13 77
36 71
53 87
46 69
28 52
44 10
34 13
39 39
69 75
42 38
97 13
34 90
83 35
8 83
74 93
38 61
74 62
22 95
40 73
7 26
94 85

*/

/* 1000������100����� ��:2614 */
void max_gold_test_04()
{
    max_gold_test_init();

    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[10] = 89;golds[11] = 59;golds[12] = 19;golds[13] = 43;golds[14] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;
    golds[0] = 89;golds[1] = 59;golds[2] = 19;golds[3] = 43;golds[4] = 100;
	golds[5] = 72;golds[6] = 44;golds[7] = 16;golds[8] = 07;golds[9] = 64;

	
    needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;
	needs[0] = 95;needs[1] = 75;needs[2] = 23;needs[3] = 73;needs[4] = 50;
	needs[5] = 22;needs[6] = 06;needs[7] = 57;needs[8] = 89;needs[9] = 98;

	max_gold_test_result((char *)"max gold test 04-1",2614,get_max_gold(1000,100));
	max_gold_test_result((char *)"max gold test 04-2",2614,get_max_gold2(1000,100));

}

int main()
{
    max_gold_test_01();
    max_gold_test_02();
    max_gold_test_03();

	return 0;
}
