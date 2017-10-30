router.out : RouterRunner.o router.o
	g++ -Wall -o router.out RouterRunner.o router.o

RouterRunner.o : RouterRunner.cpp RouterRunner.h
	g++ -Wall -c RouterRunner.cpp

router.o : router.cpp router.h BinaryHeap.h BinaryHeap.cpp
	g++ -Wall -c router.cpp

clean:
	rm router.out router.o RouterRunner.o
