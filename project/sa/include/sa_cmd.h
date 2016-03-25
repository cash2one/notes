#ifndef __SA_CMD_H__
#define __SA_CMD_H__

#ifdef __READLINE_DEBUG

//����ṹ��
typedef int (*CmdProcFunc)(void);
typedef struct
{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
}CMD_PROC;

//�����������
#define MOCK_FUNC(funcName) int funcName(void){printf("  Enter "#funcName"!\n"); return 0;}

MOCK_FUNC(ShowMeInfo);
MOCK_FUNC(SetLogCtrl);
MOCK_FUNC(TestBatch);
MOCK_FUNC(TestEndianOper);

//�������꣬���ڼ���д
#define CMD_ENTRY(cmdStr, func)     {cmdStr, func}
#define CMD_ENTRY_END               {NULL,   NULL}

//�����
static CMD_PROC gCmdMap[] = {
    CMD_ENTRY("ShowMeInfo",       ShowMeInfo),
    CMD_ENTRY("SetLogCtrl",       SetLogCtrl),
    CMD_ENTRY("TestBatch",        TestBatch),
    CMD_ENTRY("TestEndian",       TestEndianOper),
    CMD_ENTRY_END
};

#define CMD_MAP_NUM     (sizeof(gCmdMap)/sizeof(CMD_PROC)) - 1/*End*/

#endif

#endif

