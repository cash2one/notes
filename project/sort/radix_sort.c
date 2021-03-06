/************************************************************************************
 http://www.cnblogs.com/sun/archive/2008/06/26/1230095.html

 基数排序是非比较排序算法,算法的时间复杂度是O(n). 相比于快速排序的O(nlgn),从表面上看
 具有不小的优势.但事实上可能有些出入,因为基数排序的n可能具有比较大的系数K.因此在具体
 的应用中,应首先对这个排序函数的效率进行评估.

 基数排序的主要思路是,将所有待比较数值(注意,必须是正整数)统一为同样的数位长度,数位较
 短的数前面补零. 然后, 从最低位开始, 依次进行一次稳定排序(我们常用上一篇blog介绍的计
 数排序算法, 因为每个位可能的取值范围是固定的从0到9). 这样从最低位排序一直到最高位排
 序完成以后, 数列就变成一个有序序列.

 比如这样一个数列排序: 342 58 576 356, 以下描述演示了具体的排序过程

 第一次排序(个位):
 3 4 2
 5 7 6
 3 5 6
 0 5 8
 第二次排序(十位):
 3 4 2
 3 5 6
 0 5 8
 5 7 6
第三次排序(百位):
 0 5 8
 3 4 2
 3 5 6
 5 7 6
 结果: 58 342 356 576

 两个问题:

 为什么要从低位开始向高位排序?
    如果要从高位排序, 那么次高位的排序会影响高位已经排好的大小关系. 在数学中, 数位越
    高,数位值对数的大小的影响就越大.从低位开始排序,就是对这种影响的排序.数位按照影响
    力从低到高的顺序排序, 数位影响力相同则比较数位值.

 为什么同一数位的排序子程序要使用稳定排序?
    稳定排序的意思是指, 待排序相同元素之间的相对前后关系,在各次排序中不会改变.比如实
    例中具有十位数字5的两个数字58和356, 在十位排序之前356在58之前,在十位排序之后, 356
    依然在58之前.

    稳定排序能保证,上一次的排序成果被保留,十位数的排序过程能保留个位数的排序成果,百位
    数的排序过程能保留十位数的排序成果.
*/ 

