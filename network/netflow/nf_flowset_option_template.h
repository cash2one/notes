
#define SFT_SYS 1  /* Scope Field Type system*/
#define SFT_IF  2  /* Interface*/ 
#define SFT_LC  3  /* line card */
#define SFT_C   4  /* cache */
#define SFT_T   5  /* template */


/*******************************************************************************
ѡ��ģ��
    Ŀǰ��5�����͵�ѡ��ģ��(SFT_SYS SFT_IF SFT_LC SFT_C SFT_T),ÿ��ѡ��ģ�������
    �����������͵�ģ�塣
    
    ÿһ��ѡ��ģ���Ϊһ��scope���� scope filed type �� scope file length ��ʾ��type
    ��ʾ������ѡ��ģ�壬ʵ��������һ��������ʾģ�����ͣ�length��ʾ�������ռ�ü����ֽ�
    length��������һ��ռ2���ֽڡ�

Option Scope Length
    ����scopeռ�õ��ֽڣ����ģ�����������ѡ��ģ�壬����ֶε�ֵ����8.

Option Length
    ÿ�����͵�ѡ��ģ��������ɸ�option��ÿ��option��һ��option field type �� һ��
    option field length��type��ʾ������option����(TOTAL_PKTS_EXP��)��ʵ��������
    һ��������ʾģ�����ͣ�length��ʾ�������ռ�ü����ֽڣ�length��������һ��ռ2
    ���ֽڡ�

Options Template FlowSet Format
    The Options Template Record (and its corresponding Options Data Record) is 
    used to supply information about the NetFlow process configuration or NetFlow 
    process specific data, rather than supplying information about IP Flows.

    For example, the Options Template FlowSet can report the sample rate of a 
    specific interface, if sampling is supported, along with the sampling method 
    used.

          The format of the Options Template FlowSet follows.
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 1          |          Length               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Template ID           |      Option Scope Length      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Option Length          |       Scope 1 Field Type      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Scope 1 Field Length      |               ...             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Scope N Field Length      |      Option 1 Field Type      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Option 1 Field Length     |             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Option M Field Length     |           Padding             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

FlowSet ID = 1
    A FlowSet ID value of 1 is reserved for the Options Template.

Length
    Total length of this FlowSet. Each Options Template FlowSet MAY contain 
    multiple Options Template Records. Thus, the Length value MUST be used 
    to determine the position of the next FlowSet record, which could be either 
    a Template FlowSet or Data FlowSet. Length is the sum of the lengths of the 
    FlowSet ID, the Length itself, and all Options Template Records within this 
    FlowSet Template ID.
    
Template ID 		
    Template ID of this Options Template.This value is greater than 255.

Option Scope Length 		
    The length in bytes of any Scope field definition contained in the Options 
    Template Record (The use of "Scope" is described below).

Option Length 
    The length (in bytes) of any options field definitions	contained in this 
    Options Template Record.
    
Scope 1 Field Type		   
    The relevant portion of the Exporter/NetFlow process to which the Options 
    Template Record refers. Currently defined values are:			  
    1 System  2 Interface  3 Line Card  4 Cache  5 Template		  
    For example, the NetFlow process can be implemented on a per-interface basis, 
    so if the Options Template Record were reporting on how the NetFlow process 
    is configured, the Scope for the report would be 2 (interface). The associated	
    interface ID would then be carried in the associated Options Data FlowSet. 
    The Scope can be limited further by listing multiple scopes that all must match 
    at the same time.Note that the Scope fields always precede the Option fields.

Scope 1 Field Length
    The length (in bytes) of the Scope field, as it would appear in an Options 
    Data Record. 

Option 1 Field Type		  
    A numeric value that represents the type of field that would appear in the 
    Options Template Record.Refer to the Field Type Definitions section.   

Option 1 Field Length		 
    The length (in bytes) of the Option field.



Options Template FlowSet Example

   Per line card (the Exporter is composed of two line cards), we want
   to report the following Field Types:
   - Total number of Export Packets
   - Total number of exported Flows

   The format of the Options Template FlowSet is as follows:

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 1          |          Length = 24          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Template ID 257         |    Option Scope Length = 4    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Option Length = 8       |  Scope 1 Field Type = 3       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Scope 1 Field Length = 2    |   TOTAL_EXP_PKTS_SENT = 41    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Field Length = 2        |     TOTAL_FLOWS_EXP = 42      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Field Length = 2        |           Padding             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   
Option Scope Length = 4      
    һ��ѡ��ģ�������ɸ�scope������ֻ��һ��scope�����scope��һ��scope type
    ��һ��scope len��scope type��ʾscope������(������SFT_LC��ռ�����ֽ�)��
    scope len ��ʾscope type����ռ��2���ֽڡ�
    
Option Length = 8 
    ÿ��scope�������ɸ�option������ֻ��1��scope�����scope������option(����������)
    ÿ��option�ְ���һ��type��len��typeռ��2���ֽڣ�lenռ��2���ֽڡ�����һ��option
    ռ��4���ֽڣ�����optionռ��8���ֽڡ�
  
Scope 1 Field Type 3         
    scopeָ����SFT_SYS�����ͣ�����ָSFT_LC����Ҫ����ӿ���صĶ���
    
Scope 1 Field Length = 2    
    ��һ��������ʾscipe���ͣ��������ռ��2���ֽ�

Option 1 Field Type      TOTAL_EXP_PKTS_SENT = 41      
    ���scope��Ҫ������Ϣ�����ͣ�������41����ʾҪ������ĸ���(TOTAL_PKTS_EXP)

Option 1 Field Length  2  
    ��һ��������ʾ���ĸ������������ռ��2���ֽ�

Option 2 Field Type      TOTAL_FLOWS_EXP = 42      
    ���scope��Ҫ����ĵڶ�����Ϣ�����ͣ�������42����ʾҪ�������ĸ���(TOTAL_FLOWS_EXP)

Option 2 Field Length  2  
    ��һ��������ʾ���ĸ������������ռ��2���ֽ�

*******************************************************************************/

/* Options Template FlowSet -- System */
struct ot_sys
{
	u16   flowid;		    /* 1 */
	u16   total_len;	    /* sizeof(struct ot_sys) */
	
    u16   templateid;       /* �Ƕ��ٻ���̫���(�Լ����İ�) */
    u16   option_scope_len; /* Option Template�а���������scope����ֽڳ���*/
    u16   option_len;       /* Option Template�а���������Option����ֽڳ���*/
    u16   scope_field_type; /* 0x0001 System��0x0002 Interface */
    u16   scope_field_len;  /* ���������Scope��ĳ���(�ֽ�)��ȡ0�������������ֵ*/
    
    u16   total_flow_exp_type; /*��������ܸ���*/
    u16   total_flow_exp_len; 
    u16   total_exp_pkts_send_type; /*·����������ĵĸ���*/
    u16   total_exp_pkts_send_len;
    u16   as_type;                    /* peer or origin ��0Ϊpeer��1Ϊorigin*/
    u16   as_len;
    u16   pad_type;                          /*���ֽڶ���*/
    u16   pad_len;
    u16   pad;                       /*���ֽڶ���*/
};


