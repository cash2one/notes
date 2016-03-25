#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sa_cmd.h"

#ifdef __READLINE_DEBUG
#include <readline/readline.h>
#include <readline/history.h>
static const char * const pszCmdPrompt = "clover>>";

//�˳�����ʽ������������(�����ִ�Сд)
static const char *pszQuitCmd[] = {"Quit", "Exit", "End", "Bye", "Q", "E", "B"};
static const unsigned char ucQuitCmdNum = sizeof(pszQuitCmd) / sizeof(pszQuitCmd[0]);



//����gCmdMap�е�CmdStr��(����Ϊֻ���ַ���)���Թ�CmdGeneratorʹ��
static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
	return gCmdMap[dwCmdIndex].pszCmd;
}
	  
//ִ������
static int ExecCmd(char *pszCmdLine)
{
    unsigned int dwCmdIndex = 0;

    if(NULL == pszCmdLine)
        return -1;

    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if(!strcmp(pszCmdLine, gCmdMap[dwCmdIndex].pszCmd))
            break;
    }
	
    if(CMD_MAP_NUM == dwCmdIndex)
        return -1;

    gCmdMap[dwCmdIndex].fpCmd(); //������Ӧ�ĺ���
        
    return 0;
}

#ifdef __READLINE_DEBUG

static int IsUserQuitCmd(char *pszCmd)
{
    unsigned char ucQuitCmdIdx = 0;

	for(; ucQuitCmdIdx < ucQuitCmdNum; ucQuitCmdIdx++)
    {
        if(!strcasecmp(pszCmd, pszQuitCmd[ucQuitCmdIdx]))
            return 1;
        }
        return 0;
    }

//�޳��ַ�����β�Ŀհ��ַ�(���ո�)
static char *StripWhite(char *pszOrig)
{
    if(NULL == pszOrig)
        return "NUL";

    char *pszStripHead = pszOrig;
    while(isspace(*pszStripHead))
        pszStripHead++;

     if('\0' == *pszStripHead)
         return pszStripHead;

    char *pszStripTail = pszStripHead + strlen(pszStripHead) - 1;

	while(pszStripTail > pszStripHead && isspace(*pszStripTail))
        pszStripTail--;
    *(++pszStripTail) = '\0';
    return pszStripHead;
}

static char *pszLineRead = NULL;  //�ն������ַ���
static char *pszStripLine = NULL; //�޳�ǰ�˿ո�������ַ���

char *ReadCmdLine()
{
    //���ѷ��������л������������ͷ�
    if(pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }

    //��ȡ�û������������
    pszLineRead = readline(pszCmdPrompt);
 
    //�޳���������β�Ŀհ��ַ������޳�������Ϊ�գ��������ʷ�б�
    pszStripLine = StripWhite(pszLineRead);

    if(pszStripLine && *pszStripLine)
        add_history(pszStripLine);

    return pszStripLine;
}
 
static char* CmdGenerator(const char *pszText, int dwState)
{
    static int dwListIdx = 0, dwTextLen = 0;

	if(!dwState)
    {
        dwListIdx = 0;
        dwTextLen = strlen(pszText);
    }
 
    //�������ַ����������б���ĳ�����ƥ��ʱ�����ظ������ַ���
    const char *pszName = NULL;
    while((pszName = GetCmdByIndex(dwListIdx)))
    {
        dwListIdx++;
        if(!strncmp (pszName, pszText, dwTextLen))
            return strdup(pszName);
    }
    return NULL;
}

static char** CmdCompletion (const char *pszText, int dwStart, int dwEnd)
{
    //rl_attempted_completion_over = 1;
    char **pMatches = NULL;
    if(0 == dwStart)
        pMatches = rl_completion_matches(pszText, CmdGenerator);
	return pMatches;
}

//��ʼ��Tab���ܲ����Command����
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}
 
#endif

int main_cmd(void)
{
#ifndef __READLINE_DEBUG
    printf("Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!\n\n");
#else
    printf("Note: Welcome to Interactive Command!\n");
    printf(" 	 Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();

	while(1)
    {
        char *pszCmdLine = ReadCmdLine();
        if(IsUserQuitCmd(pszCmdLine))
        {
            free(pszLineRead);
            break;
        }
        ExecCmd(pszCmdLine);
    }
#endif

    return 0;
}

#else

int main_cmd(void)
{
    char cmdbuf[512] = {0};
    char *cmdstr = NULL;
	int first = 1;

    while(1)
    {
        memset(cmdbuf, 0, 512);
		if(first)
		{
		    printf("->");
			first = 0;
		}
        cmdstr = fgets(cmdbuf, 512, stdin);
		printf("len:%d, %s",(int)strlen(cmdstr), cmdstr);
		printf("->");
    }
}



#endif



/*
1 [wangxiaoyuan_@localhost test1]$ gcc -Wall -o ReadLine ReadLine.c -D__READLINE_DEBUG -lreadline -lncurses
 2 [wangxiaoyuan_@localhost test1]$ ./ReadLine
 3 Note: Welcome to Interactive Command!
 4       Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!
 5 
 6 clover>>ShowMeInfo(��������)
 7   Enter ShowMeInfo!
 8 clover>>ShowMeInfo(UP��������ʷ����)
 9   Enter ShowMeInfo!
10 clover>>SetLogCtrl (����'Se'�Զ���ȫ)
11   Enter SetLogCtrl!
12 clover>>   TestEndianOper(��������)
13 clover>>TestEndian  (����'T'�Զ���ȫΪ"Test"��������'E'�Զ���ȫΪ"TestEndian ")
14   Enter TestEndianOper!
15 clover>>  TestBatch   (������β�ӿո��޷��Զ���ȫ)
16   Enter TestBatch!
17 clover>>ReadLine (����'R'�Զ���ȫ�ļ���)
18 clover>>quit
19 [wangxiaoyuan_@localhost test1]$
������Readline��ʱ��ִ�н�����£�

1 [wangxiaoyuan_@localhost test1]$ gcc -Wall -o ReadLine ReadLine.c                                        
2 ReadLine.c:41: warning: 'GetCmdByIndex' defined but not used
3 ReadLine.c:49: warning: 'ExecCmd' defined but not used
4 [wangxiaoyuan_@localhost test1]$ ./ReadLine
5 Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!



http://www.tuicool.com/articles/zu2um27


*/
	

