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


/*-----------------------------------------------------------------------------------
 @ptr
    Pointer to a memory block previously allocated with malloc, calloc or realloc. A-
    lternatively, this can be a null pointer , in which case a new block is allocated 
    (as if malloc was called).
 @size
    New size for the memory block, in bytes.
 @ret
    A null-pointer indicates either that @size was zero(an thus @ptr was deallocated), 
    or that the function did not allocate storage (and thus the block pointed by @ptr 
    was not modified).(C90 C++98)
    A null-pointer indicates that the function failed to allocate storage, and thus -
    the block pointed by @ptr was not modified.(C99 C11 C++11)

 1 In case that @ptr is a null pointer, the function behaves like @malloc , assigning 
   a new block of size bytes and returning a pointer to its beginning.
 2 if @size is zero, the memory previously allocated at @ptr is deallocated as if a -
   call to @free was made, and a null pointer is returned.(C90 C++98)
   If @size is zero, the return value depends on the particular library implementati-
   on: it may either be a null pointer or some other location that shall not be dere-
   ferenced.(C99 C11 C++11)
 3 If the function fails to allocate the requested block of memory, a null pointer is 
   returned, and the memory block pointed to by argument @ptr is not deallocated ( it 
   is still valid, and with its contents unchanged).

reference
    http://www.cplusplus.com/reference/cstdlib/realloc/?kw=realloc
    http://blog.csdn.net/snlying/article/details/4005238
example:
-----------------------------------------------------------------------------------*/
void* realloc (void* ptr, size_t size);

/*-----------------------------------------------------------------------------------
 @ptr
    Pointer to a memory block previously allocated with malloc, calloc or realloc.
 @func
    Deallocate memory block
    
 A block of memory previously allocated by a call to malloc, calloc or realloc is de-
 allocated, making it available again for further allocations. If @ptr does not point 
 to a block of memory allocated with the above functions,it causes undefined behavior.
 If @ptr is a null pointer, the function does nothing. Notice that this function does 
 not change the value of @ptr itself, hence it still points to the same (now invalid) 
 location.

reference
    http://www.cplusplus.com/reference/cstdlib/free/?kw=free
example:
-----------------------------------------------------------------------------------*/
void free (void* ptr);




