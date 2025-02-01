SAE1.01 : SAE.o TestSAE.o
	gcc SAE.o TestSAE.o -o sae

SAE.o : SAE.c SAE.h
	gcc -c SAE.c 

TestSAE.o : TestSAE.c SAE.h
	gcc -c TestSAE.c

clean : 
	rm *.o 

doc:
	doxygen
	