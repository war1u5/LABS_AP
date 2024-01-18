//Exercitiul 1.

./sample-seq 999999 2
...
Something 999994
Something 999995
Something 999996
Something 999997
Something 999998
Something 999999

./sample-par 999999 2 2 
...
Something 999979 from thread 0 we processed 999980 tasks and submitted 999980 tasks
Something 999980 from thread 0 we processed 999981 tasks and submitted 999981 tasks
Something 999981 from thread 0 we processed 999982 tasks and submitted 999982 tasks
Something 999982 from thread 0 we processed 999983 tasks and submitted 999983 tasks
Something 999983 from thread 0 we processed 999984 tasks and submitted 999984 tasks
Something 999984 from thread 0 we processed 999985 tasks and submitted 999985 tasks
Something 999985 from thread 0 we processed 999986 tasks and submitted 999986 tasks
Something 999986 from thread 0 we processed 999987 tasks and submitted 999987 tasks
Something 999987 from thread 0 we processed 999988 tasks and submitted 999988 tasks
Something 999988 from thread 0 we processed 999989 tasks and submitted 999989 tasks
Something 999989 from thread 1 we processed 999990 tasks and submitted 999990 tasks
Something 999990 from thread 1 we processed 999991 tasks and submitted 999991 tasks
Something 999991 from thread 1 we processed 999992 tasks and submitted 999992 tasks
Something 999992 from thread 1 we processed 999993 tasks and submitted 999993 tasks
Something 999993 from thread 1 we processed 999994 tasks and submitted 999994 tasks
Something 999994 from thread 1 we processed 999995 tasks and submitted 999995 tasks
Something 999995 from thread 1 we processed 999996 tasks and submitted 999996 tasks
Something 999996 from thread 1 we processed 999997 tasks and submitted 999997 tasks
Something 999997 from thread 1 we processed 999998 tasks and submitted 999998 tasks
Something 999998 from thread 1 we processed 999999 tasks and submitted 999999 tasks
Something 999999 from thread 1 we processed 1000000 tasks and submitted 1000000 tasks

//Exercitiul 2.
./getPath-seq 999999 2
 0  1  2  3 
 0  1  2  7  5  8  3 
 0  1  2  7  5  8  6  9  4  3 
 0  1  2  7  9  4  3 
 0  1  2  7  9  6  8  3 
 0  1  6  8  3 
 0  1  6  8  5  7  2  3 
 0  1  6  8  5  7  9  4  3 
 0  1  6  9  4  3 
 0  1  6  9  7  2  3 
 0  1  6  9  7  5  8  3 
 0  4  3 
 0  4  9  6  1  2  3 
 0  4  9  6  1  2  7  5  8  3 
 0  4  9  6  8  3 
 0  4  9  6  8  5  7  2  3 
 0  4  9  7  2  1  6  8  3 
 0  4  9  7  2  3 
 0  4  9  7  5  8  3 
 0  4  9  7  5  8  6  1  2  3 
 0  5  7  2  1  6  8  3 
 0  5  7  2  1  6  9  4  3 
 0  5  7  2  3 
 0  5  7  9  4  3 
 0  5  7  9  6  1  2  3 
 0  5  7  9  6  8  3 
 0  5  8  3 
 0  5  8  6  1  2  3 
 0  5  8  6  1  2  7  9  4  3 
 0  5  8  6  9  4  3 
 0  5  8  6  9  7  2  3 

 //Exercitiul 3.
sanity-check: N=13

 0  5  7  9  4  3 
 0  5  8  3 
 0  5  7  2  3 
 0  4  3 

Pentru N=100001:
time ./getPath-par 100001 2 1: real    0m6.885s
time ./getPath-par 100001 2 2: real    0m3.902s
time ./getPath-par 100001 2 4: real    0m1.555s

//Exercitiul 5.
sanity test:
N = 18
./colorGraph-par 18 2 1
0  0  0  0  0  1  1  2  0  0  2  0  0  0  1  1  1  0

Pentru N=21:
time ./colorGraph-par 21 2 1: real    0m1.538s
time ./colorGraph-par 21 2 2: real    0m0.949s
time ./colorGraph-par 21 2 4: real    0m0.555s



