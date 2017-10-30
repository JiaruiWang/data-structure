router.out : RouterRunner.o router.o
	g++ -Wall -o router.out RouterRunner.o router.o

RouterRunner.o : RouterRunner.cpp RouterRunner.h
	g++ -Wall -c RouterRunner.cpp

router.o : router.cpp router.h 
	g++ -Wall -c router.cpp

clean:
	rm -f router.out router.o RouterRunner.o
