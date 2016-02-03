http://docs.scipy.org/doc/numpy/reference/generated/numpy.matrix.html

class numpy.matrix:
  '''
  Returns a matrix from an array-like object, or from a string of data. A matrix is -
  a specialized 2-D array that retains its 2-D nature through operations. It has cer-
  tain special operators, such as * (matrix multiplication) and ** (matrix power).

  @data : array_like or string
   If data is a string, it is interpreted as a matrix with commas or spaces separati-
   ng columns, and semicolons separating rows.
  @dtype : data-type
   Data-type of the output matrix.
  @copy : bool
   If data is already an ndarray, then this flag determines whether the data is copi-
   ed (the default), or whether a view is constructed.
   
  >>> a = np.matrix('1 2; 3 4')
  >>> print a
  [[1 2]
   [3 4]]
  >>>
  >>> np.matrix([[1, 2], [3, 4]])
  matrix([[1, 2],
          [3, 4]])   
  '''
  
  def getA1():
    '''
	Return self as a flattened ndarray. Equivalent to np.asarray(x).ravel()

    @Returns:ndarray
     self, 1-D, as an ndarray
	
    >>> x = np.matrix(np.arange(12).reshape((3,4))); x
    matrix([[ 0,  1,  2,  3],
            [ 4,  5,  6,  7],
            [ 8,  9, 10, 11]])
    >>> x.getA1()
    array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11])
	'''
  