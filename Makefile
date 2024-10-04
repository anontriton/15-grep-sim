CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

default: gerp

gerp: main.o FileManager.o HashTable.o stringProcessing.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o gerp main.o FileManager.o HashTable.o \
	                     stringProcessing.o DirNode.o FSTree.o

main.o: main.cpp FileManager.h
	$(CXX) $(LDFLAGS) -c main.cpp

FileManager.o: FileManager.cpp FileManager.h
	$(CXX) $(LDFLAGS) -c FileManager.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(LDFLAGS) -c HashTable.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(LDFLAGS) -c stringProcessing.cpp

clean:
	rm -rf gerp main.o HashTable.o FileManager.o stringProcessing.o
