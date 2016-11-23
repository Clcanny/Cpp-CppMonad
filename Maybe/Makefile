run: clean main.o
	./main.o

clean:
	- @ rm main.o

main.o: main.cpp
	g++ -std=c++11 -ggdb main.cpp -o main.o
