speller.out : mynew.o speller.o SpellRunner.o  
	g++ -ansi -Wall -o speller.out mynew.o speller.o SpellRunner.o  

mynew.o : mynew.cpp mynew.h 
	g++ -ansi -Wall -c mynew.cpp

speller.o : speller.cpp speller.h mynew.h QuadraticProbing2.h QuadraticProbing2.cpp 
	g++ -ansi -Wall -c speller.cpp

SpellRunner.o : SpellRunner.cpp CPUTimer.h mynew.h speller.h 
	g++ -ansi -Wall -c SpellRunner.cpp

clean : 
	rm -f speller.out mynew.o  speller.o  SpellRunner.o   
