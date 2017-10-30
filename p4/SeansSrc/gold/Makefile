speller.out : mynew.o speller.o SpellRunner.o  
	g++ -ansi -Wall -pg -o speller.out mynew.o speller.o SpellRunner.o  

mynew.o : mynew.cpp mynew.h 
	g++ -ansi -Wall -pg -c mynew.cpp

speller.o : speller.cpp speller.h QuadraticProbing.cpp  QuadraticProbing.h
	g++ -ansi -Wall -pg -c speller.cpp

SpellRunner.o : SpellRunner.cpp CPUTimer.h mynew.h speller.h 
	g++ -ansi -Wall -pg -c SpellRunner.cpp

clean : 
	rm -f speller.out mynew.o  speller.o  SpellRunner.o   
