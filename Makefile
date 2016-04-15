#file path
PARTITION=./Partition/*.h
INDEX=./Index/*.h
COMPRESS=./Compress/*.h
SERIALIZER=./Serializer/*.h
RECOMPRESS=./Recompress/*.h
BASIC=./BasicInclude.h
MAINCOM=./MainCompress.h
INCLUDEFILE=$(BASIC) $(PARTITION) $(INDEX) $(COMPRESS) $(SERIALIZER) $(RECOMPRESS) $(MAINCOM) 
#compile optition

CFLAGS=-Wall -std=c++11 -fopenmp -O2 -lz -lpthread

mfcO2: main.o
	g++ $(CFLAGS) -o mfcO2 *.o 

main.o: main.cpp $(INCLUDEFILE)
	g++ $(CFLAGS) -c main.cpp
	
.PHONY:clean
clean:
	rm -f mfcO2 *.o
