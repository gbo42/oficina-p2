ortografia: ortografia.o
	gcc ortografia.o -o ortografia -Wall

ortografia.o: ortografia.c
	gcc -c ortografia.c -Wall

clean:
	-rm -f *.o

purge: clean
	-rm -f ortografia
