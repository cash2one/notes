
/*
 @c
    Character to be checked, casted to an int, or EOF.
 @ret
    A value different from zero (i.e., true) if indeed c is a white-space character. 
    Zero (i.e., false) otherwise.
 @func
    Checks whether @c is a white-space character.

 white-space characters are any of:
 ' '  (0x20)   space (SPC)
 '\t' (0x09)   horizontal tab (TAB)
 '\n' (0x0a)   newline (LF)
 '\v' (0x0b)   vertical tab (VT)
 '\f' (0x0c)   feed (FF)
 '\r' (0x0d)   carriage return (CR)
*/

int isspace ( int c );
