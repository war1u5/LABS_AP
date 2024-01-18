//Exercitiul 1.
./oneProducerOneConsumerOneBuffer 100 2 4
I finished Correctly

./oneProducerOneConsumer-fakeForScriptSeq 100 2
I finished Correctly

./testCorrectnessIntensive.sh oneProducerOneConsumer-fakeForScriptSeq oneProducerOneConsumerOneBuffer 100 10000
...
Test 9992/10000
Test 9993/10000
Test 9994/10000
Test 9995/10000
Test 9996/10000
Test 9997/10000
Test 9998/10000
Test 9999/10000
Test 10000/10000
Output correct on intensive test


//Exercitiul 2.
./oneProducerOneConsumerFiveBuffer 100 2 4
I finished Correctly

./testCorrectnessIntensive.sh oneProducerOneConsumer-fakeForScriptSeq oneProducerOneConsumerFiveBuffer 1000 1000 
...
Test 9996/10000
Test 9997/10000
Test 9998/10000
Test 9999/10000
Test 10000/10000
Output correct on intensive test


//Exercitiul 3.
./multipleProducersMultipleConsumers-fakeForScriptSeq 100 2 4
CORRECT

./multipleProducersMultipleConsumers-fakeForScriptSeq 100 2 4
CORRECT

./testCorrectnessIntensive.sh multipleProducersMultipleConsumers-fakeForScriptSeq multipleProducersMultipleConsumers 100 1000 4
...
Test 994/1000
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

//Exercitiul 5+6
./readersWriters 1000 2 4
Passed all

./readersWriters-fakeForScriptSeq 1000 2 4
Passed all

./testCorrectnessIntensive.sh readersWriters-fakeForScriptSeq readersWriters 10000 1000 4
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

//Exercitiul 7+8
./philosophers 5 0 2
All phylosophers have eaten

./philosophers-fakeForScriptSeq 5 0 2
All phylosophers have eaten

./testCorrectnessIntensive.sh  philosophers-fakeForScriptSeq philosophers 5 1000 0
...
Test 993/1000
Test 994/1000
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test
