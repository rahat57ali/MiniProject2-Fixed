output: main.o
	g++ -o output main.o -lgtest -lgtest_main -pthread
main.o: main.cpp textEditor.h
	g++ -c main.cpp
clean:
	rm *.o