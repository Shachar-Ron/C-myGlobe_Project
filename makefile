Globe:Countries.o HashTable.o keyValuePair.o LinkedList.o main.o
	gcc Countries.o HashTable.o keyValuePair.o LinkedList.o main.o -o Globe
Countries.o:Countries.c Countries.h
	gcc -c Countries.c
HashTable.o:HashTable.c LinkedList.h keyValuePair.h HashTable.h
	gcc -c HashTable.c
LinkedList.o:LinkedList.c Defs.h LinkedList.h
	gcc -c LinkedList.c
keyValuePair.o:keyValuePair.c keyValuePair.h 
	gcc -c keyValuePair.c

main.o:main.c LinkedList.h keyValuePair.h HashTable.h Countries.h Defs.h
	gcc -c main.c
clean:
	rm -f *.o
