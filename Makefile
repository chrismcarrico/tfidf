CC = g++
OBJ = main.o dict.o langRules.o porterRules.o eTable.o
CFLAGS = -Wall -I. -g -c -O3
LFLAGS = -o tfidf

PA8: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS)

dict.o: dict.h dict.cpp
	$(CC) dict.cpp $(CFLAGS)

langRules.o: langRules.h langRules.cpp
	$(CC) langRules.cpp $(CFLAGS)

porterRules.o: porterRules.h porterRules.cpp
	$(CC) porterRules.cpp $(CFLAGS)

ht.o: eTable.h eTable.cpp
	$(CC) ht.cpp $(CFLAGS)

main.o:	dict.h langRules.h porterRules.h eTable.h main.cpp 
	$(CC) main.cpp $(CFLAGS)

clean:
	rm -f *.out *.gch *.o PA9
