routerGold1.out : RouterRunner.o router.o
	g++ -Wall -g -o routerGold1.out RouterRunner.o router.o

RouterRunner.o : RouterRunner.cpp RouterRunner.h
	g++ -Wall -g -c RouterRunner.cpp

router.o : router.cpp router.h QuadnaryHeap.h QuadnaryHeap.cpp
	g++ -Wall -g -c router.cpp

clean:
	rm routerGold1.out router.o RouterRunner.o
