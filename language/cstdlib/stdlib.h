/******************************************************************************
@nptr: 参数nptr字符串，如果第一个非空格字符存在，是数字或者正负号则开始做类型转
       换，之后检测到非数字(包括结束符 \0) 字符时停止转换，返回整型数。
       否则，返回零，
功 能: 把字符串转换成长整型数 ASCII to integer 
*******************************************************************************/
int atoi(const char *nptr); 

