/******************************************************************************
@nptr: ����nptr�ַ����������һ���ǿո��ַ����ڣ������ֻ�����������ʼ������ת
       ����֮���⵽������(���������� \0) �ַ�ʱֹͣת����������������
       ���򣬷����㣬
�� ��: ���ַ���ת���ɳ������� ASCII to integer 
*******************************************************************************/
int atoi(const char *nptr); 

/*-----------------------------------------------------------------------------------
 @str
    C-string containing the representation of an integral number.
 @func
    Convert string to long integer
 @ret
    On success, the function returns the converted integral number as a long int val-
    ue. If  no valid conversion could be performed, a zero  value is returned. If the 
    converted value would be out of the range  of representable values by a long int, 
    it causes undefined behavior. See strtol for a more robust cross-platform alter-
    native when this is a possibility.

 The function first discards as many whitespace characters (as in @isspace) as neces-
 sary until the first non-whitespace character is found. Then, starting from this ch-
 aracter, takes an optional initial plus or minus sign followed by as many base-10 d-
 igits as possible, and interprets them as a numerical value.
 The string can contain additional characters after those that form the integral num-
 ber, which are ignored and have no effect on the behavior of this function.
 If the first sequence of non-whitespace characters in str is not a valid integral n-
 umber, or if no such sequence exists because either str is empty or it contains onl-
 y whitespace characters, no conversion is performed and zero is returned.    
-----------------------------------------------------------------------------------*/
long int atol ( const char * str );

/************************************************************************************
 @ret:
    0 if OK, nonzero on error
 @func
    The @putenv function takes a string of the form name=value and places it in the
    environment list. If name already exists, its old definition is first removed.
************************************************************************************/
int putenv(char *str);


